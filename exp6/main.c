/* Huffman Compression And Depression
 * main algorithm
 * A. compression
 *  1. Read all `bytes` from the file
 *  2. Construct a huffman Tree
 *  3. Recode using `bit`
 *  4. Write Header to the compressed file
 *  5. write the bits
 * B. Depression
 *  1. Read the header and reconstruct the huffman tree
 *  2. Translate bits 
 *  3. Write the file
 */

/* Note
 * 1. [depression] Do we need to use bit field?
 * 2. [depression] Find the certain bit in the 
 * 3. [compression] to write bit to a file in C, check 
 *                  https://stackoverflow.com/questions/13252697/writing-bits-to-a-file-in-c
 * 4. [compression] When a byte is read, use a linked list to save it
 * 5. [all] input format: ./huff -c file 
 *                        ./huff -d file
 */

/* main.c */
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Definitions */
#define MAP_SIZE 256

/* Typedef */
typedef struct TreeNode* TNode;
typedef struct TreeNode* HuffTree;
typedef struct MapNode* MNode;
typedef struct HuffHeader* HHead;

/* Structs */
struct OriMapNode {
    unsigned char c;
    uint64_t weight;
};

struct TreeNode {
    uint64_t weight;
    unsigned char c;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct MapNode {
    unsigned char code[256];                 // a code should be less than 256 bit
    int length;
};

struct HuffHeader {
    uint64_t code_len;
    struct OriMapNode map[256];
};

/* Functions */
void compress(char* name);
void depress(char* name, char* out_name);
int my_cmp(const void* p, const void* q);
HuffTree BuildTree(struct OriMapNode* array);
void GenCode(MNode* Map, HuffTree root);
void __gen_code(MNode* Map, HuffTree T, unsigned char* code, int len);

int main(int argc, char const *argv[]) {
    /* get command */
    // compress("1");
    if(argc < 3) {
        printf("ERROR: Invalid Input!\n");
    } else {
        if(argv[1][0] == '-') {
            if(argv[1][1] == 'c') {
                /* compress */
                compress(argv[2]);
            } else if(argv[1][1] == 'd') {
                /* depress */
                if(argc < 4) {
                    printf("ERROR: Invalid Input\n");
                }
                depress(argv[2], argv[3]);
            } else {
                /* Invalid */
            }
        } else {
            /* Invalid */
        }
    }
}

/* Compress(file)
 * 1. read file name and open file
 * 2. record weight using a map
 * 3. construct huffman_tree
 * 4. use a header to indicate the number of bit
 */
void compress(char* name) {
    FILE* fin;
    FILE* fout;
    char* ext = ".haff";
    unsigned char c;
    int i, j;
    fin = fopen(name, "r");
    char* name_tmp = malloc(sizeof(name) * sizeof(char) + 10 * sizeof(char));
    for(i = 0; i < sizeof(name); ++ i) {
        name_tmp[i] = name[i];
    }
    for(j = 0; j < 5; ++ j) {
        name_tmp[i + j] = ext[j];
    }
    name_tmp[i + j] = '\0';
    printf("%s", name_tmp);
    fout = fopen(name_tmp, "w");
    /* we assum a file can be very large */
    struct OriMapNode map[MAP_SIZE];                  // unsigned char has 0 - 255

    for(i = 0; i < MAP_SIZE; ++ i) {
        map[i].c = i;
        map[i].weight = 0;
    }
    /* check */
    if(!fin) {
        printf("ERROOR: file not found. \n");
        exit(1);
    }

    /* recode all char in a map */
    while(!feof(fin)) {
        c = getc(fin);
        map[c].weight ++;
    }

    /* sort */
    qsort(map, MAP_SIZE, sizeof(struct OriMapNode), my_cmp);

    /* Build a huffman Tree */
    HuffTree HTree = BuildTree(map);

    /* generate code 
     * 1. use a new map to save code for each char
     * 2. use an array to save the code
     * 3. for every 8 bit(8 chars), set the thing and make it to a new file
     */
    MNode* CodeMap = malloc(MAP_SIZE * sizeof(MNode));
    for(i = 0; i < MAP_SIZE; ++ i) {
        CodeMap[i] = malloc(sizeof(struct MapNode));
        CodeMap[i]->length = 0;
        for(j = 0; j < 256; ++ j) {
            CodeMap[i]->code[j] = 0;
        }
    }

    /* Generate code for each char */
    GenCode(CodeMap, HTree);

    /* We need a header.... */
    HHead header = malloc(sizeof(struct HuffHeader));
    header->code_len = HTree->weight;
    for(i = 0; i < MAP_SIZE; ++ i) {
        header->map[i].weight = map[i].weight;
        header->map[i].c = map[i].c;
    }
    fwrite(header, sizeof(struct HuffHeader), 1, fout);

    /* Now the code for char c is saved in CodeMap[c]->code 
     * and lenth is CodeMap[c]->length, 
     * maybe we can now get everything written to the file?  
     */
    rewind(fin);                        // reset the point
    unsigned char tmp = 0;              // tmp is 0000 0000
    int curr_bit = 0;                   // we have written to the bit
    int char_bit = 0;                   // pointer for the char
    int len = 0;                        // current char's code lenth

    while(!feof(fin)) {
        c = getc(fin);                  // phrase 1 char
        char_bit = 0;                   // reset char_bit
        len = CodeMap[c]->length;
        
        while(char_bit < len) {
            /* we haven't finished the char */
            if(curr_bit == 8) {
                /* Oops! tmp is full! */
                fwrite(&tmp, sizeof(tmp), 1, fout);
                curr_bit = 0;
                tmp = 0;        
            } else {
                if(CodeMap[c]->code[char_bit] == 1) {
                    // set the curr_bit to 1
                    tmp = tmp | (1 << (7 - curr_bit));
                }
                curr_bit ++;
                char_bit ++;
            }
        }
    }
    /* for the final tmp -> not full */
    if(curr_bit != 0) {
        fwrite(&tmp, sizeof(tmp), 1, fout);
    }
    //printf("%llu\n", header->code_len);
}

void depress(char* name, char* out_name) {
    FILE* fin;
    FILE* fout;


    fin = fopen(name, "r");
    fout = fopen(out_name, "w");

    /* Get the header */
    HHead header = malloc(sizeof(struct HuffHeader));
    fread(header, sizeof(struct HuffHeader), 1, fin);

    /* we have code->len 's char */
    // printf("%llu", header->code_len);

    /* Construct the tree */
    HuffTree root = BuildTree(header->map);
    // printf("%d", root->right->right->c);

    /* Gain all available bits */
    uint64_t whole_char_num = header->code_len;
    unsigned char tmp = 0;
    uint64_t char_num = 0;                       // we have now depressed 
    int curr_bit_cnt = 0;                       // current bit count in tmp
    int curr_bit = 0;                           // record the current bit
    TNode tmpNode = root;
    unsigned char out = 0;
    while(!feof(fin)) {
        tmp = getc(fin);
        // printf("tmp = %d\n", tmp);

        while(char_num < whole_char_num) {
            /* We have reached the char we need */
            if(!(tmpNode->left)) {
                out = tmpNode->c;
                // printf("Dump %d\n", out);
                if(char_num != whole_char_num - 1 || out != 255) {
                    fwrite(&out, sizeof(out), 1, fout);
                }

                /* reset */
                tmpNode = root;
                char_num ++;
                out = 0;
                if(char_num == whole_char_num) {
                    break;
                }
            }
            if(((tmp) & (1 << (7 - curr_bit))) != 0) {
                // printf("Get 1\n");
                tmpNode = tmpNode->right;
            } else {
                // printf("Get 0\n");
                //printf("The anser id %d\n", ((tmp) & (1 << (7 - curr_bit))));
                tmpNode = tmpNode->left;
            }
            curr_bit ++;
            if(curr_bit == 8) {
                curr_bit = 0;
                break;
            }
        }
    }
}

int my_cmp(const void* p, const void* q) {
    struct OriMapNode a = *(struct OriMapNode*)p;
    struct OriMapNode b = *(struct OriMapNode*)q;

    if(a.weight > b.weight) {
        return 1;
    } else if(a.weight == b.weight) {
        return 0;
    } else {
        return -1;
    }
}

HuffTree BuildTree(struct OriMapNode* array) {
    int i, j;
    TNode nodes[MAP_SIZE];
    for(i = 0; i < MAP_SIZE; ++ i) {
        nodes[i] = malloc(sizeof(struct TreeNode));
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
        nodes[i]->weight = array[i].weight;
        nodes[i]->c = array[i].c;
    }

    for(i = 1; i < MAP_SIZE; i ++) {
        TNode parent = malloc(sizeof(struct TreeNode));
        parent->weight = nodes[i - 1]->weight + nodes[i]->weight;
        parent->left = nodes[i - 1];
        parent->right = nodes[i];
        nodes[i - 1] = NULL;
        nodes[i] = parent;

        /* re-sort the file */
        for(j = i ; j < MAP_SIZE - 1; ++ j) {
            if(nodes[j]->weight > nodes[j + 1]->weight) {
                TNode tmp = nodes[j + 1];
                nodes[j + 1] = nodes[j];
                nodes[j] = tmp;
            } else {
                break;
            }
        } 
    }
    return nodes[MAP_SIZE - 1];
}

void GenCode(MNode* Map, HuffTree root) {
    unsigned char code[MAP_SIZE] = {0};
    __gen_code(Map, root, code, 0);
}

void __gen_code(MNode* Map, HuffTree T, unsigned char* code, int len) {
    int i;
    if(!(T->left) && !(T->right)) {
        // printf("Mark %d, Code: \n", T->c);
        // for(i = 0; i < len; ++ i) {
        //     printf("%d", code[i]);
        // }
        // printf("\n");
        for(i = 0; i < len; ++ i) {
            Map[T->c]->code[i] = code[i];
            Map[T->c]->length = len;
        }
    } else {
        /* we have both left and right */
        code[len] = 0;
        __gen_code(Map, T->left, code, len + 1);
        code[len] = 1;
        __gen_code(Map, T->right, code, len + 1);
    }
}


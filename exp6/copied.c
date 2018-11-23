/* copied.c 
 * from https://github.com/Bestoa/huffman-codec/blob/master/huffman.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ZAP(x) (memset((x), 0, sizeof(*(x))))            // make x all zero
#define SETB(x, b) ((x |= ((1) << (b))))                // set the bth bit to 1
#define RSETB(x, b) ((x &= (~((1) << b))))              // set the bth bit to 0
#define GETB(x, b) ((x) & (1 << (b)))                   // get the bth bit

#define GEN_TABLE_UNIT(d, f) ((d) | ((f) << 8))

#define TABLE_SIZE (256)                                // cause a char has 0 - 255

struct huffman_node {
    uint64_t weight;                                    // don't know why
    uint8_t value;
    struct huffman_node* left;
    struct huffman_node* right;
};

struct huffman_code {
    uint8_t code[TABLE_SIZE];
    uint8_t length;
} huffman_code_list[TABLE_SIZE];                        // each char has a code and each code's lenth is less than 256

int table_unit_compar(const void* a, const void* b) {
    uint64_t x = *(uint64_t*)a;
    uint64_t y = *(uint64_t*)b;

    if(x > y) {
        return 1;
    } else if(x == y) {
        return 0;
    } else {
        return -1;
    }
}

void clean_huffman_code_list() {
    ZAP(&huffman_code_list);
}

void generate_huffman_code_recusive(struct huffman_node* tree, char* code, int len) {
    if(!tree->left) {
        memcpy(huffman_code_list[tree->value].code, code, len);
        huffman_code_list[tree->value].length = len;
        return;
    }
    generate_huffman_code_recusive(tree->left, code, len + 1);
    code[len] = 1;
    generate_huffman_code_recusive(tree->right, code, len + 1);
    code[len] = 0;
}

void generate_huffman_code(struct huffman_node* tree) {
    char code[TABLE_SIZE] = { 0 };
    generate_huffman_code_recusive(tree, code, 0);
}

void free_huffman_tree(struct huffman_node* root) {
    if(root->left) {
        free_huffman_tree(root->left);
    } 

    if(root->right) {
        free_huffman_tree(root->right);
    } 

    free(root);
}

struct huffman_node* build_huffman_tree(uint64_t* table, int size) {
    struct huffman_node* huffman_node_list[size];
    int i = 0, j = 0;
    for(i = 0; i < size; ++ i) {
        huffman_node_list[i] = malloc(sizeof(struct huffman_node));
        if(!huffman_node_list[i]) {
            printf("ERROR: malloc ERROR\n");
            exit(1);
        }
        ZAP(huffman_node_list[i]);
        huffman_node_list[i]->weight = table[i] >> 8;
        huffman_node_list[i]->value = table[i] & 0xff;
    }

    for(i = 0; i < size - 1; ++ i) {
        struct huffman_node* hn = malloc(sizeof(struct huffman_node));
        hn->weight = huffman_node_list[i]->weight + huffman_node_list[i + 1]->weight;
        hn->left = huffman_node_list[i];
        hn->right = huffman_node_list[i + 1];
        huffman_node_list[i + 1] = hn;
        huffman_node_list[i] = NULL;

        for(j = i + 1; j < size - 1; ++ j) {
            if(huffman_node_list[j]->weight > huffman_node_list[j + 1]->weight) {
                struct huffman_node* tmp = huffman_node_list[j + 1];
                huffman_node_list[j + 1] = huffman_node_list[j];
                huffman_node_list[j] = tmp;
            } else {
                break;
            }
        }
    }
    return huffman_node_list[size - 1];
}

struct huffman_file_header {
    char magic[8];
    uint64_t file_size;
    uint32_t table_size;
};

#define MAGIC ("HUFFMAN")
int encode(const char* name) {
    int c, ret = 0;
    FILE* ifp, *ofp;
    uint8_t cached_c = 0, used_bits = 0;
    uint64_t table[TABLE_SIZE] = { 0 };

    struct huffman_node* tree = NULL;
    struct huffman_file_header fh;

    ifp = fopen(name, "r");

    while(!feof(ifp)) {
        c = fgetc(ifp);
        table[c] ++;
    }

    fseek(ifp, 0L, SEEK_SET);

    for(c = 0; c < TABLE_SIZE; ++ c) {
        table[c] = GEN_TABLE_UNIT(c, table[c]);
    }
    qsort(table, TABLE_SIZE, sizeof(uint64_t), table_unit_compar);
    for(c = 0; c < TABLE_SIZE; c ++) {
        if(table[c] >> 8) {
            break;
        }
    }

    if(c > TABLE_SIZE - 2) {
        c = TABLE_SIZE - 2;
    }

    tree = build_huffman_tree(table + c, TABLE_SIZE - c);
    if(!tree) {
        return -1;
    }

    clean_huffman_code_list();
    generate_huffman_code(tree);

    ofp = fopen("out.he", "wb");

    ZAP(&fh);
    memcpy(fh.magic, MAGIC, sizeof(MAGIC));
    fh.file_size = tree->weight;
    fh.table_size = TABLE_SIZE - c;
    fwrite(&fh, 1, sizeof(struct huffman_file_header), ofp);
    fwrite(table + c, TABLE_SIZE - c, sizeof(uint64_t), ofp);

    while(!feof(ifp)) {
        int i = 0;
        c = fgetc(ifp);
        for(i = 0; i < huffman_code_list[c].length; i ++) {
            if(huffman_code_list[c].code[i]) {
                SETB(cached_c, 7 - used_bits);
            }
            used_bits ++;
            if(used_bits == 8) {
                fputc(cached_c, ofp);
                used_bits = 0;
                cached_c = 0;
            }
        }
    }

    if(used_bits) {
        fputc(cached_c, ofp);
    }
    fclose(ofp);

}

int decode(const char* name) {
    int ret = 0;
    int cached_c = 0, used_bits = 0;
    FILE *ifp, *ofp;
    uint64_t table[TABLE_SIZE] = { 0 };
    uint64_t size = 0;
    struct huffman_file_header fh;
    struct huffman_node *tree = NULL, *walk;

    ifp = fopen(name, "r");
    
    fread(&fh, sizeof(struct huffman_file_header), 1, ifp);
    fread(table, sizeof(uint64_t), fh.table_size, ifp);

    tree = build_huffman_tree(table, fh.table_size);

    ofp = fopen("out.hd", "wb");
    walk = tree;
    while(size < fh.file_size) {
        if(!used_bits) {
            if(feof(ifp)) {
                
            }
            cached_c = fgetc(ifp);
        }

        if(GETB(cached_c, 7 - used_bits)) {
            walk = walk->right;
        } else {
            walk = walk->left;
        }
        used_bits ++;

        if(used_bits == 8) {
            used_bits = 0;
        }

        if(!walk->left) {
            fputc(walk->value, ofp);
            walk = tree;
            size ++;
        }
    }

    fclose(ofp);
    fclose(ifp);
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        // invaild argument
    } else if(argv[1][0] == 'e') {
        encode(argv[2]);
    } else if(argv[1][0] == 'd') {
        decode(argv[2]);
    }

    return 0;
}
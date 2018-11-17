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
 */

/* main.c */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* Init file pointer */
    FILE* fin = NULL;

    /* Check argc */
    if(argc == 1) {
        /* Only 1 input */
        char file_name[20];
        scanf("%s", file_name);

        /* use `w`: 
         * This is strictly for compatibility with ISO/IEC 9899:1990
         * (``ISO C90'') and has effect only for fmemopen() ; otherwise ``b'' is ignored.
         */
        fin = fopen(file_name, "rb");
    } else {
        /* we have a file name argument */
        fin = fopen(argv[1], "rb");
    }

    if(fin == NULL) {
        printf("ERROR: FILE NOT EXIST! \n");
        exit(1);
    }

    /* init bit thing */
    char scanner = 0;
    while((scanner = getc(fin)) != EOF) {
#ifdef DEBUG
        putc(scanner, stdout);
#endif
        
    }
    return 0;
}

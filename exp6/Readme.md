# Huffman Compression

Use huffman code to `compress` the input file. Also used to depress one compressed file.

## HuffmanTree Building

The build of huffman tree of my program is general and nothing special.

I used an array to save all nodes from small to big and then make parents for every two nodes.

The one with smaller weight is always on the left while the one with larger weight on the right

## huff file Header

The output file has an extension name of `.huff` and it contains a header to allow reconstructing the original file.

The header contains two things. The first thing is a `uint64_t` type var aiming to indicate the original file's size(char); The second thing is a table which is the same as the one when we construct the file.

## Bulid the code

To build a working program, use the command below:

```
gcc main.c -Wall -Wextra
```

## Credits

The `copied.c` is a file (nearly)copied from https://github.com/Bestoa/huffman-codec
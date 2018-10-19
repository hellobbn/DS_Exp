#include "main.h"

#include <stdlib.h>

double atoF(char* s, int len) {
    char* t = malloc(len);
    for(int i = 0; i < len; ++ i) {
        *(t + i) = *(s + i);
    }

    double p = atof(t);
    free(t);
    return p;
}

int atoI(char* s, int len) {
    char* t = malloc(len);
    for(int i = 0; i < len; ++ i) {
        *(t + i) = *(s + i);
    }

    int p = atoi(t);
    free(t);
    return p;
}

int IsOpr(char c) {
    if(c == '+' || c == '*' || c == '/' || c == '-') {
        return 1;
    }

    return 0;
}
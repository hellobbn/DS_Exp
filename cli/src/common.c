#include "main.h"

#include <stdlib.h>
#include <stdio.h>

double atoF(char* s, int len) {
    char* t = malloc(len + 1);
    for(int i = 0; i < len; ++ i) {
        *(t + i) = *(s + i);
    }
    *(t + len) = '\0';
    double p = atof(t);
    free(t);
    return p;
}

int atoI(char* s, int len) {
    char* t = malloc(len + 1);
    for(int i = 0; i < len; ++ i) {
        *(t + i) = *(s + i);
    }
    *(t + len) = '\0';
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

double absF(double x) {
    return x > 0 ? x : -x;
}

double PoW(double x, int p) {
    int po = abs(p);
    double result = 1;
    for(int i = 0; i < po; ++ i) {
        result *= x;
    }
    if(p > 0) {
        return result;
    } else {
        return 1/result;
    }
}
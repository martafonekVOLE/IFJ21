#include <stdio.h>

#define DEBUG 0

#define M_PRINT(fmt) \
    do { if (DEBUG){ fprintf(stderr, "%c\n", fmt); }} while (0)
        

int main(int argc, char **argv){
    char c = 'A';
    M_PRINT(c);
}
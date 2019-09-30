#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

void *emalloc(size_t s){
    void *result = malloc(s);
    if(NULL == result){
        fprintf(stderr, "Memory Allocation Failure!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void *erealloc(void *p, size_t s){
    void *my_array = realloc(p, s);
    if(NULL == my_array){
        fprintf(stderr, "Memory Realloction Failure!\n");
        exit(EXIT_FAILURE);
    }

    return my_array;
}

int getword(char *s, int limit, FILE *stream){
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);

    while(!isalnum(c = getc(stream)) && EOF != c);

    if(EOF == c) {
        return EOF;
    } else if (--limit > 0){
        *w++ = tolower(c);
    }

    while(--limit > 0){
        if(isalnum(c = getc(stream))){
            *w++ = tolower(c);
        } else if('\'' == c){
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w-s;
}



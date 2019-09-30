#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequency;
    int **keys;
};

htable htable_new(int capacity){
    int i = 0;
    

    /*Declare htable, allocate memory as needed */
    htable result = emalloc(sizeof *result);

    /* initialise htable capacity to argument capacity, and num keys to 0 */
    result->capacity = capacity;
    result->num_keys = 0;

    /*allocate htables frequency array to be able to hold enough ints */
    result->frequency = emalloc(result->capacity * sizeof result->frequency[0]);

    /*allocate htables keys to able to store enough strings */
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);

    /*set each frequency and key to their intial values */
    for (i = 0; i < result->capacity; i++){
        result->keys[i] = NULL;
        result->frequency[i] = 0;
    }

    /* return hash table */
    return result;
}

void htable_free(htable h){
    free(h->keys);
    free(h->frequency);
    free(h);
}

static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;
    
    while(*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str){
    unsigned int key;
    int i, index;
    
    /*convert string to integer, find out where in *keys string should go */
    key = htable_word_to_int(str);
    i = key % h->capacity;
    index = i;

    /* if no string in pos, copy string to it, set the cell in *frequency to 1
       icrement num keys */
    if(h->keys[i] == NULL){
        h->keys[i] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
        strcpy(h->keys[i], str);
        h->frequency[i] = 1;
        h->num_keys++;
        return 1;
    }
    
    /* if exact same string is in that pos, increment *frequency at that pos,
       return it */
    else if(strcmp(str, h->keys[i])== 0){
        h->frequency[i]++;
        return h->frequency[i];
    }

    
    else {

        /* if incorrect string at that pos, move along array till open space
           or string you are looking for. mod by table capacity each time you
           add to the position if you need to wrap around to the beginning of
           the table */
        while(h->keys[i] != NULL && strcmp(str, h->keys[i]) != 0){
                i = (i + 1) % h->capacity;
                if(i == index){
                    return 0;
                }
            }

        /* if you find open space copy string, set frequency to 1 and increment
           num of keys */
            if(h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str) + 1) * sizeof h->keys[0][0]);
                strcpy(h->keys[i], str);
                h->frequency[i] = 1;
                h->num_keys++;
                return 1;
            }


            /* if you find correct string, increment frequency and return it */
            else if(strcmp(h->keys[i],str) == 0){
                h->frequency[i]++;
                return h->frequency[i];
            }
    }
    /* hash table must be full so return 0 */
    return 0;
}

void htable_print(htable h, FILE *stream){
    int i;

    /* for each element in h up to capacity, if key isnt empty(exists)
       print it after frequency */
    for(i = 0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            fprintf(stream, "%d %s\n", h->frequency[i], h->keys[i]);
        }
    }
}


int htable_search(htable h, char *str){
    int col = 0;
    int pos = htable_word_to_int(str) % h->capacity;

    while(h->keys[pos] != NULL && strcmp(str, h->keys[pos]) != 0){
        pos++;
        col++;
    }

    if(col == h->capacity){
        return 0;
    }
    else{
        return h->frequency[pos];
    }
}



            
            

    



    



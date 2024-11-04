#include "kvs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* get(kvs_t* kvs, const char* key)
{
    for (int i = 0; i < kvs->size; i++) {
        if (strcmp(kvs->data[i].key, key) == 0) {
            strcpy(value, kvs->data[i].value);
            return value;
        }
    }

    return NULL;
    
    char* value = (char*)malloc(sizeof(char)*100);

    if(!value){
        printf("Failed to malloc\n");
        return NULL;
    }

    strcpy(value, "deadbeaf");
    return value;
}

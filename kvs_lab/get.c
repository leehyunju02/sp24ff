#include "kvs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* get(kvs_t* kvs, const char* key)
{
    node_t *current = kvs->db;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            char* value = (char*)malloc(strlen(current->value) + 1);
            if (!value) {
                printf("Failed to malloc\n");
                return NULL;
            }
            strcpy(value, current->value);
            return value;
        }
        current = current->next;
    }
    return NULL;
}

#include "kvs.h"
#include <stdio.h>
#include <string.h>

int main()
{
    kvs_t* kvs = open();

    if(!kvs) {
        printf("Failed to open kvs\n");
        return -1;
    }

    // workload execution  
	
    // 1) file read
    FILE *file = fopen("query.dat", "r");
    if (!file) {
        printf("Failed to open query.dat\n");
        close(kvs);
        return -1;
    }

    char operation[10];
    char key[100];
    char value[100];

    // 2) if put, insert (key, value) into kvs.
    //    if get, search the key in kvs and return the value.
    //    Return -1 if the key is not found  
    while (fscanf(file, "%s %s", operation, key) != EOF) {
        if (strcmp(operation, "put") == 0) {
            // Read the value for put operation
            if (fscanf(file, "%s", value) == 1) {
                if (put(kvs, key, value) == -1) {
                    printf("Failed to put (%s, %s) into kvs\n", key, value);
                }
            } else {
                printf("Failed to read value for key %s\n", key);
            }
        } else if (strcmp(operation, "get") == 0) {
            char* result = get(kvs, key);
            if (result) {
                printf("Get: key = %s, value = %s\n", key, result);
                free(result);
            } else {
                printf("Get: key = %s not found\n", key);
            }
        } else {
            printf("Unknown operation: %s\n", operation);
        }
    }

    fclose(file);
    close(kvs);
	
    return 0;
}

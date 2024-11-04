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

    // answer.dat 파일을 쓰기 모드로 열기
    FILE *output_file = fopen("answer.dat", "w");
    if (!output_file) {
        printf("Failed to open answer.dat\n");
        close(kvs);
        fclose(file);
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
                    fprintf(output_file, "Failed to put (%s, %s) into kvs\n", key, value);
                }
            } else {
                fprintf(output_file, "Failed to read value for key %s\n", key);
            }
        } else if (strcmp(operation, "get") == 0) {
            char* result = get(kvs, key);
            if (result) {
                fprintf(output_file, "Get: key = %s, value = %s\n", key, result);
                free(result);
            } else {
                fprintf(output_file, "Get: key = %s not found\n", key);
            }
        } else {
            fprintf(output_file, "Unknown operation: %s\n", operation);
        }
    }

    // 파일 닫기
    fclose(file);
    fclose(output_file);
    close(kvs);
	
    return 0;
}

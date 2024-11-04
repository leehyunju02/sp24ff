#include "kvs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int put(kvs_t* kvs, const char* key, const char* value)
{
    printf("put: %s, %s\n", key, value);

    node_t* current = kvs->db;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);  // 기존 값 메모리 해제
            current->value = (char*)malloc(strlen(value) + 1);
            if (!current->value) {
                printf("Failed to malloc\n");
                return -1;
            }
            strcpy(current->value, value);
            return 0;
        }
        current = current->next;
    }

    // 새로운 노드 생성
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        printf("Failed to malloc\n");
        return -1;
    }
    strcpy(new_node->key, key);  
    new_node->value = (char*)malloc(strlen(value) + 1);
    if (!new_node->value) {
        printf("Failed to malloc\n");
        free(new_node);
        return -1;
    }
    strcpy(new_node->value, value);

    // 새로운 노드를 리스트의 맨 앞에 추가
    new_node->next = kvs->db;
    kvs->db = new_node;

    kvs->items++; 

    return 0;
}

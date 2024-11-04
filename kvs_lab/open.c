#include "kvs.h"
#include <stdlib.h>
#include <stdio.h>

kvs_t* open()
{
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));
    if (kvs) {
        kvs->items = 0;
        kvs->db = NULL;  // db를 NULL로 초기화
        printf("Open: kvs has %d items\n", kvs->items);
    } else {
        printf("Failed to allocate memory for kvs\n");
    }
    return kvs;
}

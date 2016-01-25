#ifndef __MY_FREE_LIST_H__
#define __MY_FREE_LIST_H__

#include "my_malloc.h"
#include <sys/types.h>
#include <stdio.h>

typedef struct block
{
  short in_use;
  short size;
  struct block* next;
  struct block* prev;
} block_t;



block_t*     un_free(block_t** freelist, int index);
block_t*     add_to_back(block_t** freelist,int index, block_t* node);
void     printListSizes(block_t** freelist);
block_t*     removeNode(block_t** freelist, int index,block_t* node);

extern block_t* freelist[8];


#endif /* __MY_FREE_LIST_H__ */
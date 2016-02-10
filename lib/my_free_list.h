#ifndef __MY_FREE_LIST_H__
#define __MY_FREE_LIST_H__

#include "my_malloc.h"
#include <sys/types.h>
#include <stdio.h>

typedef struct block
{
  int in_use;
  int size;
  struct block* next;
  struct block* prev;
} block_t;



block_t*     un_free(block_t** freelist, int index);
block_t *add_list_last(block_t **freelist, int index, block_t *block_node);



#endif /* __MY_FREE_LIST_H__ */
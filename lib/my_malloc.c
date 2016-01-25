/*
** main.c for libReload in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:48 2015 Pigot Aurélien
** Last update Thu Jan 14 01:10:06 2016 Pigot Aurélien
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include "my_free_list.h"
#include "my_malloc.h"

#define DEFAULT_SIZE 2048

void    *heap;

block_t *freelist[9];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
 * freelist[8] -> 2049+
 */


/**
 * [get_index return index in freelist array for given size]
 * @param  malloc_size size of the block you search in freelist tab
 * @return int block_t array index 
 */
int     get_index(int malloc_size) {
    int index; 

    if (malloc_size > 2048) {
        index = 8;
        return (index);
    }

    index = my_log(2, malloc_size);

    return (index -4);
}


/**
 * [init_heap get first sbrk slice it and create list]
 * @return [description]
 */
void    *init_heap() {
    heap = my_sbrk(DEFAULT_SIZE);
    int i;

    if (heap == NULL)
    {
      return(NULL);
    }

    for(i = 0; i < 8; i++){
      freelist[i] = NULL;
    }

    block_t* heap_block = (block_t*)heap;
    heap_block->in_use = 0;
    heap_block->size = DEFAULT_SIZE;
    heap_block->next = NULL;
    heap_block->prev = NULL;
    freelist[7] = heap_block;

    printf("sizeof heap_block struc %d\n", (int)sizeof(heap_block) );    
    return(heap);
}

void    *my_sbrk(int block_size) {
    void    *res;
    res = sbrk(block_size);

    if(res == (void*)-1) 
    {
            ERRNO=OUT_OF_MEMORY;
            return NULL;
    }

    return (res);
}

void    *my_super_brk(int block_size) {
    void    *res;
    int    index;
    double size;
    size = (double)block_size+sizeof(block_t);
    res = sbrk(size);
    
    if(res == (void*)-1) {
            ERRNO=OUT_OF_MEMORY;
            return NULL;
    }

    if (size > DEFAULT_SIZE){
      index = 9;
    } else {
      get_index(size);
    }

    block_t* heap_block = (block_t*)res;
    heap_block->in_use = 0;
    heap_block->size = block_size;
    heap_block->next = NULL;
    heap_block->prev = NULL;
    freelist[index] = heap_block;

    return (freelist[index]);
}

int     my_log(int n, int b)
{  if (n < b)
   return (0);
 return 1 + my_log(n / b, b);
}

void    *get_block(int index) {
  block_t *my_block;
  if (freelist[index] != NULL) {
     my_block = un_free(freelist, index);
     my_block->in_use = 1;
    
     return (my_block+1);
     
  } else {
    index = get_bigger(index);
    if (index != -1)
    {
       my_block = un_free(freelist, index);
       my_block->in_use = 1;
       return (my_block+1);
    } else {
      /**
       * sbrk a bigger heap and stor it in index 8 of freelist
       * where all block grearter than DEFAULT_SIZE are stored
       */
      return (NULL);
    }
   
  }
}

int    get_bigger(int index, int size) {
  int find_flag;
  int i;
  find_flag = -1;

  for(i = index+1; i < 8; i++){
    if(freelist[i] != NULL && find_flag < 0){
          find_flag = i;
      }
    }

    return(find_flag);
}


void     *my_malloc    (size_t block_size) 
{
  double asked_size;
  int index;
  
  asked_size = (double)(block_size+sizeof(block_t));
  index = get_index(asked_size);


  if (!heap)
  {
    heap = init_heap();
    printf("first use\n");
  }

  printf("heap value %d\n", heap );

  printf("freelist index 7 value %d\n", freelist[7]);

  return (heap);

}



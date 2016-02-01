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

block_t *freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
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

    index = my_log(malloc_size, 2);

    printf("get_index index value %d and asked malloc size is %d\n", index-4, malloc_size );

    return (index-4);
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
    freelist[get_index(DEFAULT_SIZE)] = heap_block;

    printf("sizeof heap_block struc %d\n", (int)sizeof(block_t*) );    
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

/**
 * 
 * @param  int block_size size of the block we need 
 * @return  void*   pointeur to mem block we ask + size of block_t struct 
 * for pointer storage
 */
void    *my_super_brk(int block_size) {
    void    *res;
    int    index;
    double size;
    //size = (double)block_size+sizeof(block_t);
    size = block_size;
    res = sbrk(size);
    
    if(res == (void*)-1) {
            ERRNO=OUT_OF_MEMORY;
            return NULL;
    }

    if (size > DEFAULT_SIZE){
      index = 8;
    } else {
      index = get_index(size);
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

void    *get_block(int index, int size) {
  block_t *my_block;
  block_t *my_new_block;
  int bigindex;
  //check if block of size we need is here
  if (freelist[index] != NULL) {
    printf("*************** get_block check if block of size we need is here\n");
     my_block = un_free(freelist, index);
     my_block->in_use = 1;
    
     return (my_block+1);
     
  } else {
    //else check for bigger one
    bigindex = get_bigger(index);
    if (bigindex != -1)
    {
       my_slice_block(bigindex, index);
    } else {
      /**
       * sbrk a bigger heap and stor it in index 8 of freelist
       * where all block grearter than DEFAULT_SIZE are stored
       */
       my_new_block =  my_super_brk(DEFAULT_SIZE);
       my_slice_block(7, index);
    }
    printf("get_block index is%d\n", index);
    my_block = un_free(freelist, index);
    printf("get_block my_block adresse is %d\n", my_block);
    my_block->in_use = 1;
    ERRNO= NO_ERROR;
    return ((void*)(((char*)my_block)+sizeof(block_t)));
   
  }
}

int    get_bigger(int index) {
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

/**
 *
 * need to finish it, prob with block size of my struct
 */

void my_slice_block(int block_idx, int new_size_idx) {
  int i;
  block_t *bigger;

  printf("my_slice_block block_idx is %d, new_size_idx is %d\n",block_idx, new_size_idx );
  
  for (i = block_idx ; i > new_size_idx; --i)
  {
    bigger = un_free(freelist, i);
    printf("my_slice_block adresse de block_t *bigger: %d loop var i is %d \n", bigger, i);
    //exit(0);
    printf("========= my_slice_block bigger size before /2 %d\n", bigger->size);
    bigger->size /= 2;
    printf("========= my_slice_block bigger size after /2 %d\n", bigger->size);

    //nouvelle moitié
    block_t *new_block = (block_t *)((char *)bigger + bigger->size );
    new_block->size = bigger->size;
    new_block->in_use = 0;
    new_block->next = NULL;
    new_block->prev = bigger;

    add_list_last(freelist, i-1, bigger);
    add_list_last(freelist, i-1, new_block);
    
  }
  printf("OUT my_slice_block \n\n\n");
}


void     *my_malloc    (size_t block_size) 
{
  int asked_size;
  int index;
  void * new_block;
  printf("my_malloc var block_size %d\n", block_size + sizeof(block_t));
  asked_size = (int)(block_size + sizeof(block_t));
  printf("IN malloc asked_size %d\n", asked_size);
  printf("++++++++++++ my_malloc sizeof block_t %d and sizeof var block_size %d\n", sizeof(block_t), sizeof(block_size));

  //if not heap, init it
  if (!heap)
  {
    heap = init_heap();
    my_slice_block(7, 0);
    printf("first use\n");
  }
  index = get_index(asked_size);
  
  new_block = get_block(index, asked_size);

  printf("my_malloc heap value %d\n", heap );

  //printf("my_malloc freelist index value %d AND freelist next is: %d\n", freelist[index], freelist[index]->next);

  printf("my_malloc new_block value is: %d\n", new_block);

  printf("OUT malloc \n\n\n");

  return (new_block);

}



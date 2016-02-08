/*
** main.c for libReload in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:48 2015 Pigot Aurélien
** Last update Mon Feb  8 01:22:32 2016 Pigot Aurélien
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include "my_free_list.h"
#include "my_malloc.h"

#define DEFAULT_SIZE 2048


void    *heap = NULL;

block_t *freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 32
 * freelist[1] -> 64
 * freelist[2] -> 128
 * freelist[3] -> 256
 * freelist[4] -> 512
 * freelist[5] -> 1024
 * freelist[6] -> 2048
 * freelist[7] -> 2049 and more
 */


/**
 * [get_index return index in freelist array for given size]
 * @param  malloc_size size of the block you search in freelist tab
 * @return int block_t array index 
 */
int     get_index(int malloc_size) {
    int index; 

    if (malloc_size <= 32)
        return 0;

    if (malloc_size > DEFAULT_SIZE) {
        index = 7;
        return (index);
    }

    index = my_log(malloc_size-1, 2)+1;

    return (index-5);
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
    heap_block->in_use = -1;
    heap_block->size = DEFAULT_SIZE;
    heap_block->next = NULL;
    heap_block->prev = NULL;
    freelist[get_index(DEFAULT_SIZE)] = heap_block;

    //printf("sizeof heap_block struc %d\n", (int)sizeof(block_t*) );    
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
      index = 7;
    } else {
      index = get_index(size);
    }

    block_t* heap_block = (block_t*)res;
    heap_block->in_use = -1;
    heap_block->size = block_size;
    heap_block->next = NULL;
    heap_block->prev = NULL;

    add_list_last(freelist, index, heap_block);

    return heap_block;
}

int     my_log(int n, int b)
{  if (n < b)
   return (0);
 return 1 + my_log(n / b, b);
}

void      my_memcpy(void *dest, void *src, int size)
{
  char      *ptr_dest;
  char      *ptr_src;
  int     i;

  i = 0;
  ptr_dest = (char *)dest;
  ptr_src = (char *)src;
  while (i < size)
    {
      ptr_dest[i] = ptr_src[i];
      i += 1;
    }
}

void    *my_memset(void *s, char c, int size)
{
  int   i;

  i = 0;
  while (i < size) {
    ((char*) s)[i] = c;
    i++;
  }
  return ((void*)s);
}

void    *get_block(int index, int size) {
  block_t *my_block;
  block_t *my_new_block;
  int bigindex;
  //check if block of size we need is here
  if (freelist[index] != NULL) {
    //printf("*************** get_block check if block of size we need is here\n");
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
       * sbrk a bigger heap and stor it in index 7 of freelist
       * where all block grearter than DEFAULT_SIZE are stored
       */
       //printf("*************** get_block new sbrk \n");
       my_new_block =  my_sbrk(size);
       my_new_block->size = size;
       my_new_block->prev = NULL;
       my_new_block->next = NULL;
       my_new_block->in_use = 1;
       add_list_last(freelist, get_index(size), my_new_block);
       return (my_new_block+1);
    }
    //printf("get_block index is%d\n", index);
    my_block = un_free(freelist, index);
    //printf("get_block my_block adresse is %d\n", my_block);
    my_block->in_use = 1;
    ERRNO= NO_ERROR;
    return (my_block+1);
   
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

  //printf("my_slice_block block_idx is %d, new_size_idx is %d\n",block_idx, new_size_idx );

  
  for (i = block_idx ; i > new_size_idx; --i)
  {
    //printf("========= my_slice_block freelist node is %d AND next is %d \n",freelist[i], freelist[i]->next);
    bigger = un_free(freelist, i);
    //printf("========= my_slice_block adresse de block_t *bigger: %d loop var i is %d \n", bigger, i);
    //exit(0);
    //printf("========= my_slice_block bigger size before /2 %d\n", bigger->size);
    bigger->size /= 2;
    //printf("========= my_slice_block bigger size after /2 %d\n", bigger->size);

    //nouvelle moitié
    //printf("========= my_slice_block decalage %d\n", bigger + bigger->size);
    block_t *new_block = (block_t *)((char *)bigger + bigger->size);
    new_block->size = bigger->size;
    new_block->in_use = -1;
    new_block->next = NULL;
    new_block->prev = NULL;

    bigger->in_use = -1;
    bigger->prev = NULL;
    bigger->next = NULL;

    add_list_last(freelist, i-1, bigger);
    add_list_last(freelist, i-1, new_block);
    
  }
  //printf("OUT my_slice_block \n\n\n");
}


void     *malloc    (size_t block_size) 
{
  int asked_size;
  int index;
  void * new_block;
  block_t *my_new_block;
  //printf("my_malloc var block_size %d\n", block_size + sizeof(block_t));
  asked_size = (int)(block_size + sizeof(block_t));
  //printf("IN malloc asked_size %d\n", asked_size);
  //printf("++++++++++++ my_malloc sizeof block_t %d and sizeof var block_size %d\n", sizeof(block_t), sizeof(block_size));

  //if not heap, init it
  if (!heap)
  {
    heap = init_heap();
    //my_slice_block(7, 0);
    //printf("first use\n");
  }

  if (asked_size > DEFAULT_SIZE)
  {
    my_new_block =  my_sbrk(asked_size);
       my_new_block->size = asked_size;
       my_new_block->prev = NULL;
       my_new_block->next = NULL;
       my_new_block->in_use = 1;
       add_list_last(freelist, get_index(asked_size), my_new_block);
       //freelist[7] = my_new_block;
       return (my_new_block+1);
  }
  index = get_index(asked_size);
  
  new_block = get_block(index, asked_size);

  //printf("my_malloc heap value %d\n", heap );

  //printf("my_malloc freelist index value %d AND freelist next is: %d\n", freelist[index], freelist[index]->next);

  //printf("my_malloc new_block value is: %d\n", new_block);
  //int j;
  /*for ( j = 0; j < 7; ++j)
  {
    printf("freelist index is %d AND value is %d AND next is %d\n",j ,freelist[j], freelist[j]->next);
  }*/

  //printf("OUT malloc \n\n\n");

  return (new_block);

}

void free(void *ptr) {

  block_t *my_block; 
  int index;

  if (!ptr)
    return;

  my_block = (block_t*) ( (char*)ptr - sizeof(block_t) );

  if (my_block->in_use == -1)
    return;

  
  if (my_block->in_use == 1)
  {
    index = get_index(my_block->size);
    my_block->in_use = -1;
    add_list_last(freelist, index, my_block);
    //printf("free ok\n" );
    return ;
  }

  if (my_block->in_use != 1 && my_block->in_use != -1)
    return;

}

void *calloc(size_t count, size_t csize) {
	
  void *new_block;
  size_t total;
  if(count == 0 || csize == 0)
    return (NULL);

  total  = count * csize;
  new_block = malloc(total);

  new_block = my_memset(new_block, 0, total);

  return (new_block);

}

void *realloc(void *ptr, size_t rsize) {
  block_t *my_block;
  void *new_ptr;

  my_block = (block_t*) ((char *) ptr - sizeof(block_t));

  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    //printf("realloc !ptr\n" );
    return malloc(rsize);
  }

  if ((my_block->size) /2 >= rsize) {
    // We have enough space. Could free some once we implement split.
    //printf("my_block->size >= rsize: %d\n", my_block->size /2);
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  //printf("in realloc before malloc\n");
  new_ptr = malloc(rsize);
  if (!new_ptr) {
    //printf("malloc have faild\n");
    return NULL; // TODO: set errno on failure.
  }
  //printf("before memcpy\n");
  my_memcpy(new_ptr, ptr, my_block->size);
  free(ptr);
  return (new_ptr);
}

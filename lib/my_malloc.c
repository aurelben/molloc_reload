/*
** main.c for libReload in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:48 2015 Pigot Aurélien
** Last update Mon Feb  8 11:01:33 2016 Pigot Aurélien
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
  if (freelist[index] != NULL) {
     my_block = un_free(freelist, index);
     my_block->in_use = 1;
    
     return (my_block+1);
     
  } else {
    bigindex = get_bigger(index);
    if (bigindex != -1)
    {
       my_slice_block(bigindex, index);
    } else {
      /**
       * sbrk a bigger heap and stor it in index 7 of freelist
       * where all block grearter than DEFAULT_SIZE are stored
       */
       my_new_block =  my_sbrk(size);
       my_new_block->size = size;
       my_new_block->prev = NULL;
       my_new_block->next = NULL;
       my_new_block->in_use = 1;
       //add_list_last(freelist, get_index(size), my_new_block);
       return (my_new_block+1);
    }
    my_block = un_free(freelist, index);
    my_block->in_use = 1;
    ERRNO= NO_ERROR;
    return (my_block+1);
   
  }
}

int    get_bigger(int index) {
  int find_flag;
  int i;
  find_flag = -1;
  if(index == 7)
    return (find_flag);

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
  
  for (i = block_idx ; i > new_size_idx; --i)
  {
    bigger = un_free(freelist, i);
    //exit(0);
    bigger->size /= 2;

    //nouvelle moitié
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
}

void     *malloc    (size_t block_size) 
{
  int asked_size;
  int index;
  void * new_block;
  block_t *my_new_block;
  asked_size = (int)(block_size + sizeof(block_t));
  if (!heap)
  {
    heap = init_heap();
    //my_slice_block(7, 0);
  }
  
  index = get_index(asked_size);

  if (asked_size > DEFAULT_SIZE)
  {
    if (freelist[index] !=  NULL && freelist[index]->size >= asked_size) {
     my_new_block = un_free(freelist, index);
     my_new_block->in_use = 1;
     printf("HIT\n");
     return (my_new_block+1); 
    }
    my_new_block =  my_sbrk(asked_size);
       my_new_block->size = asked_size;
       my_new_block->prev = NULL;
       my_new_block->next = NULL;
       my_new_block->in_use = 1;
       //add_list_last(freelist, get_index(asked_size), my_new_block);
       return (my_new_block+1);
  }
  new_block = get_block(index, asked_size);

  return (new_block);
}

void free(void *ptr) {

  block_t *my_block; 
  int index;

  if (!ptr)
    return;

  my_block = (block_t*) ( (char*)ptr - sizeof(block_t) );

  if (my_block->in_use == -1) {
    ERRNO = DOUBLE_FREE_DETECTED;
    return;
  }

  
  if (my_block->in_use == 1)
  {
    index = get_index(my_block->size);
    my_block->in_use = -1;
    add_list_last(freelist, index, my_block);
    return ;
  }

  if (my_block->in_use != 1 && my_block->in_use != -1) {
    ERRNO = NO_ERROR;
    return;
  }

}

void *calloc(size_t count, size_t csize) {
	
  void *new_block;
  size_t total;
  if(count == 0 || csize == 0)
      return (NULL);

  total  = count * csize;
  new_block = malloc(total);

  if (!new_block)
    return (NULL);

  new_block = my_memset(new_block, 0, total);

  return (new_block);

}

void *realloc(void *ptr, size_t rsize) {
  block_t *my_block;
  void *new_ptr;

  my_block = (block_t*) ((char *) ptr - sizeof(block_t));

  if (!ptr) {
    // NULL ptr. realloc should act like malloc.
    return (malloc(rsize));
  }

  if (((unsigned)((my_block->size) /2)) >= rsize) {
    return ptr;
  }

  // Need to really realloc. Malloc new space and free old space.
  // Then copy old data to new space.
  new_ptr = malloc(rsize);
  if (!new_ptr) {
    return (NULL);
  }
  my_memcpy(new_ptr, ptr, my_block->size);
  free(ptr);
  return (new_ptr);
}

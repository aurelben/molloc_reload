#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include "my_malloc.h"
#include <sys/types.h>
#include <stdio.h>

enum my_malloc_err {
	NO_ERROR,
	OUT_OF_MEMORY,
	SINGLE_REQUEST_TOO_LARGE,
	DOUBLE_FREE_DETECTED
};
enum my_malloc_err ERRNO;

int     my_log(int n, int b);
void*    malloc(size_t);
void*    my_memory_move(void* dest, const void* src, size_t num_bytes);
void* 	 init_heap();
void* 	 my_sbrk(int block_size);
int     get_index(int malloc_size);
void    *get_block(int index, int size);
int    get_bigger(int index);
void my_slice_block(int block_idx, int new_size_idx);
void free(void *ptr);
void *realloc(void *ptr, size_t rsize);
void *calloc(size_t count ,size_t csize);
void      my_memcpy(void *dest, void *src, int size);
void    *my_memset(void *s, char c, int size);
void	my_put_nbr(int n);
void	my_putstr(char *str);

#endif /* __MY_MALLOC_H__ */

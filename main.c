/*
** main.c for libReload in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:48 2015 Pigot Aurélien
** Last update Mon Feb  8 00:40:01 2016 Pigot Aurélien
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main (void) 
{
  int log_res;
  //void *res;
  void *tmp;
  void *tmp2;
  void *addr_tmp;
  
  log_res = my_log(16, 2);		
  printf("testing my log2 %d \n", log_res );

  printf("testing my log2 %d \n", my_log(536, 2) );

  //void *malloc_res;
  
  int i;
  for (i = 0; i < 50000; ++i)
  {
  	printf("--------------------------ROUND %d----------------------------------\n", i);
		tmp = my_malloc(6400);
    addr_tmp = &tmp;
                printf("memset FIRST\n");
                memset(tmp, '$', 6400);
                //printf("memset FIRST res is: %s\n", (char*)tmp);     
    my_free(tmp);      
		tmp = my_realloc(tmp,2000);
		memset(tmp, '$', 2000);
                my_free(tmp);
              
		printf("------------------------------------------------------------\n");
    tmp2 = my_malloc(i);
                printf("memset BIG\n");
                memset(tmp2, '$', i);
    //tmp2 = my_realloc(tmp2, 64);
    //memset(tmp2, '$', 64);
                //printf("memset BIG res is: %s\n", (char*)tmp2);
                my_free(tmp2);

    printf("------------------------------------------------------------\n");
                printf("FUCK FREE TEST\n");
                my_free(tmp);
                my_free(addr_tmp);
    printf("------------------------------------------------------------\n");          
    void * tmp_calloc;
    tmp_calloc = my_calloc(8,64);
    memset(tmp_calloc, '$', 64);
    my_free(tmp_calloc);
    printf("memset CALLOC\n");
                //printf("memset res is: %s\n", (char*)res);
		printf("------------------------------------------------------------\n");
  }
  
  printf("END ------------------ testing my_malloc\n");
  return (0);
}

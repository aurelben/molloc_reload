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
#include <string.h>
#include "main.h"

int main (void) 
{
  int log_res;
  //void *res;
  void *tmp;
  
  log_res = my_log(16, 2);		
  printf("testing my log2 %d \n", log_res );

  printf("testing my log2 %d \n", my_log(536, 2) );

  //void *malloc_res;
  
  int i;
  for (i = 0; i < 800; ++i)
  {
  	printf("--------------------------ROUND %d----------------------------------\n", i);
		tmp = my_malloc(64);
                printf("memset 1\n");
                memset(tmp, '$', 32);
                //printf("memset res is: %s\n", (char*)res);
		printf("------------------------------------------------------------\n");
		tmp = my_malloc(64);
                memset(tmp, '$', 32);
                printf("memset 2\n");
                //printf("memset res is: %s\n", (char*)res);
		printf("------------------------------------------------------------\n");
  }
  
  printf("END ------------------ testing my_malloc\n");
  return (0);
}

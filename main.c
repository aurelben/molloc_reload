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
  //void *res;
  void *tmp;
  
  
  int i;
  for (i = 0; i < 8000; ++i)
  {
  	my_putstr("--------------------------ROUND");
    my_put_nbr(i);
    my_putstr("----------------------------------\n");
		tmp = malloc(3000);
                printf("memset FIRST\n");
                memset(tmp, '$', 3000);
	        tmp = realloc(tmp,4000);
		memset(tmp, '$', 2000);
                free(tmp);
              
		my_putstr("------------------------------------------------------------\n");
                void *tmp2;
                tmp2 = malloc(1024);
                my_putstr("memset BIG \n");
                memset(tmp2, '$', 1024);
                free(tmp2);
    my_putstr("------------------------------------------------------------\n");          
    void * tmp_calloc;
    tmp_calloc = calloc(8,64);
    memset(tmp_calloc, '$', 64);
    free(tmp_calloc);
    my_putstr("memset CALLOC\n");
		my_putstr("------------------------------------------------------------\n");
  }
  
  my_putstr("END ------------------ testing my_malloc\n");
  return (0);
}

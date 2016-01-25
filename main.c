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
#include "main.h"

int main (void) 
{
  int log_res;
  
  log_res = my_log(16, 2);		
  printf("testing my log2 %d \n", log_res );

  printf("testing my log2 %d \n", my_log(32, 2) );

  //void *malloc_res;

  my_malloc(512);

  my_malloc(1024);
  printf("testing my_malloc\n");
  return (0);
}

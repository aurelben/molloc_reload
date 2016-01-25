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
#include "my_free_list.h"



block_t*  un_free(block_t** freelist, int index){
	block_t* head = freelist[index];
	//really simple
	freelist[index] = head->next;
	if(((block_t*)freelist[index])!=NULL){
		((block_t*)freelist[index])->prev = NULL;
	}
	head->next = NULL;
	head->prev = NULL;
	return head;
}

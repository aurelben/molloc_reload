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


//remove head
block_t *un_free(block_t **freelist, int index){
	//printf("un_free var int index is %d\n", index);

	block_t* head = freelist[index];

	//printf("un_free var block_t head is %d AND head->next is: %d\n", head, head->next);
	//really simple
	freelist[index] = head->next;
	if(((block_t*)freelist[index])!=NULL){
		((block_t*)freelist[index])->prev = NULL;
	}
	head->next = NULL;
	head->prev = NULL;
	//printf("OUT OF UN_FREE\n\n");
	return head;
}

//add to back
block_t *add_list_last(block_t **freelist, int index, block_t *block_node){
	block_t *block_list = freelist[index];

	if (block_list == NULL)
	{
		freelist[index] = block_node;
		block_node->next = NULL;
		block_node->prev = NULL;

		return (block_node);
	}

	block_t *safe_copy =  block_list;

	while( safe_copy->next != NULL) {
		safe_copy = safe_copy->next;
	}
	safe_copy->next = block_node;
	block_node->prev = safe_copy;
	block_node->next = NULL;

	return (block_node);

}
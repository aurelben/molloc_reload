/*
** libParse.h for libParse in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:12 2015 Pigot Aurélien
** Last update Wed Apr 29 13:39:13 2015 Pigot Aurélien
*/


#ifndef LIBPARSE_H__
# define LIBPARSE_H__
#include "lib_list.h"

void add_option(sll_s *p_sll, void *option, int is_required, void *data);
void **validate_options(int opt_c, char *option[], sll_s *optionList);
void *check_option(char *option, sll_s *optionList);
int is_required(int opt_c, char *option[], sll_s *optionList);


#endif /* !LIBPARSE_H__ */

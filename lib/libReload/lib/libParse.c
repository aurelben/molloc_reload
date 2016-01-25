/*
** libParse.c for libParse in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:21:39 2015 Pigot Aurélien
** Last update Wed Apr 29 14:23:07 2015 Pigot Aurélien
*/


#include "../lib.h"
#include "../lib_list.h"

void add_option(sll_s *p_sll, void *option, int is_required, void *data)
{
  if (sizeof(p_sll) > 0) {
    sll_insert (p_sll, data, option, is_required);
  } else {
    my_error("pleas use a valid generic option list");
  }
}

void **validate_options(int opt_c, char *option[], sll_s *optionList)
{
  int i;
  void *tmp;
  void **res;
  if(is_required(opt_c, option, optionList) == 0)
    return;
  my_putstr("req options are ok \n");
  for(i = 0; i < opt_c; i++) {
    tmp = (char*)check_option(option[i], optionList);
    if(tmp != NULL)
      {
      my_putstr("option ok \n");
      void *(*tmp) (char*);
      tmp = sll_data(optionList);
      tmp ("a dumb mess");
      my_putstr("\n");
      //res[i] = tmp;
      }
  }
  return (res);
}

void *check_option(char *option, sll_s *optionList) 
{
  sll_first(optionList);
  char *tmp;
  while (sll_key(optionList) != NULL)
    {
      tmp = (char*)sll_key(optionList);
      if (my_strcmp(option, tmp)  == 0 )
	{
	  return (sll_data(optionList));
	} else {
      sll_next (optionList);
      }
    }
  my_putstr("entry notre found in the option list\n");
  return;
}

int is_required(int opt_c, char *option[], sll_s *optionList)
{
  int i;
  int j;
  int req_opt_count;
  sll_first(optionList);
  j = 0;
  req_opt_count = 0;
  while(sll_key(optionList) != NULL)
    { 
      if(sll_is_req(optionList) == 1) {
	req_opt_count++;
	for(i = 0; i < opt_c ;  i = i + 1) {
	  if(my_strcmp((char*)sll_key(optionList), option[i]) == 0)
	    j++;
	  }
	}
      sll_next(optionList);
    }
  if(req_opt_count == 0)
      return (1);

  if(j != req_opt_count) {
    my_putstr("a required option is missing \n");
    return (0);
  }
  return (1);
}


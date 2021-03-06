#include "../lib.h"
#include "../lib_list.h"



void add_option(sll_s *p_sll, void *option, int is_required, void *data)
{
  if (sizeof(p_sll) > 0) {
  sll_insert (p_sll, option, data, is_required);
  } else {
    my_error("add_option: pleas use a valid generic option list");
  }
}

void **validate_options(char **option, sll_s *optionList)
{
  int i;
  void *tmp;
  void ** res;
  if(is_required(option, optionList) == 0)
    return;
  for(i = 0; option, option++, i++) {
    tmp = check_option(option, optionList);
    if(tmp != NULL)
      res[i][] = tmp;
  }
  return (res);
  
}

void *check_option(char *option, sll_s *optionList) 
{
  sll_first(optionList);
  char *tmp;
  while (optionList->list != NULL)
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

int is_required(char **option, sll_ *optionList)
{
  int i;
  int j;
  sll_first(optionList);
  while(optionList->list != NULL)
    { 
      if(sll_isreq(optionList) == 1) {
	for(i = 0; option; option++, i++) {
	  if(my_strcmp((char*)sll_key(optionList), option[i][0]) != 0){
	    my_putstr("a required option is missing");
	    return (0)
	      }
	}
      } 
      sll_next(optionList);
    }
  return (1);
}


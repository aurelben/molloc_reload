/***
** option.c
** Last update Wed Apr 29 22:26:54 2015 Pigot Aurélien
****/
#include "option.h"
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char        *readLine()
{
  ssize_t   ret;
  char      *buff;

  if ((buff = malloc(sizeof(*buff) * (250 + 1))) == NULL)
    return (NULL);
  if ((ret = read(0, buff, 250)) > 1)
  {

    buff[ret - 1] = '\0';
    return (buff);
  }
  buff[0] = '\0';
  return (buff);
}

void	error_entry_message()
{
   my_putstr(" \e[31m\nInvalid input\nplease type a valid command type usage for show commande\n\n\e[0m");
    my_putchar('\n');
}

int    read_entry(char *rln)
{
  int i;
  char *commands[] = {"/bye", "/auth", "/list", "/hs", "/psychohistory", 
                      "/getstatus", "/me", "/setstatus"};
  int returns[] = {-1, 1, 2, 3, 4, 5, 6, 7};
  char **wordtab;
  char *tmp;
  if(if_null_entry(rln) == 0){
    my_putstr("<<<<< Entry is NULL safe exit >>>>>\n");
    return (-1);
  }
  my_strtolower(rln);
  tmp = rln;
  wordtab = my_str_to_wordtab(tmp);
  for (i = 0; i < 8; ++i)
    {
    if (my_strcmp(wordtab[0], commands[i]) == 0)
      {
	// free(wordtab);
        return (returns[i]);
      }
    }
  if (my_strcmp(my_strupcase(rln), "usage") == 0)
     {
         printf("<<<<< Usages here >>>>>\n");
         return (8);
     }
   error_entry_message();
  //free(wordtab);
  return (0);
}


int    read_option(char *argoption, char *argval)
{
  if (isoption_ok(argoption, argval) == 1)
    {
      return (1);
    }else
    return (0);
}

int    isoption_ok(char *option, char *val)
{
  char *validOption[] = {
    "--ip", "--port"
  };
  int j;
  my_putstr(val);
  my_putstr("\n");

  j = 0;
  while(j < 2){
    if(my_strcmp(validOption[j], option) != 0){
      //       my_putstr("Option is not valid \n");
       j++;
       continue;}
    if(my_strcmp(validOption[j], option) == 0)
      {
        my_putstr("Option is valide \n");
	//check the option value
        // for(i = 0; val[i]; i++ ){
        //   if(char_isnum(val[i]) == 0)
        //     {
        //       if(val[i] != '.'){
        //       my_putstr("Value is not valid ... \n");
        //       return (0);}
        //     }
        // }
        // my_putstr("Value is valid \n");
        return (1);
	}
    j++;
  }
  my_putstr("Option is not valid end \n");
  return (0);
}

int     char_isnum(char c)
{
  if (c >= '0' && c <= '9')
    return (1);
  else
    return (0);
}

int if_null_entry(char *entry){
  if(entry == NULL)
    return (0);
  else
    return (1);
}

int check_option(int argc, char **argv) {
  char *option;
  int i;
  char *val;
   if(argc != 5) {
    my_putstr("Pleas use commandes --ip[ip] --port[port] \n");
    return (0);
    }
    for(i = 1; argv[i]; i = i + 2 ){
      option = argv[i];
      val = "q";
      if(argv[i+1])
         val = argv[i+1];
      if (read_option(option, val) != 1 ) {
        my_putstr("\e[31m\n is not a valid option. pleas use --ip[ip] --port[port]\n\n\e[0m");
          return (0);
      }
    }
}

int prompt_loop () 
{
  char *entry;
  int readEntry;
  do
    {
      my_putstr("Prompt-> ");
      entry = readLine();
      readEntry = read_entry(entry);
      if (readEntry == -1)
      {
        my_putstr("\nyou are living \n");
        close(sock);
        free(entry);
        return (0);
      }
      if(readEntry == 0)
      {
        error_entry_message();
      }else{
      

    }while(readEntry != -1);
    free(entry);
  return (1);
}

/*
** my_strdup.c for my_strdup in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Mon Oct 27 16:40:36 2014 Pigot Aurélien
** Last update Sat Feb 14 20:19:51 2015 Pigot Aurélien
*/

#include <stdlib.h>

int       my_strlen(char*);
char      *my_strcpy(char*, char*);

char      *my_strdup(char *str)
{
  int     len;
  char    *dup;

  len = my_strlen(str);
  dup = malloc(len * sizeof(char));
  return (my_strcpy(dup, str));
}

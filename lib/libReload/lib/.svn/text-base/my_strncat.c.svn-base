/*
** my_strncat.c for my_strncat in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 10:33:57 2014 Pigot Aurélien
** Last update Sat Feb 14 20:55:39 2015 Pigot Aurélien
*/

int       getlen(char *str)
{
  int     i;

  i = 0;
  while (*str)
  {
    str++;
    i++;
  }
  return (i);
}

char      *my_strncat(char *str1, char *str2, int n)
{
  char    *ret;

  ret = str1;
  while (*str1)
    str1++;

  while (*str2 && n > 0)
  {
    *str1 = *str2;
    str1++;
    str2++;
    n--;
  }
  return (ret);
}

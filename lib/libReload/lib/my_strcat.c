/*
** my_strcat.c for my_strcat in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 10:01:51 2014 Pigot Aurélien
** Last update Sat Feb 14 20:14:01 2015 Pigot Aurélien
*/

char      *my_strcat(char *str1, char *str2)
{
  char    *ret;

  ret = str1;
  while (*str1)
    str1++;

  while (*str2)
  {
    *str1 = *str2;
    str1++;
    str2++;
  }
  return (ret);
}

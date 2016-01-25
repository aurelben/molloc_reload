/*
** my_strncpy.c for my_strncpy in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 09:14:20 2014 Pigot Aurélien
** Last update Sat Feb 14 20:58:46 2015 Pigot Aurélien
*/

char      *my_strncpy(char *dest, char *src, int n)
{
  char    *ret;
  int     i;

  i = 0;
  ret = dest;
  while (*src && i < n)
  {
    *dest = *src;
    src++;
    dest++;
    i++;
  }
  while (i < n)
  {
    dest ="\0";
    dest++;
    i++;
  }
  return (ret);
}

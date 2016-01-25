/*
** my_strncmp.c for my_strncmp in /home/
**
** Made by Pigot Aurélie
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 09:55:51 2014 Pigot Aurélie
** Last update Sat Feb 14 20:57:57 2015 Pigot Aurélien
*/

int       my_strncmp(char *s1, char *s2, int n)
{
  while (*s1 && n > 0)
  {
    if (*s1 < *s2)
      return (-1);
    else if (*s1 > *s2)
      return (1);
    s1++;
    s2++;
    n--;
  }
  if (n == 0 || (*s1 == '\0' && *s2 == '\0'))
    return (0);
  else
    return (-1);
}

/*
** my_strcmp.c for my_strcmp in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 09:43:03 2014 Pigot Aurélien
** Last update Sat Feb 14 20:16:05 2015 Pigot Aurélien
*/

int       my_strcmp(char *s1, char *s2)
{
  while (*s1)
  {
    if (*s1 < *s2)
      return (-1);
    else if (*s1 > *s2)
      return (1);
    s1++;
    s2++;
  }
  if (*s1 == '\0' && *s2 == '\0')
    return (0);
  else
    return (-1);
}

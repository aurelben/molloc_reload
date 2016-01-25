/*
** my_strstr.c for my_strstr in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Thu Oct 23 11:34:23 2014 Pigot Aurélien
** Last update Sat Feb 14 21:02:42 2015 Pigot Aurélien
*/

int       check_needle(char *hay, char *needle)
{
  while (*needle)
  {
    if (*needle != *hay)
      return (1);
    needle++;
    hay++;
  }
  return (0);
}

char      *my_strstr(char *str, char *to_find)
{
  if (*to_find == '\0')
    return (str);
  while (*str)
  {
    if (*str == *to_find && check_needle(str, to_find) == 0)
    {
      return (str);
    }
    str++;
  }
  return ("null");
}

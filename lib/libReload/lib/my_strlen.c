/*
** my_strlen.c for my strlen in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Wed Oct 22 12:06:30 2014 Pigot Aurélien
** Last update Sat Feb 14 20:54:03 2015 Pigot Aurélien
*/

int   my_strlen(char *str)
{
  int i;

  i = 0;
  while (*str != '\0')
    {
      i++;
      str++;
    }
  return (i);
}

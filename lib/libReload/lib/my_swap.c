/*
** my_swap.c for my swap in /home/
**
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Wed Oct 22 12:00:36 2014 Pigot Aurélien
** Last update Sat Feb 14 21:05:50 2015 Pigot Aurélien
*/

void    my_swap(int *a, int *b)
{
  int   tmp;

  tmp = *b;
  *b = *a;
  *a = tmp;
}

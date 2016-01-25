/*
** my_aff_tab.c for my aff tab in /home/
** 
** Made by pigot_a
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Tue Oct 21 09:16:21 2014 pigot_a
** Last update Sat Feb 14 19:47:23 2015 Pigot Aurélien
*/
#include <unistd.h>

void	my_putstr(char *str);
void	my_put_nbr(int n);
int	calc_diviser(int n)
{
  int	diviser;

  diviser = 1;
  while (n > 10)
    {
      n = n / 10;
      diviser = diviser * 10;
    }
  return (diviser);
}

void	my_aff_tab(int *tab, int len)
{
  int	i;

  i = 0;
  while (i < len)
    {
      my_put_nbr(*tab);
      write(1, "\n", 1);
      tab++;
      i++;
    }
}

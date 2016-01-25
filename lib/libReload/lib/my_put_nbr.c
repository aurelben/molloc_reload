/*
** my_put_nbr.c /my_put_nbr
**
** Made by pigot_a
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Mon Oct 20 14:36:12 2014 pigot_a
** Last update Sat Feb 14 19:33:40 2015 Pigot Aurélien
*/
#include <unistd.h>

void	my_putstr(char *str);
int	calc_nbr_diviser(int n)
{
  int	diviser;

  diviser = 1;
  while ((n / diviser) >= 10)
    {
      diviser = diviser * 10;
    }
  return (diviser);
}

void	my_put_nbr(int n)
{
  int	diviser;
  char	c;

  if (n == -2147483648)
    {
      my_putstr("-2147483648");
      return;
    }
  if (n < 0)
    {
      n = n * -1;
      write(1, "-", 1);
    }
  diviser = calc_nbr_diviser(n);
  while (diviser > 0)
    {
      c = n / diviser + 48;
      n = n % diviser;
      diviser = diviser / 10;
      write(1, &c, 1);
    }
}

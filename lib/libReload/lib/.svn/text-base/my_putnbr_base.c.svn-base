/*
** my_putnbr_base.c for my putnbr base in /home
**
** Made by pigot_a
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Fri Oct 24 14:12:04 2014 pigot_a
** Last update Sat Feb 14 20:10:06 2015 Pigot Aurélien
*/
#include <unistd.h>

void    my_putstr(char *str);

int     getbaselen(char  *base)
{
  int   i;

  i = 0;
  while (*base)
  {
    base++;
    i++;
  }
  return (i);
}

char*    put_base(int number, char *base)
{
  char   c;

  c = base[number];
  write(1, &c, 1);
  return (base);
}

int     calc_div(int n, char *base)
{
  int   diviser;
  int   base_len;

  diviser = 1;
  base_len = getbaselen(base);
  while ((n / diviser) >= base_len)
    {
      diviser = diviser * base_len;
    }
  return (diviser);
}

void    my_putnbr_base(int n, char *base)
{
  int   diviser;
  int   base_len;
  char  c;

  if (n < 0)
    {
      n = n * -1;
      write(1, "-", 1);
    }
  diviser = calc_div(n, base);
  base_len = getbaselen(base);
  while (diviser > 0)
    {
      c = (n / diviser) % base_len;
      put_base(c, base);
      diviser = diviser / base_len;
    }
}

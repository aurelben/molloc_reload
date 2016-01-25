/*
 ** my_getnbr.c for my getnbr in /home/vagrant/projects/piscine/devc/jour03/diallo_l/my_getnbr
 **
 ** Made by DIALLO Leny
 ** Login   <diallo_l@etna-alternance.net>
 **
 ** Started on  Wed Oct 22 12:09:12 2014 DIALLO Leny
 ** Last update Wed Oct 22 13:17:17 2014 DIALLO Leny
 */

int     valid(char *str)
{
  int   i;

  i = 0;
  while (*str != '\0')
  {
    if (*str >= '0' && *str <= '9')
      return (i);
    else if ((*str < '0' || *str > '9') && *str != '+' && *str != '-')
      return (-1);
    i++;
    str++;
  }
  return (-1);
}

int     get_len(char *str, int pos)
{
  int   i;

  i = 0;
  while (str[pos] != '\0')
  {
    if (str[pos] < '0' || str[pos] > '9')
      return (i);
    i++;
    pos++;
  }
  return (i);
}

int     diviser(int mul)
{
  int   div;

  div = 1;
  while (mul > 1)
  {
    div = div * 10;
    mul--;
  }
  return (div);
}

int     convertnbr(char *str, int pos, int diviser)
{
  int   result;

  result = 0;
  while (diviser >= 1)
  {
    result = result + ((str[pos] - 48) * diviser);
    diviser = diviser / 10;
    pos++;
  }
  return (result);
}

int     my_getnbr(char *str)
{
  int   pos;
  int   sign;
  int   div;
  int   i;

  pos = valid(str);
  if (pos == -1)
    return (0);
  sign = 0;
  i = 0;
  if (pos > 0)
  {
    while (i < pos)
    {
      if (str[i] == '-')
        sign++;
      i++;
    }
    sign = sign % 2 == 1;
  }
  div = diviser(get_len(str, pos));
  if (sign == 1)
    return (convertnbr(str, pos, div)) * -1;
  return (convertnbr(str, pos, div));
}

/*                                                                                                                                                                                
** my_strupcase.c for my_strupcase in /home/pigot_a/piscine/c/jour02/pigot_a/my_strupcase                                                                                         
**                                                                                                                                                                                
** Made by PIGOT Aurélien                                                                                                                                                         
** Login   <pigot_a@etna-alternance.net>                                                                                                                                          
**                                                                                                                                                                                
** Started on  Tue Oct 21 16:35:36 2014 PIGOT Aurélien                                                                                                                            
** Last update Tue Oct 21 18:20:49 2014 PIGOT Aurélien                                                                                                                            
*/

void    my_putchar(char c);


char    *my_strupcase(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
    {
      if ((str[i] >= 'a') && (str[i] <= 'z'))

          str[i] = str[i] - 32;

      i = i + 1;
    }
  return (str);
}

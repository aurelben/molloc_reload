/*
** lib.h for my lib in /lib/
**
** Made by pigot_a
** Login   <pigot_a@etna-alternance.net>
**
** Last update Sun Apr 26 13:57:03 2015 Pigot Aurélien
*/
#ifndef LIB_H__
# define LIB_H__

#include "libError.h"
#include "libParse.h"

void	my_putchar(char c);

void    my_put_nbr(int n);

void    my_putstr(char *str);

int     my_getnbr(char *str);

char    *readLine();

char    *my_strupcase(char *str);

char    *my_strtolower(char *str);

char    **my_str_to_wordtab(char *str);

int     my_strcmp(char *s1, char *s2);

void    my_aff_tab(int *tab, int len);

int     my_isneg(int n);

char    *my_memset(char *s, char c, int size);

void    my_putnbr_base(int n, char *base);

char    *my_strcat(char *str1, char *str2);

char    *my_strcpy(char *dest, char *src);

char    *my_strdup(char *str);

int	my_strlen(char *str);

char    *my_strncat(char *str1, char *str2, int n);

int     my_strncmp(char *s1, char *s2, int n);

char    *my_strncpy(char *dest, char *src, int n);

char    *my_strstr(char *str, char *to_find);

void    my_swap(int *a, int *b);

#endif /* !LIB_H__ */

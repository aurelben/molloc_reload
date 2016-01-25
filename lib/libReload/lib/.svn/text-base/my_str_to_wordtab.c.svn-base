/*
** my_str_to_wordtab.c for my_str_to_wordtab in 
**
** Made by Pigot Aurelien
** Login   <pigot_a@etna-alternance.net>
**
** Started on  Mon Oct 27 16:52:13 2014 Pigot Aurelien
** Last update Mon Jan 26 10:15:33 2015 Pigot Aurélien
*/
#include <stdlib.h>

typedef   struct Word Word;
struct    Word
{
  int     len;
  char    *start;
  char    *end;
};

int       my_strlen(char*);
char      *my_strncpy(char*, char*, int);

int       my_isalphanum(char c)
{
  if (c >= '0' && c <= '9')
    return (0);
  if (c >= 'a' && c <= 'z')
    return (0);
  if (c >= 'A' && c <= 'Z')
    return (0);
  if (c == '/')
    return (0);  
  return (-1);
}

int       count_word(char *str)
{
  int     ct;
  int     in;
  int     is_alpha;

  ct = 0;
  in = 0;
  while (*str)
  {
    is_alpha = my_isalphanum(*str);
    if (is_alpha == 0 && in == 0)
    {
      ct++;
      in = 1;
    }
    else if (is_alpha == -1 && in == 1)
      in = 0;
    str++;
  }
  return (ct);
}

void      init_word(Word *word, char *str)
{
  word->len   = 0;
  word->start = str;
  while (my_isalphanum(*str) == 0)
  {
    word->len++;
    str++;
  }
  word->end   = str;
}

void      populate(Word *word, char **tab, int index)
{
  tab[index] = malloc(sizeof(char) * word->len);
  my_strncpy(tab[index], word->start, word->len);
  
}

char      **my_str_to_wordtab(char *str)
{
  Word    *word;
  char    **tab;
  int     nb_words;
  int     it;

  it = 0;
  word = malloc(sizeof(Word));
  nb_words = count_word(str);
  tab = malloc(sizeof(char*) * nb_words + 1);
  tab[nb_words] = "\0";
  while (*str)
  {
    if (my_isalphanum(*str) == 0)
    {
      init_word(word, str);
      populate(word, tab, it);
      it++;
      str = word->end;
    }
    else
      str++;
  }
  free(word);
  return (tab);
}

/*
** lib_list.h for lib_list in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:29:25 2015 Pigot Aurélien
** Last update Wed Apr 29 13:29:29 2015 Pigot Aurélien
*/


#ifndef LIB_LIST_H__
# define LIB_LIST_H__
#include <stddef.h>             /* pour size_t */

typedef struct sll sll_s;

sll_s *sll_new (void);
void sll_insert (sll_s *, void *, void *, int);
void sll_removeNext (sll_s *);
void sll_removeFirst (sll_s *);
void sll_next (sll_s *);
void *sll_data (sll_s *);
void *sll_key (sll_s *);
int  sll_is_req (sll_s *);
void sll_first (sll_s *);
void sll_last (sll_s *);
size_t sll_sizeof (sll_s *);
void sll_delete (sll_s **);


#endif /* !LIB_LIST_H__ */

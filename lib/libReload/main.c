/*
** main.c for libReload in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:39:48 2015 Pigot Aurélien
** Last update Wed Apr 29 22:21:37 2015 Pigot Aurélien
*/


#include <stdio.h>
#include <stdlib.h>
#include "lib_list.h"
#include "lib.h"

static void list_print (sll_s *);
void test_error();
void test_libParse();
void *useless(char *message);
//void *(*ptr_useless) (*char);

int main (void)
{
  sll_s *p_sll = NULL;
  char text[][6] = { "Hello", "le ", "World", "!" };
  char key[][6] = { "-v", "-r", "", "-w" }; 
  my_putstr("\t-- List Initialisation --\n");
  p_sll = sll_new ();
  list_print (p_sll);

  my_putstr("\n\t-- List data Insertion --\n");

    int i;
    int j;
    int k;
    for (j = 0; j < 11; j++) {
    for (i = 0; i < 4; i++)
      {
	sll_insert (p_sll, text[i], key[i], j);
      }
    }

  list_print (p_sll);
 
  for (k = 0; k < 5; k++ ) 
    {
      my_putstr ("\n\t-- List node Suppression --\n");
      sll_removeFirst (p_sll);
      my_putstr("Node is distroyed\n");
      sll_first(p_sll);
      my_putstr((char*)sll_data(p_sll));
    }

  my_putstr("\n\t-- List Destruction --\n");
  sll_delete (&p_sll);
  my_putstr("\n\t-- New list print try --\n\n");
  list_print (p_sll);
  my_putstr("List is distroyed\n\n");
  test_error();
  test_libParse();
  return EXIT_SUCCESS;
}

void test_error () 
{
  my_putstr("\t-- Generate fopen error for testing libError --\n");
  int fd;
  fd = my_fopen("::/", O_APPEND, 0777);
  if (fd < 0)
    {
      my_error("canot open file");
    }
}

void test_libParse() 
{
  sll_s *p_sll;
  p_sll = NULL;
  p_sll = sll_new();
  char *arg1;
  char *arg2;
  char *arg3;
  char *fake_option[3];
  void *(*ptr_useless) (char*);
  ptr_useless = &useless;
  arg1 = "-v";
  arg2 = "-o";
  arg3 = "-w";
  fake_option[0] = arg1;
  fake_option[1] = arg2;
  fake_option[2] = arg3;
  my_putstr("\t-- adding options --\n");
  add_option(p_sll, "-o", 1, ptr_useless);
  add_option(p_sll, "-z", 0, "option is -z");
  add_option(p_sll, "all", 0, "option is all");
  my_putstr("\t-- options added -- \n\n\t -- validate  options --\n");
  validate_options(3,fake_option, p_sll);
  sll_delete(&p_sll);
}




static void list_print (sll_s * p_l)
{
  int i;
  int size = sll_sizeof (p_l);

  sll_first (p_l);
  for (i = 0; i < size; i++)
    {
      if (sll_data(p_l) != NULL && sll_key(p_l) != NULL)
	{
	  my_putstr("Data: ");
	  my_putstr((char *) sll_data (p_l));
	  my_putstr("\nKey: ");
	  my_putstr((char *) sll_key(p_l));
	  my_putstr("\nIs_req: ");
	  my_put_nbr (sll_is_req(p_l));
	  my_putstr("\n");
	}
      sll_next (p_l);
    }
  my_putstr ("\n");
}

void *useless (char *message)
{
  void *my_void;
  my_void = NULL;
  my_putstr("Iam a useless function, i'am printing a message \n");
  my_putstr(message);
  return my_void;
}

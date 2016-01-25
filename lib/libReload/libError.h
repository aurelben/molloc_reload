/*
** libError.h for libError in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:38:52 2015 Pigot Aurélien
** Last update Wed Apr 29 13:38:54 2015 Pigot Aurélien
*/


#ifndef LIBERROR_H__
# define LIBERROR_H__
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

int my_error (char *message);
void log_error(char *message);
int my_fopen (char *path, int access, int right);
int my_fputs(char *txt, int file);


#endif /* !LIBERROR_H__ */

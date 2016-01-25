#include <stdio.h>
#include <errno.>
#include "lib.h"

int my_error (int errno, char *message) 
{
  if(errno && message) 
    {
    my_putstr("Errno value: ");
    my_put_nbr(errno);
    my_putstr("\n");
    perror(message);
    return (1);
    }
  return (0);
}

void log_error(int errno, char *message) 
{
  int file;

  file = fopen("error.log", "w");
  file = fopen("error.log", "a");
  if (file > 0)
    {
    fputs (message, file);
    fputs (" ");
    fputs (errno, file);
    fputs ("\n");
    fclose(file);
    } else {my_putstr("log file cannot be wrtien")}
}

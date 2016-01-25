/*
** libError.c for libError in /home/aurel/libReload
** 
** Made by Pigot Aurélien
** Login   <pigot_a@etna-alternance.net>
** 
** Started on  Wed Apr 29 13:38:22 2015 Pigot Aurélien
** Last update Wed Apr 29 13:38:27 2015 Pigot Aurélien
*/

#include "../lib.h"

int my_error(char *message)
{
  if(message) 
    {
    my_putstr("Errno value: ");
    my_putstr("\n");
    perror(message);
    log_error(message);
    return (1);
    }
  return (0);
}

void log_error(char *message) 
{
  int file;
  time_t rowtime;
  time(&rowtime);
  file = my_fopen("error.log", O_APPEND, 0777);
  if(file == 0)
    {
    my_putstr("log file can't be writed");
    return;
    }
  my_fputs(ctime(&rowtime), file);
  my_fputs (message, file);
  my_fputs(": ", file);
  my_fputs(strerror(errno), file);
  my_fputs ("\n", file);
  close(file);

}

int my_fopen (char *path, int access, int right)
{ 

  int fd;
  fd = open(path, access|O_CREAT|O_RDWR, right);
  return (fd);
}

int my_fputs(char *txt, int file)
{
  int n; 
  if (file > 0)
    n = write(file, txt, my_strlen(txt));

  if(n < 0)
  {
      perror("my_fputs()");
      return (errno);
  }
  return (1);
}

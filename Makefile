##
## Makefile for Makefile in /home/pigot_a/piscine/c/battmid/pigot_a/
## 
## Made by PIGOT Aurélien
## Login   <pigot_a@etna-alternance.net>
## 
## Started on  Sat Nov  1 15:36:03 2014 PIGOT Aurélien
## Last update Mon Feb  8 12:23:45 2016 Pigot Aurélien
##
NAME= malloc
RM= rm -f
CC= gcc
OPT= -L lib/. -lmy
SRC= $(wildcard *.c)
CFLAGS = -W -Wall -Werror
OBJ=$(SRC:%.c=%.o)

$(NAME): $(OBJ)
	make -C lib/
	$(CC) $(CFLAGS) $(OBJ) $(OPT) -o  $(NAME)
all: $(NAME)
clean:
	$(RM) $(OBJ)
	rm -f lib/*.so
	make clean -C lib/
fclean: clean
	$(RM) $(NAME)
re: fclean all


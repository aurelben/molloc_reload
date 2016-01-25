##
## Makefile for Makefile libmy in /home/Pigot Aurélien
##
## Made by Pigot Aurélien
## Login   <pigot_a@etna-alternance.net>
##
## Started on  Thu Oct 23 20:00:16 2014 Pigot Aurélien
## Last update Sat Feb 14 21:58:30 2015 Pigot Aurélien
##
NAME= libmy.a
RM= rm -f
CC= gcc
SRC=$(wildcard *.c)
FLAGS = -W -Wall -Werror
OBJ=$(SRC:.c=.o)
$(NAME):$(OBJ)
	@ar r $(NAME) $(OBJ)
		@ranlib $(NAME)
all: $(OBJ)
	$(CC) $(FLAGS) -c $(SRC)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

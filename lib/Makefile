##
## Makefile for my_malloc in my_malloc/pigot_a
##
## Made by PiGOT aurelien
## Login   <pigot_a@etna-alternance.net>
##
## Started on  Mon Jan 11 16:22:56 2016 Pigot Aurélien
## Last update Mon Feb  8 11:10:25 2016 Pigot Aurélien
##
UNAME		:= $(shell uname)
NAME		= libmy_malloc_$(UNAME).so
LINK_NAME	= libmy_malloc.so
RM		= rm -f
CC		= gcc
SRC		= my_malloc.c my_free_list.c
CFLAGS 		= -W -Wall -Werror
PICFLAGS 	= -fPIC
LDFLAGS 	= -shared
OBJ		= $(SRC:%.c=%.o)
$(NAME):	$(OBJ)
		$(CC) -c $(CFLAGS) $(PICFLAGS) $(SRC)
		$(CC) $(PICFLAGS) $(LDFLAGS) -o $(NAME) *.o
		@ln -s $(NAME) $(LINK_NAME)
all: 		$(NAME)
tests:		$(OBJ)
		$(CC) -c $(CFLAGS) $(PICFLAGS) $(SRC)
		$(CC) $(PICFLAGS) $(LDFLAGS) -o $(NAME) *.o
		@export LD_PRELOAD=./libmy_malloc_Linux.so
		#@echo "Launching unit test"
		#@.././malloc
		@echo "Launching ls -Rla"
		@ls -la /
		@echo "Launching svn st"
		@svn st
		#@unset LD_PRELOAD
		@make fclean
stress:		$(OBJ)
		$(CC) -c $(CFLAGS) $(PICFLAGS) $(SRC)
		$(CC) $(PICFLAGS) $(LDFLAGS) -o $(NAME) *.o
		@export LD_PRELOAD=./libmy_malloc_Linux.so
		@./malloc_stress.sh ./$(NAME)
		@unset LD_PRELOAD
		@make fclean
clean:
		$(RM) $(OBJ)
fclean:		clean
		$(RM) $(NAME)
		$(RM) $(LINK_NAME)
re:		fclean all
.PHONY:		all clean fclean re tests
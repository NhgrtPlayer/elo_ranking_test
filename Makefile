##
## Makefile for  in /home/player/Programmes perso/elo_prog
## 
## Made by Merwan Lara
## Login   <player@epitech.net>
## 
## Started on  Tue Jul 26 00:31:21 2016 Merwan Lara
## Last update Tue Jul 26 01:15:30 2016 Merwan Lara
##

CC	= gcc

RM	= rm -f

NAME	= elo_rank

SRCS	= main.c \
	  list.c \
	  rank.c \
	  utils/my_putchar_putstr.c \
	  utils/my_strcmp.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -W -Wall -Werror -I include

LDFLAGS	= -lm

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

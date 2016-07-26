##
## Makefile
##
## Made by NhgrtPlayer
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

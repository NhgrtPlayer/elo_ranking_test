##
## Makefile
##
## Made by NhgrtPlayer
##

CC	= gcc

RM	= rm -f

NAME	= test_gui

SRCS	= test.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	= -W -Wall -Werror -I include `pkg-config --cflags gtk+-3.0`

LDFLAGS	= `pkg-config --libs gtk+-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

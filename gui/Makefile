##
## Makefile
##
## Made by NhgrtPlayer
## (⌐■_■)
##
## Beyond the Brain
##

CC	= g++

RM	= rm -f

NAME	= test_gui

SRCS	= test.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Werror -I include

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

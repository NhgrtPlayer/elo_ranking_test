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

SRCS	= main_window.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -std=c++14 -W -Wall -I include
CPPFLAGS += `pkg-config --cflags gtkmm-3.0`

LDFLAGS	= `pkg-config --libs gtkmm-3.0`

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

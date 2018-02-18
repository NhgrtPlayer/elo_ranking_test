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

SRCS	= main.cpp \
	  MainWindow.cpp \
	  NewPlayerWindow.cpp \
	  MainTreeView.cpp \
	  MainApplication.cpp \
	  Player.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -std=c++14 -W -Wall -I include
CPPFLAGS += `pkg-config gtkmm-3.0 --cflags`

LDFLAGS	= `pkg-config gtkmm-3.0 --libs`

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

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

SRCS	= source/main.cpp \
	  source/MainWindow.cpp \
	  source/NewPlayerWindow.cpp \
	  source/MainTreeView.cpp \
	  source/MainApplication.cpp \
	  source/Player.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -std=c++14 -W -Wall -I header
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

CC	= g++

RM	= rm -f

NAME	= elo_rank

SRCS	= main.cpp \
	  Player.cpp

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	= -W -Wall -Werror -I include

LDFLAGS	= 

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re

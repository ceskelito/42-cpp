NAME	= account
CC		= g++
CFLAGS	= -Wall -Wextra -Werror --std=c++98
RM 		= rm -f

SRCS = Account.cpp \
	   tests.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

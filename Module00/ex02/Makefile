NAME	= account
CC		= g++
CFLAGS	= -Wall -Wextra -Werror
RM 		= rm -f

SRCS = Account.cpp \
	   tests.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@echo OBJS: $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

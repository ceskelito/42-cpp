NAME	= Megaphone
CC		= g++
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror --std=c++98
IFLAGS	= -Iincludes

FILES = megaphone

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

%.o: %.cpp
	$(CC) -c $(IFLAGS) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

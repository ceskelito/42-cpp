NAME	= mutatedAbomination
CC		= g++
MKDIR	= mkdir -p
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror --std=c++98

FILES	= main

OBJS_DIR	= objs

SRCS	= main.cpp

OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:%.cpp=%.o))

all: $(NAME)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR):
	$(MKDIR) $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

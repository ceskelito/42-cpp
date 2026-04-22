NAME		= Bureaucrat
CC			= g++
MKDIR		= mkdir -p
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror --std=c++98
IFLAGS		= -Iincludes

OBJS_DIR 	= objs

SRCS		= main.cpp \
				Bureaucrat.class.cpp

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:%.cpp=%.o))

all: $(NAME)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CC) -c $(IFLAGS) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(OBJS_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

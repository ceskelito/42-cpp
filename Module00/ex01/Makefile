NAME	= PhoneBook
CC		= g++
MKDIR	= mkdir -p
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror --std=c++98
IFLAGS	= -Iincludes

FILES = Contact.class \
		PhoneBook.class	\
		main

SRCS = $(addsuffix .cpp, $(FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

SRCS_DIR = srcs
OBJS_DIR = objs

vpath %.cpp $(SRCS_DIR)

all: $(NAME)

$(OBJS_DIR)/%.o: %.cpp $(OBJS_DIR)
	$(CC) -c $(IFLAGS) $(CFLAGS) $< -o $@

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

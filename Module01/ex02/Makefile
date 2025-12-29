NAME 	= zombie
CC 		= g++
RM 		= rm -f
MKDIR 	= mkdir -p
CFLAGS 	= -Wall -Wextra -Werror --std=c++98

O_DIR = objs

SRCS = 	main.cpp

OBJS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(O_DIR)/%.o: %.cpp | $(O_DIR)
	$(CC) -c $(CFLAGS) $(IFLAGS) $^ -o $@

$(O_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(O_DIR)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean re

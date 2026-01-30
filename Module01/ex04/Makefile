NAME      	= sed
TESTER_NAME = tester
CC        	= g++
MKDIR     	= mkdir -p
RM        	= rm -f
CFLAGS    	= -Wall -Wextra -Werror --std=c++98
IFLAGS   	= -Iincludes

FILES     = main

SRCS_DIR  = srcs
OBJS_DIR  = objs

TESTER_SRCS = $(SRCS_DIR)/tester.cpp

SRCS      = $(addsuffix .cpp, $(FILES))
OBJS      = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES)))

vpath %.cpp $(SRCS_DIR)

all: $(NAME)

$(TESTER_NAME):
	$(CC) $(CFLAGS) $(TESTER_SRCS) -o tester

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
	$(RM) $(TESTER_NAME)

re: fclean all

.PHONY: all clean fclean re

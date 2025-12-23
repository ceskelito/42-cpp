CC 		= g++
RM 		= rm -f
MKDIR 	= mkdir -p
CFLAGS 	= -Wall -Wextra -Werror --std=c++98
IFLAGS 	= -Iincludes

S_DIR = srcs

O_DIR = objs

SRCS = 	Zombie.cpp		\
		main.cpp		\
		newZombie.cpp	\
		randomChump.cpp

# OBJS = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

vpath %.cpp $(S_DIR)

all: $(OBJS)

$(O_DIR)/%.o: %.cpp | $(O_DIR)
	$(CC) -c $(CFLAGS) $(IFLAGS) $^ -o $@

$(O_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(O_DIR)

re: clean all

.PHONY: all clean re

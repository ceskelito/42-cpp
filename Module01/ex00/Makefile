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

OBJS = $(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

vpath %.c $(S_DIR)

all: $(OBJS)

$(O_DIR)/%.o: %.cpp | $(O_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $< -o $@

$(O_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJS)
	$(RM) -r $(O_DIR)

.PHONY: all clean re

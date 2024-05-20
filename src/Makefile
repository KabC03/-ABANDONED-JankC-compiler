# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRCS = main.c compiler_structs.c shunting_yard.c stacks.c storage_controller.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = my_program

# Default target
all: $(EXEC)

# Linking object files to create the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects and executable
clean:
	rm -f $(OBJS) $(EXEC)

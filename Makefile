# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = sha256.c sha256_funcs.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = sha

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm  # Add -lm to link with the math library

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

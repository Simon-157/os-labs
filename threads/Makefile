# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source files and executable names
SRC_QUESTION1 = question1.c
SRC_QUESTION2 = question2.c
EXEC_QUESTION1 = question1
EXEC_QUESTION2 = question2

# Default target
all: $(EXEC_QUESTION1) $(EXEC_QUESTION2)

# Rule to build the executables
$(EXEC_QUESTION1): $(SRC_QUESTION1)
	$(CC) $(CFLAGS) -o $@ $^

$(EXEC_QUESTION2): $(SRC_QUESTION2)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule to remove compiled files
clean:
	rm -f $(EXEC_QUESTION1) $(EXEC_QUESTION2)


CC = gcc
CFLAGS = -Wall -g

# Directory for source files
SRC_DIR = ./src

# Directory for object files
OBJ_DIR = ./obj

# Directory for binary output
BIN_DIR = ./bin

# Target executable name
TARGET = $(BIN_DIR)/compiler

# List all source files here
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/compiler_structs.c $(SRC_DIR)/stack.c $(SRC_DIR)/storage_container.c

# Convert source file paths to object file paths
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule to build everything
all: $(TARGET)

# Link object files into a binary
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the binary
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Additional dependencies
$(OBJ_DIR)/main.o: $(SRC_DIR)/compiler_structs.h $(SRC_DIR)/stack.h $(SRC_DIR)/storage_controller.h
$(OBJ_DIR)/compiler_structs.o: $(SRC_DIR)/compiler_structs.h
$(OBJ_DIR)/stack.o: $(SRC_DIR)/stack.h
$(OBJ_DIR)/storage_container.o: $(SRC_DIR)/storage_controller.h

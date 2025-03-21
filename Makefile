# Compiler & Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -Iinc

# Directories
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc

# Sources & Objects
SRCS    := $(wildcard $(SRC_DIR)/*.c)
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME    := ft_traceroute

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	@echo "🔗 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)
	@echo "🛠️  Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if missing
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

# Clean all
fclean: clean
	@echo "🧽 Removing executable..."
	@rm -f $(NAME)

# Rebuild from scratch
re: fclean all

# Bonus (if you add a bonus target later)
bonus: all

# Phony targets
.PHONY: all clean fclean re bonus

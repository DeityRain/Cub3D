# --- Names ---
NAME        = cub3D

# --- Compilation ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinc -I$(MLX_PATH)

# --- Directories ---
MLX_PATH    = ./minilibx
MLX_LIB     = $(MLX_PATH)/libmlx.a
SRC_DIR     = src
OBJ_DIR     = obj

# --- Sources & Objects ---
# This will find main.c inside the src/ folder
SRCS        = $(SRC_DIR)/main.c
# This places .o files in a separate obj/ folder to keep things clean
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# --- Library Flags (Linux) ---

MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

# --- Rules ---

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully!"

$(MLX_LIB):
	@echo "🔧 Compiling MiniLibX..."
	@make -C $(MLX_PATH) > /dev/null 2>&1

# Rule to compile .c files from src/ into .o files in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_PATH) clean > /dev/null 2>&1
	@echo "🧹 Objects removed."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Executable removed."

re: fclean all

.PHONY: all clean fclean re

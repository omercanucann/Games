NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

SRCS = src/so_long.c src/sprites.c src/move.c src/validate.c src/map_size_reader.c src/path_valid.c src/utils.c src/utilstwo.c src/enemy.c printf/ft_printf_utils.c printf/ft_printf.c \
		get_next_line/get_next_line_utils.c get_next_line/get_next_line.c
OBJS = $(SRCS:.c=.o) $(PRINTF:.c=.o)

all: $(LIBFT) $(NAME) $(MLX)

$: $(MLX):
	make -C $(MLX_DIR)
$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -I $(MLX_DIR) -I $(LIBFT_DIR) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all
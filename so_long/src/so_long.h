/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:19 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 15:28:41 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../printf/ft_printf.h"
# include <stdio.h>

# define TILE_SIZE 64
# define DIR_RIGHT 0
# define DIR_LEFT 1
# define DIR_UP 2
# define DIR_DOWN 3
# define MAX_ENEMIES 50
# define ENEMY_MOVE_DELAY 400
typedef struct s_enemy
{
	int	x;
	int	y;
	int	direction;
}	t_enemy;

typedef struct s_map_info
{
	int	*player_count;
	int	*exit_count;
	int	*collectible_count;
	int	i;
	int	j;
}	t_map_info;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*exit;
	void	*player_right;
	void	*player_left;
	void	*player_front;
	void	*player;
	int		player_dir;
	void	*collection;
	void	*floor;
	void	*enemy;
	void	*enemy_left;
	void	*explosion1;
	void	*explosion2;
	void	*explosion3;
	void	*explosion4;
	void	*explosion5;
	char	**map;
	int		game_over;
	int		map_width;
	int		map_height;
	int		check;
	t_enemy	enemies[MAX_ENEMIES];
	int		enemy_count;
	int		frame_count;
	int		is_exploding;
	int		explosion_frame;
	int		explosion_x;
	int		explosion_y;
}	t_game;

void	ft_error(char *str, t_game *game);
int		close_game(t_game *game);
void	load_sprites(t_game *game);
void	draw_map(t_game *game);
int		validate_map(t_game *game);
int		check_walls(t_game *game);
void	find_player_position(t_game *game, int *x, int *y);
int		count_collectibles(t_game *game);
void	move_player(t_game *game, int new_x, int new_y, int direction);
int		key_hook(int keycode, t_game *game);
void	check_sprites(t_game *game);
char	**read_map_dynamic(char *filename, t_game *game);
int		get_map_dimensions(char *filename, int *width, int *height);
int		is_path_valid(t_game *game);
void	destroy_images(t_game *game);
void	draw_tile(t_game *game, char tile, int x, int y);
char	**copy_map(char **map, int height);
int		perform_flood_fill(t_game *game, char **map_copy);
char	**allocate_map_memory(int height, t_game *game);
void	fill_map_data(int fd, char **map, int height, t_game *game);
void	argc_checker(int argc, t_game *game);
void	init_game(t_game *game, char *argv);
void	update_player_map(t_game *game, int *pos, int *new_pos);
void	init_enemies(t_game *game);
void	update_enemies(t_game *game);
int		check_player_collision(t_game *game);
void	move_enemy(t_game *game, int enemy_idx);
int		game_loop(t_game *game);
void	update_explosion_animation(t_game *game);
#endif
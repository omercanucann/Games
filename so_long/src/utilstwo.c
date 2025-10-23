/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilstwo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:50:39 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 14:50:40 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**read_map_dynamic(char *filename, t_game *game)
{
	char	**map;
	int		fd;

	if (!get_map_dimensions(filename, &game->map_width, &game->map_height))
		close_game(game);
	map = allocate_map_memory(game->map_height, game);
	if (!map)
	{
		perror("Error");
		close_game(game);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		close_game(game);
	}
	fill_map_data(fd, map, game->map_height, game);
	close(fd);
	return (map);
}

void	argc_checker(int argc, t_game *game)
{
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		close_game(game);
	}
}

void	init_game(t_game *game, char *argv)
{
	game->map = read_map_dynamic(argv, game);
	game->mlx = mlx_init();
	if (!game->mlx || !game->map)
	{
		perror("Error\n");
		close_game(game);
	}
	if (!validate_map(game) || !check_walls(game) || !is_path_valid(game))
	{
		close_game(game);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		perror("Error\n");
		close_game(game);
	}
	load_sprites(game);
	check_sprites(game);
	init_enemies(game);
	game->frame_count = 0;
	draw_map(game);
}

void	update_player_map(t_game *game, int *pos, int *new_pos)
{
	int	player_x;
	int	player_y;
	int	new_x;
	int	new_y;

	player_x = pos[0];
	player_y = pos[1];
	new_x = new_pos[0];
	new_y = new_pos[1];
	game->map[player_y][player_x] = '0';
	game->map[new_y][new_x] = 'P';
}

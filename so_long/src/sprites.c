/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:23 by oucan             #+#    #+#             */
/*   Updated: 2025/03/22 16:59:32 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_sprites(t_game *game)
{
	if (!game->wall || !game->exit || !game->player
		|| !game->collection || !game->floor
		|| !game->player_right || !game->player_left || !game->player_front
		|| !game->enemy || !game->enemy_left
		|| !game->explosion1 || !game->explosion2 || !game->explosion3
		|| !game->explosion4 || !game->explosion5)
	{
		if (!game->wall)
			ft_error("wall error", game);
		else if (!game->exit)
			ft_error("exit error", game);
		else if (!game->player)
			ft_error("player error", game);
		else if (!game->collection)
			ft_error("collection error", game);
		else if (!game->floor)
			ft_error("floor error", game);
		else if (!game->player_right)
			ft_error("player_right error", game);
		else if (!game->player_left)
			ft_error("player_left error", game);
		else if (!game->player_front)
			ft_error("player_front error", game);
		else if (!game->enemy)
			ft_error("enemy error", game);
		else if (!game->enemy_left)
			ft_error("enemy_left (enemysol.xpm) error", game);
		else if (!game->explosion1)
			ft_error("explosion1 (patlamaone.xpm) error", game);
		else if (!game->explosion2)
			ft_error("explosion2 (patlamatwo.xpm) error", game);
		else if (!game->explosion3)
			ft_error("explosion3 (patlamathree.xpm) error", game);
		else if (!game->explosion4)
			ft_error("explosion4 (patlamafour.xpm) error", game);
		else if (!game->explosion5)
			ft_error("explosion5 (patlamafive.xpm) error", game);
	}
}

static void	*load_image(t_game *game, char *path)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	return (mlx_xpm_file_to_image(game->mlx, path, &width, &height));
}

void	load_sprites(t_game *game)
{
	game->wall = load_image(game, "./textures/wall.xpm");
	game->exit = load_image(game, "./textures/exit.xpm");
	game->player_right = load_image(game, "./textures/player_right.xpm");
	game->player_left = load_image(game, "./textures/player_left.xpm");
	game->player_front = load_image(game, "./textures/player_front.xpm");
	game->player = game->player_front;
	game->player_dir = DIR_UP;
	game->collection = load_image(game, "./textures/collection.xpm");
	game->floor = load_image(game, "./textures/floor.xpm");
	game->enemy = load_image(game, "./textures/enemy.xpm");
	/* left-facing enemy sprite (Turkish: enemysol.xpm) */
	game->enemy_left = load_image(game, "./textures/enemysol.xpm");
	game->explosion1 = load_image(game, "./textures/patlamaone.xpm");
	game->explosion2 = load_image(game, "./textures/patlamatwo.xpm");
	game->explosion3 = load_image(game, "./textures/patlamathree.xpm");
	game->explosion4 = load_image(game, "./textures/patlamafour.xpm");
	game->explosion5 = load_image(game, "./textures/patlamafive.xpm");
}

void	draw_tile(t_game *game, char tile, int x, int y)
{
	void	*img;
	int		i;

	if (tile == '1')
		img = game->wall;
	else if (tile == 'E')
		img = game->exit;
	else if (tile == 'P')
	{
		img = game->player;
		mlx_put_image_to_window(game->mlx, game->win, game->floor, 
			x * TILE_SIZE, y * TILE_SIZE);
		mlx_put_image_to_window(game->mlx, game->win,
			img, x * TILE_SIZE, y * TILE_SIZE);
		return ;
	}
	else if (tile == 'C')
		img = game->collection;
	else
		img = game->floor;
	mlx_put_image_to_window(game->mlx, game->win,
		img, x * TILE_SIZE, y * TILE_SIZE);
	i = -1;
	while (++i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
		{
			if (game->enemies[i].direction == DIR_LEFT && game->enemy_left)
				mlx_put_image_to_window(game->mlx, game->win,
					game->enemy_left, x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_put_image_to_window(game->mlx, game->win,
					game->enemy, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
}

void	draw_map(t_game *game)
{
	int		x;
	int		y;
	void	*explosion_img;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
	if (game->is_exploding)
	{
		if (game->explosion_frame < 80)
			explosion_img = game->explosion1;
		else if (game->explosion_frame < 100)
			explosion_img = game->explosion2;
		else if (game->explosion_frame < 120)
			explosion_img = game->explosion3;
		else if (game->explosion_frame < 140)
			explosion_img = game->explosion4;
		else
			explosion_img = game->explosion5;
		mlx_put_image_to_window(game->mlx, game->win, explosion_img,
			game->explosion_x * TILE_SIZE, game->explosion_y * TILE_SIZE);
	}
}

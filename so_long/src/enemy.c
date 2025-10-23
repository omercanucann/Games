/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by oucan             #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_enemies(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map_height && count < MAX_ENEMIES)
	{
		x = 0;
		while (x < game->map_width && count < MAX_ENEMIES)
		{
			if (game->map[y][x] == 'N')
			{
				game->enemies[count].x = x;
				game->enemies[count].y = y;
				game->enemies[count].direction = (count % 4);
				game->map[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
	game->enemy_count = count;
}

static int	can_move_enemy(t_game *game, int x, int y)
{
	int	i;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'E')
		return (0);
	if (game->map[y][x] == 'C')
		return (1);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			return (0);
		i++;
	}
	return (1);
}

void	move_enemy(t_game *game, int enemy_idx)
{
	int	new_x;
	int	new_y;
	int	dir;
	int	tries;

	dir = game->enemies[enemy_idx].direction;
	tries = 0;
	while (tries < 4)
	{
		new_x = game->enemies[enemy_idx].x;
		new_y = game->enemies[enemy_idx].y;
		if (dir == DIR_RIGHT)
			new_x++;
		else if (dir == DIR_LEFT)
			new_x--;
		else if (dir == DIR_UP)
			new_y--;
		else if (dir == DIR_DOWN)
			new_y++;
		if (can_move_enemy(game, new_x, new_y))
		{
			game->enemies[enemy_idx].x = new_x;
			game->enemies[enemy_idx].y = new_y;
			game->enemies[enemy_idx].direction = dir;
			return ;
		}
		dir = (dir + 1) % 4;
		tries++;
	}
	game->enemies[enemy_idx].direction = dir;
}


int	check_player_collision(t_game *game)
{
	int	player_x;
	int	player_y;
	int	i;

	find_player_position(game, &player_x, &player_y);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == player_x
			&& game->enemies[i].y == player_y)
		{
			ft_printf("Game Over! You were caught by an enemy!\n");
			game->game_over = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		move_enemy(game, i);
		i++;
	}
	check_player_collision(game);
}

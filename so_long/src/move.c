/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:03:04 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 15:13:29 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collectibles(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static int	check_exit_condition(t_game *game, int new_x,
	int new_y, int move_count)
{
	if (game->map[new_y][new_x] == 'E')
	{
		if (count_collectibles(game) == 0)
		{
			ft_printf("You won in %d moves!\n", move_count + 1);
			game->game_over = 1;
			return (1);
		}
		else
		{
			ft_printf("Collect all items first!\n");
			return (2);
		}
	}
	return (0);
}

static void	update_player_sprite(t_game *game, int direction)
{
	if (direction == DIR_RIGHT)
		game->player = game->player_right;
	else if (direction == DIR_LEFT)
		game->player = game->player_left;
	else if (direction == DIR_UP || direction == DIR_DOWN)
		game->player = game->player_front;
}

void	move_player(t_game *game, int new_x, int new_y, int direction)
{
	int			pos[2];
	int			new_pos[2];
	static int	move_count = 0;
	int			exit_result;

	find_player_position(game, &pos[0], &pos[1]);
	new_pos[0] = new_x;
	new_pos[1] = new_y;
	if (game->map[new_y][new_x] == '1')
		return ;
	exit_result = check_exit_condition(game, new_x, new_y, move_count);
	if (exit_result == 2)
		return ;
	update_player_sprite(game, direction);
	game->player_dir = direction;
	update_player_map(game, pos, new_pos);
	move_count++;
	ft_printf("Moves: %d\n", move_count);
	draw_map(game);
}

int	key_hook(int keycode, t_game *game)
{
	int	player_x;
	int	player_y;

	find_player_position(game, &player_x, &player_y);
	if (keycode == 65307)
		close_game(game);
	else if (keycode == 119)
		move_player(game, player_x, player_y - 1, DIR_UP);
	else if (keycode == 115)
		move_player(game, player_x, player_y + 1, DIR_DOWN);
	else if (keycode == 97)
		move_player(game, player_x - 1, player_y, DIR_LEFT);
	else if (keycode == 100)
		move_player(game, player_x + 1, player_y, DIR_RIGHT);
	return (0);
}

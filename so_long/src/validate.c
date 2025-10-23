/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:26 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 15:20:13 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_counts(int player, int exit, int collectible)
{
	if (player != 1)
	{
		ft_printf("Error Number of players must be 1! (Now: %d)\n", player);
		return (0);
	}
	if (exit != 1)
	{
		ft_printf("Error There should be 1 exit!\n");
		return (0);
	}
	if (collectible < 1)
	{
		ft_printf("Error Must be at least 1 collectible!\n");
		return (0);
	}
	return (1);
}

static int	validate_map_char(char c, t_map_info *map_info)
{
	if (c == 'P')
		(*map_info->player_count)++;
	else if (c == 'E')
		(*map_info->exit_count)++;
	else if (c == 'C')
		(*map_info->collectible_count)++;
	else if (c == 'N')
		;
	else if (c != '0' && c != '1')
	{
		ft_printf("Error\n");
		return (0);
	}
	return (1);
}

int	check_map_dimensions(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map_height)
	{
		if (ft_strlen(game->map[i]) < game->map_width)
		{
			ft_error("Error: Map is not rectangular!", game);
			return (0);
		}
	}
	return (1);
}

int	count_map_elements(t_game *game, int *p_count, int *e_count, int *c_count)
{
	int			i;
	int			j;
	t_map_info	map_info;

	i = -1;
	map_info.player_count = p_count;
	map_info.exit_count = e_count;
	map_info.collectible_count = c_count;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			map_info.i = i;
			map_info.j = j;
			if (!validate_map_char(game->map[i][j], &map_info))
				return (0);
		}
	}
	return (1);
}

int	validate_map(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	if (!check_map_dimensions(game))
		return (0);
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	if (!count_map_elements(game, &player_count,
			&exit_count, &collectible_count))
		return (0);
	return (validate_counts(player_count, exit_count, collectible_count));
}

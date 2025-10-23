/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:50:31 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 15:14:15 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *str, t_game *game)
{
	ft_printf("%s\n", str);
	close_game(game);
}

int	close_game(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->map_height)
		{
			free(game->map[i]);
			i++;
		}
		if (game->map)
			free(game->map);
		game->map = NULL;
	}
	destroy_images(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(1);
}

int	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
		{
			ft_printf("Error: There is a gap in the top or bottom row\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
		{
			ft_printf("Error: There is a gap in the right or left column\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	find_player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	is_path_valid(t_game *game)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		ft_error("Memory allocation failed during path validation!\n", game);
	result = perform_flood_fill(game, map_copy);
	return (result);
}

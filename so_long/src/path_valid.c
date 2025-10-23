/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:12 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 15:13:42 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
	{
		perror("Error\n");
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[height] = NULL;
	return (map_copy);
}

static void	do_flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	do_flood_fill(map, x + 1, y);
	do_flood_fill(map, x - 1, y);
	do_flood_fill(map, x, y + 1);
	do_flood_fill(map, x, y - 1);
}

int	check_fill(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'E' || map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	free_map_copy(t_game *game, char **map_copy)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

int	perform_flood_fill(t_game *game, char **map_copy)
{
	int	player_x;
	int	player_y;

	find_player_position(game, &player_x, &player_y);
	do_flood_fill(map_copy, player_x, player_y);
	if (check_fill(map_copy, game->map_height) == 0)
	{
		ft_printf("Error: Map is not surrounded by walls!\n");
		free_map_copy(game, map_copy);
		return (0);
	}
	free_map_copy(game, map_copy);
	return (1);
}

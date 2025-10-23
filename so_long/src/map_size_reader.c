/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:05:03 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 17:08:36 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_dimensions(char *line, int *max_width)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (len > *max_width)
		*max_width = len;
}

int	get_map_dimensions(char *filename, int *width, int *height)
{
	int		fd;
	char	*line;
	int		max_w;
	int		count_h;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (0);
	}
	max_w = 0;
	count_h = 0;
	line = get_next_line(fd);
	while (line)
	{
		update_dimensions(line, &max_w);
		count_h++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	*width = max_w;
	*height = count_h;
	return (1);
}

char	**allocate_map_memory(int height, t_game *game)
{
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		perror("Error\n");
		close_game(game);
	}
	return (map);
}

void	fill_map_data(int fd, char **map, int height, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (i < height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			perror("Error\n");
			close_game(game);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
	}
	map[i] = NULL;
	line = get_next_line(fd);
	if (line)
		free(line);
}

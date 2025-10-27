/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:02:16 by oucan             #+#    #+#             */
/*   Updated: 2025/03/24 16:38:21 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->player_right)
		mlx_destroy_image(game->mlx, game->player_right);
	if (game->player_left)
		mlx_destroy_image(game->mlx, game->player_left);
	if (game->player_front)
		mlx_destroy_image(game->mlx, game->player_front);
	if (game->collection)
		mlx_destroy_image(game->mlx, game->collection);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->enemy)
		mlx_destroy_image(game->mlx, game->enemy);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

int	game_loop(t_game *game)
{
	if (game->game_over)
		close_game(game);
	game->frame_count++;
	if (game->frame_count % ENEMY_MOVE_DELAY == 0)
	{
		update_enemies(game);
		draw_map(game);
	}
	else if (game->frame_count % 2 == 0)
	{
		draw_map(game);
	}
	return (0);
}

void	check_ber(char **argvn)
{
	int	i;

	i = 0;
	while (argvn[1][i])
		i++;
	if (argvn[1][i - 1] != 'r' || argvn[1][i - 2] != 'e'
		|| argvn[1][i - 3] != 'b' || argvn[1][i - 4] != '.')
	{
		ft_printf("Invalid map format!\n");
		exit(1);
	}
	if (argvn[1][i - 5] == '\0')
	{
		ft_printf("Invalid map format!\n");
		exit(1);
	}
	if (argvn[1][i - 1] == 'r' && argvn[1][i - 2] == 'e'
		&& argvn[1][i - 3] == 'b'
		&& argvn[1][i - 4] == '.' && argvn[1][i - 5] == '/')
	{
		ft_printf("Invalid map format!\n");
		exit(1);
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	argc_checker(argc, &game);
	check_ber(argv);
	init_game(&game, argv[1]);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

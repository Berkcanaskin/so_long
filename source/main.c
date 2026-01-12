/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:15:10 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_arg(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (file[len - 4] != '.' || file[len - 3] != 'b'
		|| file[len - 2] != 'e' || file[len - 1] != 'r')
		return (0);
	return (1);
}

static int	key_handle(int key, t_data *data)
{
	if (key == ESC)
		clean_exit(data);
	else if (key == W)
		move_player(data, 0, -1);
	else if (key == S)
		move_player(data, 0, 1);
	else if (key == A)
		move_player(data, -1, 0);
	else if (key == D)
		move_player(data, 1, 0);
	draw_map(data);
	return (0);
}

static int	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->map_w * TILE,
			data->map_h * TILE, "so_long");
	if (!data->win)
		error_exit("Window creation failed", data);
	init_imgs(data);
	check_imgs(data);
	draw_map(data);
	mlx_key_hook(data->win, key_handle, data);
	mlx_hook(data->win, 17, 0, clean_exit, data);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 32), 1);
	if (!check_arg(av[1]))
		return (write(2, "Error\nInvalid file extension\n", 28), 1);
	data = init_game();
	if (!data)
		return (write(2, "Error\nGame initialization failed\n", 31), 1);
	if (!read_map_size(av[1], data))
		error_exit("Map reading failed", data);
	if (!read_map_fill(av[1], data))
		error_exit("Map reading failed", data);
	check_map_objects(data);
	check_map_walls(data);
	if (!check_valid_path(data))
		error_exit("No valid path exists", data);
	if (!init_window(data))
		error_exit("Window initialization failed", data);
	mlx_loop(data->mlx);
	return (0);
}

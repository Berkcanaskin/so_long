/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:19:56 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_objects(t_data *data)
{
	if (data->player.x == -1)
		error_exit("No player found", data);
	if (data->coins == 0)
		error_exit("No coins found", data);
	if (data->exit != 1)
		error_exit("Invalid number of exits", data);
}

static void	check_horizontal_walls(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->map_w)
	{
		if (data->map[0][x] != '1' || data->map[data->map_h - 1][x] != '1')
			error_exit("Map not surrounded by walls", data);
		x++;
	}
}

static void	check_vertical_walls(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_h)
	{
		if (data->map[y][0] != '1' || data->map[y][data->map_w - 1] != '1')
			error_exit("Map not surrounded by walls", data);
		y++;
	}
}

void	check_map_walls(t_data *data)
{
	check_horizontal_walls(data);
	check_vertical_walls(data);
}

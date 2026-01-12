/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 02:50:08 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_data *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, x * TILE, y * TILE);
}

void	draw_tile(t_data *data, int x, int y)
{
	put_image(data, data->img_b, x, y);
	if (data->map[y][x] == '1')
		put_image(data, data->img_w, x, y);
	else if (data->map[y][x] == 'P')
		put_image(data, data->img_p, x, y);
	else if (data->map[y][x] == 'C')
		put_image(data, data->img_c, x, y);
	else if (data->map[y][x] == 'E')
		put_image(data, data->img_e, x, y);
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			draw_tile(data, x, y);
			x++;
		}
		y++;
	}
}

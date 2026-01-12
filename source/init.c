/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:14:07 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_values(t_data *data)
{
	data->map = NULL;
	data->win = NULL;
	data->img_p = NULL;
	data->img_w = NULL;
	data->img_c = NULL;
	data->img_e = NULL;
	data->img_b = NULL;
	data->map_w = 0;
	data->map_h = 0;
	data->coins = 0;
	data->exit = 0;
	data->moves = 0;
	data->current = 0;
	data->player.x = -1;
	data->player.y = -1;
}

t_data	*init_game(void)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	init_values(data);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

void	init_imgs(t_data *data)
{
	int	size;

	size = TILE;
	data->img_p = mlx_xpm_file_to_image(data->mlx, "textures/player.xpm",
			&size, &size);
	data->img_w = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm",
			&size, &size);
	data->img_c = mlx_xpm_file_to_image(data->mlx, "textures/coin.xpm",
			&size, &size);
	data->img_e = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm",
			&size, &size);
	data->img_b = mlx_xpm_file_to_image(data->mlx, "textures/bg.xpm",
			&size, &size);
}

void	check_imgs(t_data *data)
{
	if (!data->img_p || !data->img_w || !data->img_c
		|| !data->img_e || !data->img_b)
		error_exit("Image loading failed", data);
}

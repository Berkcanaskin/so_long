/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:45:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 02:54:27 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_images(t_data *data)
{
	if (data->img_p)
		mlx_destroy_image(data->mlx, data->img_p);
	if (data->img_w)
		mlx_destroy_image(data->mlx, data->img_w);
	if (data->img_c)
		mlx_destroy_image(data->mlx, data->img_c);
	if (data->img_e)
		mlx_destroy_image(data->mlx, data->img_e);
	if (data->img_b)
		mlx_destroy_image(data->mlx, data->img_b);
}

int	clean_exit(t_data *data)
{
	if (!data)
		return (0);
	destroy_images(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_map(data->map);
	free(data);
	exit(0);
	return (0);
}

void	error_exit(char *msg, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	clean_exit(data);
	exit(1);
}

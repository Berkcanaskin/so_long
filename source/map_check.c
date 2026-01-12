/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:19:32 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**create_temp_map(t_data *data)
{
	char	**temp;
	int		i;

	temp = ft_calloc(data->map_h + 1, sizeof(char *));
	if (!temp)
		error_exit("Memory allocation failed", data);
	i = 0;
	while (i < data->map_h)
	{
		temp[i] = ft_strdup(data->map[i]);
		if (!temp[i])
		{
			free_map(temp);
			error_exit("Memory allocation failed", data);
		}
		i++;
	}
	return (temp);
}

static void	update_count(char c, int *count)
{
	if (c == 'C' || c == 'E')
		(*count)++;
}

void	flood_fill(char **map, t_pos size, t_pos curr, int *count)
{
	if (curr.x < 0 || curr.x >= size.x || curr.y < 0 || curr.y >= size.y)
		return ;
	if (map[curr.y][curr.x] == '1' || map[curr.y][curr.x] == 'V')
		return ;
	update_count(map[curr.y][curr.x], count);
	map[curr.y][curr.x] = 'V';
	flood_fill(map, size, (t_pos){curr.x + 1, curr.y}, count);
	flood_fill(map, size, (t_pos){curr.x - 1, curr.y}, count);
	flood_fill(map, size, (t_pos){curr.x, curr.y + 1}, count);
	flood_fill(map, size, (t_pos){curr.x, curr.y - 1}, count);
}

int	check_valid_path(t_data *data)
{
	char	**temp;
	t_pos	size;
	int		count;
	int		result;

	temp = create_temp_map(data);
	size.x = data->map_w;
	size.y = data->map_h;
	count = 0;
	flood_fill(temp, size, data->player, &count);
	result = (count == data->coins + 1);
	free_map(temp);
	return (result);
}

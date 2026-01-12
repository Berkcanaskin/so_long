/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:15:19 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_map_size(char *file, t_data *data)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file", data);
	data->map_w = 0;
	data->map_h = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (data->map_h == 0 && c != '\n')
			data->map_w++;
		if (c == '\n')
			data->map_h++;
	}
	data->map_h++;
	close(fd);
	return (1);
}

char	**read_map_size(char *file, t_data *data)
{
	if (!get_map_size(file, data))
		return (NULL);
	data->map = ft_calloc(data->map_h + 1, sizeof(char *));
	if (!data->map)
		error_exit("Memory allocation failed", data);
	return (data->map);
}

static void	parse_map_char(char c, t_data *data, int x, int y)
{
	if (c == 'P')
	{
		if (data->player.x != -1)
			error_exit("Multiple players found", data);
		data->player.x = x;
		data->player.y = y;
	}
	else if (c == 'C')
		data->coins++;
	else if (c == 'E')
		data->exit++;
	else if (c != '0' && c != '1')
		error_exit("Invalid character in map", data);
}

static int	read_map_line(int fd, t_data *data, int y)
{
	char	c;
	int		x;

	x = 0;
	while (read(fd, &c, 1) > 0 && c != '\n')
	{
		if (x >= data->map_w)
			error_exit("Map is not rectangular", data);
		data->map[y][x] = c;
		parse_map_char(c, data, x, y);
		x++;
	}
	if (x != data->map_w)
		error_exit("Map is not rectangular", data);
	return (1);
}

char	**read_map_fill(char *file, t_data *data)
{
	int		fd;
	int		y;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file", data);
	y = 0;
	while (y < data->map_h)
	{
		data->map[y] = ft_calloc(data->map_w + 1, sizeof(char));
		if (!data->map[y])
			error_exit("Memory allocation failed", data);
		if (!read_map_line(fd, data, y))
			error_exit("Error reading map", data);
		y++;
	}
	close(fd);
	return (data->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:55:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 02:53:17 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_data *data, t_pos new)
{
	if (new.x < 0 || new.x >= data->map_w || new.y < 0 || new.y >= data->map_h)
		return (0);
	if (data->map[new.y][new.x] == '1')
		return (0);
	return (1);
}

static void	display_moves(t_data *data)
{
	char	*moves_str;

	moves_str = ft_itoa(data->moves);
	write(1, "Moves: ", 7);
	write(1, moves_str, ft_strlen(moves_str));
	write(1, "\n", 1);
	free(moves_str);
}

static void	collect_coin(t_data *data)
{
	data->current++;
	display_moves(data);
}

static void	update_player_pos(t_data *data, t_pos new)
{
	char	old_tile;

	if (data->map[new.y][new.x] == 'E' && data->current == data->coins)
	{
		data->moves++;
		display_moves(data);
		clean_exit(data);
	}
	old_tile = data->map[data->player.y][data->player.x];
	if (data->map[new.y][new.x] == 'C')
		collect_coin(data);
	if (old_tile != 'E')
		data->map[data->player.y][data->player.x] = '0';
	else
		data->map[data->player.y][data->player.x] = 'E';
	if (data->map[new.y][new.x] != 'E')
		data->map[new.y][new.x] = 'P';
	data->player = new;
	data->moves++;
	display_moves(data);
}

int	move_player(t_data *data, int x, int y)
{
	t_pos	new;

	new.x = data->player.x + x;
	new.y = data->player.y + y;
	if (is_valid_move(data, new))
	{
		update_player_pos(data, new);
		return (1);
	}
	return (0);
}

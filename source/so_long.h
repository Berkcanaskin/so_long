/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:45:12 by baskin            #+#    #+#             */
/*   Updated: 2025/01/23 03:20:39 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define TILE 64
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	void	*img_p;
	void	*img_w;
	void	*img_c;
	void	*img_e;
	void	*img_b;
	int		map_w;
	int		map_h;
	t_pos	player;
	int		coins;
	int		exit;
	int		moves;
	int		current;
}	t_data;

t_data	*init_game(void);
void	init_imgs(t_data *data);
void	check_imgs(t_data *data);
char	**read_map_size(char *file, t_data *data);
char	**read_map_fill(char *file, t_data *data);
void	check_map_objects(t_data *data);
void	check_map_walls(t_data *data);
int		check_valid_path(t_data *data);
char	**create_temp_map(t_data *data);
void	flood_fill(char **map, t_pos size, t_pos curr, int *count);
int		move_player(t_data *data, int x, int y);
void	update_map(t_data *data, t_pos new);
int		check_move(t_data *data, t_pos pos);
void	draw_map(t_data *data);
void	draw_tile(t_data *data, int x, int y);
void	*ft_calloc(size_t count, size_t size);
void	free_map(char **map);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
int		ft_numlen(int n);
void	error_exit(char *msg, t_data *data);
int		clean_exit(t_data *data);

#endif
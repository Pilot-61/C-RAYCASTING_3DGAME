/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:30:49 by mes-salh          #+#    #+#             */
/*   Updated: 2025/02/14 22:09:09 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include "../../MLX/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define TILE_S 15
# define MIN_WIDTH 240
# define MIN_HEIGHT 140

# define BUFFER_SIZE 42

typedef struct s_gc
{
	void		*content;
	struct s_gc	*next;
}	t_gc;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;
	int				count;
}	t_textures;

typedef struct s_colors
{
	int			f_red;
	int			f_green;
	int			f_blue;
	int			c_red;
	int			c_green;
	int			c_blue;
	uint32_t	c_floor;
	uint32_t	c_ceiling;
}	t_colors;

typedef struct s_mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*img_mini;
	mlx_image_t	*img_map;
}	t_mlx_data;

typedef struct s_p
{
	float	x;
	float	y;
}	t_p;

typedef struct s_draw
{
	int	dx;
	int	sy;
	int	dy;
	int	sx;
	int	decis;
	t_p	limit;
}	t_draw;

typedef struct s_line
{
	t_p	p0;
	t_p	p1;
	int	color;
}	t_line;

typedef struct s_rays
{
	float	raydist;
	float	rayangle;
	char	direction;
	t_p		hit;
	bool	hit_hor;
	bool	hit_vert;
	bool	is_down;
	bool	is_up;
	bool	is_right;
	bool	is_left;
}	t_rays;

typedef struct s_player
{
	float	x_pos;
	float	y_pos;
	float	rotate_angle;
	float	rot_speed;
	float	xc;
	float	yc;
	float	r;
	t_p		pos;
}	t_player;

typedef struct s_md
{
	char	**temp_map;
	char	**normalized_map;
	int		height;
	int		width;
	int		player_count;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_md;

typedef struct s_vars
{
	char		*line;
	int			floor_set;
	int			ceiling_set;
	int			map_set;
	int			is_newline;
	int			tr;
}	t_vars;

typedef struct s_data
{
	t_textures	*textures;
	t_vars		vars;
	t_colors	*colors;
	t_mlx_data	*d_mlx;
	t_player	*player;
	t_rays		*d_rays;
	t_p			wall_mov;
	t_p			wall_pos;
	float		height_map;
	float		width_map;
	t_md		md;
	char		**map;
}	t_data;

typedef struct s_player_pos
{
	int	x;
	int	y;
}	t_player_pos;

typedef struct s_render_info
{
	int				i;
	int				y;
	double			wall_height;
	int				wall_top;
	int				wall_bottom;
	double			offset;
	int				tex_x;
	mlx_texture_t	*texture;
}	t_render_info;

void			*gcollector(size_t size, int mode);
void			*ft_calloc(size_t count, size_t size);
int				ft_strcmp(const char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_putstr_fd(const char *s, int fd);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *c);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strtok(char *str, char *sep);
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
char			*get_next_line(int fd);
void			ft_err(char *err_msg);
int				get_rgba(int r, int g, int b, int a);
void			draw_line(t_data *data, mlx_image_t *image, t_line line);
void			map_2d(t_data **data);
void			my_keyhook(void *param);
bool			is_wall(t_data **data, int x, int y);
void			draw_rays(t_data *data);
void			*ft_memset(void *b, int c, size_t len);
t_p				hit_hor(t_data *data, float rayangle);
t_p				hit_vert(t_data *data, float rayangle);
t_p				ray_dist(t_data *data, float rayangle, t_p p1, int r_id);
float			normalize_angle(float angle);
void			walls3d(t_data *data);
int				choose_color(t_data *data, int i);
t_rays			get_ray_dir(float rayangle);
t_p				vert_steps(float rayangle, t_rays dir);
t_p				init_vert_pos(t_data *data, float rayangle, t_rays dir);
t_p				hor_steps(float rayangle, t_rays dir);
t_p				init_hor_pos(t_data *data, float rayangle, t_rays dir);
void			ray_dire(t_data *data, int r_id);
int				ft_atoi2(char *str);
int				validate_file_extension(char *filename);
int				is_map_line(char *line);
int				tex_id(char *line);
char			*get_texture_path(char *line);
int				s_tex(t_textures *tex, char *line);
int				is_color_id(char *line);
int				count_commas(char *line);
int				parse_color(char *line, int *r, int *g, int *b);
void			remove_newline(char *line);
int				parse_map_line(char *line, t_data *game, int *nl);
int				is_sep(char c);
int				map_bordered(char **map, int height);
int				is_empty_line(char *line);
int				check_map_newlines(char **map, int height);
void			init_player_pos(t_data *game);
int				get_max_width(char **map, int height);
int				normalize_map(char **normalized, char **original,
					int height, size_t max_width);
char			**valid_map(t_data *game);
void			flood_fill(char **map, int x, int y, int *invalid);
void			get_pos(char **map, int height, int width,
					t_player_pos *pos);
int				valid_bound(t_data *game);
int				parse_file(int fd, t_data *data);
char			**duplicate_map(char **src, int height, int width);
int				parse_color(char *line, int *r, int *g, int *b);
int				process_color(t_colors *colors, char *line,
					int *floor_set, int *ceiling_set);
int				check_color_format(char *color);
void			destory_png_textures(t_textures *textures);
void			load_png_textures(t_data *data);
void			init_data(t_data **data);
float			ft_calculate_wall_height(t_data *data, int i);
void			ft_draw_ceiling(t_data *data, int i, float start_y);
void			ft_draw_floor(t_data *data, int i, t_p end_y);
mlx_texture_t	*get_wall_texture(t_data *data, int i);
t_p				find_plyr(t_data *data);
int				init_data2(t_data **data, int fd);
int				check_map_content(char **map, int height);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_get_the_next(char *buffer);
char			*ft_get_the_line(char *buffer);
char			*ft_read_line(int fd, char *resultat);
char			*ft_strjoin(char const *s1, char const *s2);
char			*get_next_line(int fd);
#endif
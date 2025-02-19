/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:55:45 by hzahri            #+#    #+#             */
/*   Updated: 2025/02/12 17:06:31 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/bonus_cub.h"

static double	get_texture_x(t_data *data, int i, mlx_texture_t *texture)
{
	if (data->d_rays[i].hit_vert)
		return (fmodf(data->d_rays[i].hit.y * (texture->width / TILE_S),
				texture->width));
	return (fmodf(data->d_rays[i].hit.x * (texture->width / TILE_S),
			texture->width));
}

static void	calculate_wall_bounds(double wall_height, int *top, int *bottom)
{
	*top = HEIGHT / 2 - wall_height / 2;
	*bottom = HEIGHT / 2 + wall_height / 2;
	if (*top < 0)
		*top = 0;
	if (*bottom >= HEIGHT)
		*bottom = HEIGHT - 1;
}

static void	draw_wall_pixel(t_data *data, t_render_info *r)
{
	double		y_coord;
	int			tex_y;
	uint8_t		*pixel;

	y_coord = (r->y - (HEIGHT / 2.0) + (r->wall_height / 2)) * r->offset;
	if (y_coord < 0)
		y_coord = 0;
	if (y_coord >= r->texture->height)
		y_coord = r->texture->height - 1;
	tex_y = (int)y_coord;
	pixel = r->texture->pixels + (r->tex_x * r->texture->bytes_per_pixel)
		+ (tex_y * r->texture->width * r->texture->bytes_per_pixel);
	mlx_put_pixel(data->d_mlx->img_map, r->i, r->y,
		get_rgba(pixel[0], pixel[1], pixel[2], pixel[3]));
}

static void	draw_textured_wall(t_data *data, t_render_info *r)
{
	int	y;

	calculate_wall_bounds(r->wall_height, &r->wall_top, &r->wall_bottom);
	r->offset = (double)r->texture->height / r->wall_height;
	y = r->wall_top - 1;
	while (++y <= r->wall_bottom)
	{
		r->y = y;
		draw_wall_pixel(data, r);
	}
	ft_draw_ceiling(data, r->i, r->wall_top);
	ft_draw_floor(data, r->i, (t_p){r->i, r->wall_bottom});
}

void	walls3d(t_data *data)
{
	t_render_info	r;
	mlx_texture_t	*texture;

	r.i = -1;
	while (++r.i < WIDTH)
	{
		ray_dire(data, r.i);
		r.wall_height = ft_calculate_wall_height(data, r.i);
		texture = get_wall_texture(data, r.i);
		if (!texture)
			continue ;
		r.texture = texture;
		r.tex_x = (int)get_texture_x(data, r.i, texture);
		draw_textured_wall(data, &r);
	}
}

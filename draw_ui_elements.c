#include "cub3d.h"

void	draw_red_border(t_cub3d *t)
{
	int	x;
	int	y;
	int	width;

	width = 10;
	y = -1;
	while (++y < t->win_h)
	{
		x = -1;
		while (++x < t->win_w)
		{
			if (x < 10 || x > t->win_w - 10)
				ft_putpxl(t, x, y, 0x00FF0000);
		}
	}
}

void	draw_crosshair(t_cub3d *t)
{
	int				x;
	int				y;
	unsigned int	texel;

	y = -1;
	while (++y < 32)
	{
		x = -1;
		while (++x < 32)
		{
			texel = ft_getpxl(t, 8, x, y);
			if (texel != 4278190080)
				ft_putpxl(t, ((t->win_w / 2) - 16) + x,
				((t->win_h / 2) - 16) + y, texel);
		}
	}
}

void	draw_bullets(t_cub3d *t)
{
	int				x;
	int				y;
	unsigned int	texel;
	int				bullet;
	int				x_start;

	bullet = 0;
	x_start = t->win_w / 3;
	while (bullet < t->p_bullets)
	{
		y = -1;
		while (++y < 32)
		{
			x = -1;
			while (++x < 32)
			{
				texel = ft_getpxl(t, 38, x / 2, y / 2);
				if (texel != 4278190080)
					ft_putpxl(t, x_start + x, (t->win_h - 37) + y, texel);
			}
		}
		x_start += 20;
		bullet++;
	}
}

void	draw_torch(t_cub3d *t)
{
	int				x;
	int				y;
	unsigned int	texel;
	static double	time_frame_swp;
	static int		frame;

	y = -1;
	while (++y < 256)
	{
		x = -1;
		while (++x < 256)
		{
			texel = ft_getpxl(t, 13 + frame, x / 4, y / 4);
			if (texel != 4278190080)
				ft_putpxl(t, x, y, texel);
		}
	}
	if ((double)(t->time_now - time_frame_swp) / (double)CLOCKS_PER_SEC > 0.1)
	{
		frame++;
		time_frame_swp = t->time_now;
	}
	if (frame > 3)
		frame = 0;
}

void	draw_gun(t_cub3d *t)
{
	int				x;
	int				y;
	unsigned int	texel;
	static double	time_frame_swp;
	static int		frame;

	y = -1;
	while (++y < 256)
	{
		x = -1;
		while (++x < 256)
		{
			texel = ft_getpxl(t, 17 + frame, x / 4, y / 4);
			if (texel != 4278190080)
				ft_putpxl(t, (t->win_w - 256) + x, (t->win_h - 256) + y, texel);
		}
	}
	if ((t->shoot == 1 || frame > 0)
	&& (double)(t->time_now - time_frame_swp) / (double)CLOCKS_PER_SEC > 0.1)
	{
		frame++;
		time_frame_swp = t->time_now;
	}
	if (frame > 3)
		frame = 0;
}

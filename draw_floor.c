#include "cub3d.h"

typedef struct		s_draw_floor_variables
{
	float			r_dir_x0;
	float			r_dir_y0;
	float			r_dir_x1;
	float			r_dir_y1;
	int				p;
	float			pos_z;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				cell_x;
	int				cell_y;
	int				tx;
	int				ty;
	unsigned int	texel;
}					t_dfv;

static void	make_calculations(t_cub3d *t, t_dfv *f, int y)
{
	f->r_dir_x0 = t->p_dir_x - t->plane_x;
	f->r_dir_y0 = t->p_dir_y - t->plane_y;
	f->r_dir_x1 = t->p_dir_x + t->plane_x;
	f->r_dir_y1 = t->p_dir_y + t->plane_y;
	f->p = y - t->win_h / 2;
	f->pos_z = 0.5 * t->win_h;
	f->row_distance = f->pos_z / f->p;
	f->floor_step_x = f->row_distance * (f->r_dir_x1 - f->r_dir_x0) / t->win_w;
	f->floor_step_y = f->row_distance * (f->r_dir_y1 - f->r_dir_y0) / t->win_w;
	f->floor_x = t->p_x + f->row_distance * f->r_dir_x0;
	f->floor_y = t->p_y + f->row_distance * f->r_dir_y0;
}

void		draw_floor(t_cub3d *t)
{
	t_dfv	f;
	int		y;
	int		x;

	y = t->win_h / 2;
	while (++y < t->win_h)
	{
		make_calculations(t, &f, y);
		x = -1;
		while (++x < t->win_w)
		{
			f.cell_x = (int)(f.floor_x);
			f.cell_y = (int)(f.floor_y);
			f.tx = (int)(64 * (f.floor_x - f.cell_x)) & (64 - 1);
			f.ty = (int)(64 * (f.floor_y - f.cell_y)) & (64 - 1);
			f.floor_x += f.floor_step_x;
			f.floor_y += f.floor_step_y;
			f.texel = ft_getpxl(t, 6, f.tx, f.ty);
			f.texel = shader(f.texel, f.row_distance);
			ft_putpxl(t, x, y, f.texel);
		}
	}
}

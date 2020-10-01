#include "cub3d.h"

typedef struct		s_put_sprites_variables
{
	int				i;
	int				x;
	double			sprite_y;
	double			sprite_x;
	double			sprite_x2;
	double			sprite_y2;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_scrn_x;
	int				sprite_h;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	unsigned int	texel;
	int				tex_x;
	int				tex_y;
	int				d;
}					t_spr;

static void	sort_sprites(t_cub3d *t)
{
	t_sprite tmp;
	int i;
	int j;

	i = -1;
	while (++i < t->sprite_n)
		t->spr[i].dis = ((t->p_x - t->spr[i].x) * (t->p_x - t->spr[i].x)
		+ (t->p_y - t->spr[i].y) * (t->p_y - t->spr[i].y));
	i = 0;
	j = 1;
	while (i + 1 < t->sprite_n)
	{
		while (j < t->sprite_n)
		{
			if (t->spr[i].dis < t->spr[j].dis)
			{
				tmp = t->spr[j];
				t->spr[j] = t->spr[i];
				t->spr[i] = tmp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

static void	make_calculations_2(t_cub3d *t, t_spr *s, int frame, double z_buf)
{
	int	y;

	if (s->transform_y > 0 && s->x > 0 && s->x < t->win_w
	&& s->transform_y < z_buf)
	{
		y = s->draw_start_y - 1;
		while (++y < s->draw_end_y)
		{
			s->d = y * 256 - t->win_h * 128 + s->sprite_h * 128;
			s->tex_y = ((s->d * 64) / s->sprite_h) / 256;
			s->texel = ft_getpxl(t->addr[frame], t->line_len[frame],
			t->bpp[frame], s->tex_x, s->tex_y);
			if (t->spr[s->i].hit > 0)
				s->texel = shader_red(s->texel);
			s->texel = shader(s->texel, s->transform_y);
			if (s->texel != 4278190080)
				ft_putpxl(t, s->x, y, s->texel);
		}
	}
}

static void	make_calculations_1(t_cub3d *t, t_spr *s)
{
	s->sprite_x2 = s->sprite_x - t->p_x; //translate sprite position to relative to camera
	s->sprite_y2 = s->sprite_y - t->p_y;
	s->inv_det = 1.0 / (t->plane_x * t->p_dir_y - t->p_dir_x * t->plane_y); //required for correct matrix multiplication
	s->transform_x =
	s->inv_det * (t->p_dir_y * s->sprite_x2 - t->p_dir_x * s->sprite_y2);
	s->transform_y =
	s->inv_det * (-t->plane_y * s->sprite_x2 + t->plane_x * s->sprite_y2); //this is actually the depth inside the screen, that what Z is in 3D
	s->sprite_scrn_x =
	(int)((t->win_w / 2) * (1 + s->transform_x / s->transform_y));
	//calculate height of the sprite on screen
	s->sprite_h = abs((int)(t->win_h / (s->transform_y))); //using 'transform_y' instead of the real distance prevents fisheye
	s->draw_start_y = -s->sprite_h / 2 + t->win_h / 2; //calculate lowest and highest pixel to fill in current x
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_h / 2 + t->win_h / 2;
	if (s->draw_end_y >= t->win_h)
		s->draw_end_y = t->win_h - 1;
	s->sprite_w = abs((int)(t->win_h / (s->transform_y))); //calculate width of the sprite
	s->draw_start_x = -s->sprite_w / 2 + s->sprite_scrn_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_w / 2 + s->sprite_scrn_x;
	if (s->draw_end_x >= t->win_w)
		s->draw_end_x = t->win_w - 1;
}

void		draw_sprites(t_cub3d *t, double *z_buf)
{
	t_spr		s;
	static int	frame[10];

	sort_sprites(t);
	s.i = -1;
	while (++s.i < t->sprite_n)
	{
		if (t->spr[s.i].type != '0')
		{
			s.sprite_y =
			t->spr[s.i].y + 0.5 + t->spr[s.i].y_draw * t->spr[s.i].mod;
			s.sprite_x =
			t->spr[s.i].x + 0.5 + t->spr[s.i].x_draw * t->spr[s.i].mod;
			make_calculations_1(t, &s);
			frame[s.i] = get_sprite_frame(t, s.i, t->time_now);
			s.x = s.draw_start_x - 1;
			while (++s.x < s.draw_end_x)
			{
				s.tex_x =
				(int)(256 * (s.x - (-s.sprite_w / 2 + s.sprite_scrn_x))
				* 64 / s.sprite_w) / 256;
				make_calculations_2(t, &s, frame[s.i], z_buf[s.x]);
			}
		}
	}
}

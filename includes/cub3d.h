/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 20:08:09 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/11 10:21:17 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RD 0.01745329251
# define MIN_WINDOW_WIDTH 300
# define MIN_WINDOW_HEIGHT 250
# define INVISIBLE 4278190080
# define SPRITE_MAX 150

# define RED "\033[0;31m"
# define B_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define B_GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define B_YELLOW "\033[01;33m"
# define BLUE "\033[0;34m"
# define B_BLUE "\033[1;34m"
# define MAGENTA "\033[0;35m"
# define B_MAGENTA "\033[1;35m"
# define CYAN "\033[0;36m"
# define B_CYAN "\033[1;36m"
# define RESET "\033[0m"

# include "../mlx/mlx.h"
# include "../ft_printf/ft_printf.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>

typedef struct			s_draw_floor_variables
{
	float				r_dir_x0;
	float				r_dir_y0;
	float				r_dir_x1;
	float				r_dir_y1;
	int					p;
	float				pos_z;
	float				row_distance;
	float				floor_step_x;
	float				floor_step_y;
	float				floor_x;
	float				floor_y;
	int					cell_x;
	int					cell_y;
	int					tx;
	int					ty;
	unsigned int		texel;
}						t_dfv;

typedef struct			s_draw_skybox_variables
{
	double				r_dir_x;
	double				r_dir_y;
	double				r_degree;
	int					tex_x;
	double				tex_y_incr;
}						t_psv;

typedef struct			s_draw_sprites_variables
{
	int					i;
	int					x;
	double				sprite_y;
	double				sprite_x;
	double				sprite_x2;
	double				sprite_y2;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_scrn_x;
	int					sprite_h;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_w;
	int					draw_start_x;
	int					draw_end_x;
	unsigned int		texel;
	int					tex_x;
	int					tex_y;
	int					d;
}						t_spr;

typedef struct			s_draw_walls_variables
{
	double				r_dir_x;
	double				r_dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					draw_start;
	int					draw_end;
	int					tex_nbr;
	double				wall_x;
	double				step;
	double				tex_pos;
	int					tex_x;
	int					line_height;
	int					step_x;
	int					step_y;
	int					side;
	unsigned int		texel;
}						t_pwv;

typedef struct			s_find_path_variables
{
	int					current_y;
	int					current_x;
	int					i;
	int					check;
	int					front_of_list;
}						t_fpv;

typedef struct			s_gen_bitmap_data
{
	int					bpp;
	int					file_h_size;
	int					info_h_size;
	char				*filename;
	int					fd;
	unsigned char		*image;
	unsigned char		*file_h;
	unsigned char		*info_h;
	int					malloc_image;
	int					malloc_file_h;
	int					malloc_info_h;
}						t_gen_bmp_data;

typedef struct			s_check_for_walls_variables
{
	double				y_dest;
	double				x_dest;
	double				y_dif;
	double				x_dif;
	double				step_x;
	double				step_y;
	double				tmp;
}						t_cfwv;

typedef struct			s_cast_ray
{
	double				r_dir_x;
	double				r_dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					step_x;
	int					step_y;
}						t_ray;

typedef struct			s_visited_squares
{
	int					y;
	int					x;
	char				direction_of_origin;
}						t_visited_squares;

typedef struct			s_sprite_xys
{
	char				type;
	int					x;
	int					y;
	double				x_draw;
	double				y_draw;
	int					dis;
	int					alive;
	int					mod;
	int					health;
	double				t_o_d;
	int					hit;
	char				mode;
	int					frame;
	double				time_frame_swp;
	double				time_spawn;
}						t_sprite;

typedef struct			s_texture_data
{
	void				*texture;
	char				*tex_path;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_texture_data;

typedef struct			s_cub3d
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	void				*mlx;
	void				*win;

	int					win_w;
	int					win_h;
	int					max_win_w;
	int					max_win_h;
	int					retina;
	char				**map;
	int					map_w;
	int					map_h;
	int					colors[2];
	int					save;
	t_texture_data		*td;

	double				fps;
	clock_t				time_now;
	int					error;
	int					music_playing;

	int					p_dir;
	double				p_x;
	double				p_y;
	double				p_dir_x;
	double				p_dir_y;
	double				plane_x;
	double				plane_y;
	double				scrn_x;
	int					p_health;
	int					p_bullets;
	double				p_hit;

	int					spd;
	int					w;
	int					s;
	int					a;
	int					d;
	int					l_a;
	int					r_a;
	int					mouse_move;
	int					prev_mouse_x;
	int					shoot;

	int					sprite_n;
	t_sprite			*spr;
	t_visited_squares	*l;
	int					path_steps;
}						t_cub3d;

void					play_music(t_cub3d *t);
void					*terminate(char **s);
void					error_and_exit(t_cub3d *t, char *message);
void					death(t_cub3d *t);
void					exit_cub3d(t_cub3d *t);

void					get_bmp(t_cub3d *t);
void					free_stuff(t_gen_bmp_data *b);
void					bmp_creation_error(t_cub3d *t, t_gen_bmp_data *b);
unsigned int			get_pxl_for_bmp(t_cub3d *t, int x, int y);

void					print_terminal_map(t_cub3d *t);

void					parse_cub_file(t_cub3d *t, int ac, char **av);
char					*copy_file(int fd);
int						check_arguments(t_cub3d *t, int ac, char **av);
int						get_colour(t_cub3d *t, char *file, int *index);
void					check_tex_path(t_cub3d *t, char *tex_path);
void					parse_map(t_cub3d *t, char *file);
void					find_player(t_cub3d *t);
void					find_sprites(t_cub3d *t);
char					**ft_split_var(char *s, t_cub3d *t);
void					get_textures(t_cub3d *t);
void					get_window_resolution(t_cub3d *t, char *file,
						int *index);
unsigned int			ft_getpxl(t_cub3d *t, int i, int x, int y);
void					ft_putpxl(t_cub3d *data, int x, int y, int color);

int						keypress_hook(int keycode, t_cub3d *t);
int						keyrelease_hook(int keycode, t_cub3d *t);
int						mouse_move_hook(int mouse_x, int mouse_y, t_cub3d *t);
int						exit_hook(int keycode, t_cub3d *t);
void					move(t_cub3d *t);
void					turn_left(t_cub3d *t, double rot_spd);
void					turn_right(t_cub3d *t, double rot_spd);

void					draw_background(t_cub3d *t, int sky, int floor);
double					draw_walls(t_cub3d *t, int i);
void					draw_sprites(t_cub3d *t, double *z_buf);
int						get_sprite_frame(t_cub3d *t, int i);
void					draw_floor(t_cub3d *t);
void					draw_skybox(t_cub3d *t);
void					draw_skybox2(t_cub3d *t);

unsigned int			shader(unsigned int start_colour, double distance);
unsigned int			shader_red(unsigned int start_colour);

void					draw_crosshair(t_cub3d *t);
void					draw_torch(t_cub3d *t);
void					draw_gun(t_cub3d *t);
void					draw_red_border(t_cub3d *t);
void					draw_hearts(t_cub3d *t);
void					draw_bullets(t_cub3d *t);

void					sprite_control(t_cub3d *t, int s);
void					enemy_pathfinding(t_cub3d *p, int s);
int						obstacle(char c);
void					move_enemy(t_cub3d *t, int i);

double					get_distance(int y_dest, int x_dest, int y_src,
						int x_src);

void					shoot(t_cub3d *t);

#endif

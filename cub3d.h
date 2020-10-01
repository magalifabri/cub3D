#ifndef LIBFT_H
# define LIBFT_H

# define RD(x) (x * 0.01745329251)

# include "../mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <time.h>

typedef struct  s_visited_squares
{
    int y;
    int x;
    char direction_of_origin;
}               t_visited_squares;

typedef struct  s_sprite_xys
{
  char type;
  double x;
  double y;
  double x_draw;
  double y_draw;
  int dis;
  int alive;
  int counter;
  int health;
  double t_o_d;
  int hit;
  char mode;
  int frame;
}               t_sprite;

typedef struct  s_cub3d 
{
    // mlx
    void *img;
    char *addr[50];
    int  bpp[50];
    int  line_len[50];
    int  endian[50];
    void *mlx;
    void *win;

    int game;
    double fps;
    clock_t time_now;

    // player
    int fov;
    int p_dir;
    double p_x;
    double p_y;
    double p_dir_x;
    double p_dir_y;
    double plane_x;
    double plane_y;
    double scrn_x;
    int p_health;
    int p_bullets;
    double p_hit;

    // raycasting
    double r_dir;
    double d1;
    double d2;
    int start;
    int wsh;
    int tex_x1;
    int tex_x2;
    char face;

    // controls
    int spd;
    int w;
    int s;
    int a;
    int d;
    int l_a;
    int r_a;
    int mouse_move;
    int shoot;
    int prev_mouse_x;

    // cub file parsing
    int win_w;
    int win_h;
    char **map;
    int map_w;
    int map_h;
    char *tex_path[50];
    void *texture[50];
    int colors[2];

    // sprites
    int sprite_n;
    t_sprite *spr;
    t_visited_squares *l;
    int path_steps;
}               t_cub3d;

int main(void);
void ft_init(t_cub3d *t);

int keypress_hook(int keycode, t_cub3d *t);
int keyrelease_hook(int keycode, t_cub3d *t);
int mouse_move_hook(int mouse_x, int mouse_y, t_cub3d *t);
int exit_hook(int keycode, t_cub3d *t);

void move(t_cub3d *t);
void parse_cub_file(t_cub3d *t);
char *copy_file(int fd);
void parse_map(t_cub3d *t, char *file);
char **ft_split_var(char *s, t_cub3d *t);
void get_textures(t_cub3d *t);
unsigned int ft_getpxl(char *addr, int size_line, int bpp, int x, int y);
void ft_putpxl(t_cub3d *data, int x, int y, int color);

double draw_walls(t_cub3d *t, int i);
void draw_sprites(t_cub3d *t, double *z_buf);
void draw_floors(t_cub3d *t);
void draw_skybox(t_cub3d *t);
void draw_skybox2(t_cub3d *t);

unsigned int shader(unsigned int start_colour, double distance);
void play_music(void);

void find_path(t_cub3d *p);
double get_distance(int y_dest, int x_dest, int y_src, int x_src);

void draw_crosshair(t_cub3d *t);
void draw_torch(t_cub3d *t);
void draw_gun(t_cub3d *t);
void draw_red_border(t_cub3d *t);
void draw_hearts(t_cub3d *t);
void draw_bullets(t_cub3d *t);

void cast_ray(t_cub3d *t);

unsigned int shader_red(unsigned int start_colour);

#endif

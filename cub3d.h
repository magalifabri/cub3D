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

typedef struct  s_sprite_xys
{
  int y;
  int x;
  int dis;
}               t_sprite;

typedef struct  s_cub3d 
{
    // mlx
    void *img;
    char *addr[9];
    int  bpp[9];
    int  line_len[9];
    int  endian[9];
    void *mlx;
    void *win;

    int game;
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
    // cub file parsing
    int win_w;
    int win_h;
    char **map;
    int map_w;
    int map_h;
    char *tex_path[9];
    int colors[2];
    void    *texture[8];
    //sprites
    // int sprite_coords[2];
    // char side;
    // int *sprite_xys;
    int sprite_n;
    t_sprite *spr;
    // double *z_buf;
}               t_cub3d;

int main(void);
void ft_init(t_cub3d *t);
int ft_keypress(int keycode, t_cub3d *t);
int ft_keyrelease(int keycode, t_cub3d *t);
int mouse_move_hook(int mouse_x);
int exit_hook(int keycode, t_cub3d *t);
void ft_move(t_cub3d *t);
void ft_cub_file_parser(t_cub3d *t);
char *ft_copy_file(int fd);
void ft_map_parser(t_cub3d *t, char *file);
char **ft_split_var(char *s, t_cub3d *t);
void get_textures(t_cub3d *t);
unsigned int	ft_getpxl(char *addr, int size_line, int bpp, int x, int y);
void ft_putpxl(t_cub3d *data, int x, int y, int color);
double ft_walls(t_cub3d *t, int i);
void put_sprites(t_cub3d *t, double *z_buf);
void put_floors(t_cub3d *t);
void put_skybox(t_cub3d *t);
void put_skybox2(t_cub3d *t);
unsigned int shader(unsigned int start_colour, double distance);

#endif

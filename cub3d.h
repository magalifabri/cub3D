#ifndef LIBFT_H
# define LIBFT_H

# include "../mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct  s_sprite_xys
{
  int y;
  int x;
  int dis;
}               sprite;

typedef struct  s_cub3d 
{
    // mlx
    void *img;
    char *addr[6];
    int  bpp[6];
    int  line_len[6];
    int  endian[6];
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
    char *tex_path[6];
    int colors[2];
    void    *texture[5];
    //sprites
    // int sprite_coords[2];
    // char side;
    // int *sprite_xys;
    int sprite_n;
    sprite *spr;
    // double *z_buf;
}               cub3d;

int main(void);
void ft_init(cub3d *t);
int ft_keypress(int keycode, cub3d *t);
int ft_keyrelease(int keycode, cub3d *t);
int exit_hook(int keycode, cub3d *t);
void ft_move(cub3d *t);
void ft_cub_file_parser(cub3d *t);
char *ft_copy_file(int fd);
void ft_map_parser(cub3d *t, char *file);
char **ft_split_var(char *s, cub3d *t);
void    ft_textures(cub3d *t);
unsigned int	ft_getpxl(char *addr, int size_line, int bpp, int x, int y);
void ft_putpxl(cub3d *data, int x, int y, int color);
double ft_walls(cub3d *t, int i);
void put_sprites(cub3d *t, double *z_buf);
void put_floors(cub3d *t);

#endif

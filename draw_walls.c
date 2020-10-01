#include "cub3d.h"

typedef struct s_put_walls_variables
{
    double r_dir_x;
    double r_dir_y;
    int map_x;
    int map_y;
    double side_dist_x; //length of ray from current position to next x or y-side
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int draw_start;
    int draw_end;
    int tex_nbr;
    double wall_x;
    double step;
    double tex_pos;
    int tex_x;
    int line_height;
    int step_x; //what direction to step in x or y-direction (either +1 or -1)
    int step_y;
    int side; //was a NS or a EW wall hit?
    unsigned int texel;
} t_pwv;

static void make_calculations_3(t_cub3d *t, t_pwv *w)
{
    if (w->r_dir_x >= 0 && w->side == 0) //choose texture
        w->tex_nbr = 1; // west-facing: blue
    else if (w->r_dir_x < 0 && w->side == 0)
        w->tex_nbr = 2; // east-facing: green
    else if (w->r_dir_y >= 0 && w->side == 1)
        w->tex_nbr = 3; // south-facing: brown
    else if (w->r_dir_y < 0 && w->side == 1)
        w->tex_nbr = 4; // noth-facing: yellow
    w->wall_x = (w->side == 0) ? (t->p_y + w->perp_wall_dist * w->r_dir_y)
    : (t->p_x + w->perp_wall_dist * w->r_dir_x);
    w->wall_x -= floor((w->wall_x));
    w->tex_x = (int)(w->wall_x * (double)64); //x coordinate on the texture
    if ((w->side == 0 && w->r_dir_x > 0) || (w->side == 1 && w->r_dir_y < 0))
        w->tex_x = 64 - w->tex_x - 1;
    w->step = 1.0 * 64 / w->line_height; // How much to increase the texture coordinate per screen pixel
    w->tex_pos = (w->draw_start - t->win_h / 2 + w->line_height / 2) * w->step; // Starting texture coordinate
}

static void make_calculations_2(t_cub3d *t, t_pwv *w)
{
    while (t->map[w->map_y][w->map_x] != '1') //jump to next map square, OR in x-direction, OR in y-direction
    {
        if (w->side_dist_x < w->side_dist_y)
        {
            w->side_dist_x += w->delta_dist_x;
            w->map_x += w->step_x;
            w->side = 0;
        }
        else
        {
            w->side_dist_y += w->delta_dist_y;
            w->map_y += w->step_y;
            w->side = 1;
        }
    }
    w->perp_wall_dist = (w->side == 0) 
    ? (w->map_x - t->p_x + (1 - w->step_x) / 2) / w->r_dir_x
    : (w->map_y - t->p_y + (1 - w->step_y) / 2) / w->r_dir_y;
    w->line_height = (int)(t->win_h / w->perp_wall_dist); //Calculate height of line to draw on screen
    w->draw_start = -w->line_height / 2 + t->win_h / 2; //calculate lowest and highest pixel to fill in current stripe
    w->draw_start = (w->draw_start < 0) ? (0) : (w->draw_start);
    w->draw_end = w->line_height / 2 + t->win_h / 2;
    w->draw_end = (w->draw_end >= t->win_h) ? (t->win_h - 1) : (w->draw_end);
}

static void make_calculations_1(t_cub3d *t, t_pwv *w)
{
    if (w->r_dir_x < 0) //calculate step and initial sideDist
    {
        w->step_x = -1;
        w->side_dist_x = (t->p_x - w->map_x) * w->delta_dist_x;
    }
    else
    {
        w->step_x = 1;
        w->side_dist_x = (w->map_x + 1.0 - t->p_x) * w->delta_dist_x;
    }
    if (w->r_dir_y < 0)
    {
        w->step_y = -1;
        w->side_dist_y = (t->p_y - w->map_y) * w->delta_dist_y;
    }
    else
    {
        w->step_y = 1;
        w->side_dist_y = (w->map_y + 1.0 - t->p_y) * w->delta_dist_y;
    }
}

double draw_walls(t_cub3d *t, int x)
{
    t_pwv w;
    int y;

    t->scrn_x = 2 * x / (double)t->win_w - 1;
    w.r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
    w.r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
    w.map_x = (int)t->p_x; //which box of the map we're in
    w.map_y = (int)t->p_y;
    w.delta_dist_x = fabs(1 / w.r_dir_x); //length of ray from one x or y-side to next x or y-side
    w.delta_dist_y = fabs(1 / w.r_dir_y);
    make_calculations_1(t, &w);
    make_calculations_2(t, &w);
    make_calculations_3(t, &w);
    y = -1;
    while (++y < w.line_height && y < t->win_h)
    {
        w.texel = ft_getpxl(t->addr[w.tex_nbr], t->line_len[w.tex_nbr], t->bpp[w.tex_nbr], w.tex_x, w.tex_pos + (w.step * y));
        // w.texel = shader(w.texel, w.perp_wall_dist);
        if (w.texel != 4278190080)
            ft_putpxl(t, x, w.draw_start + y, w.texel);
    }
    return (w.perp_wall_dist);
}

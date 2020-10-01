#include "cub3d.h"

typedef struct s_put_skybox_variables
{
    double r_dir_x;
    double r_dir_y;
    double r_degree;
    int tex_x;
    double tex_y_incr;
} t_psv;

void put_skybox(t_cub3d *t)
{
    t_psv s;
    int x;
    int y;
    static double j;

    x = -1;
    while (++x < t->win_w)
    {
        t->scrn_x = 2 * x / (double)t->win_w - 1;
        s.r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
        s.r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
        s.r_degree = atan(s.r_dir_y / s.r_dir_x) * 180 / M_PI; // calc degree
        if (s.r_dir_x >= 0 && s.r_dir_y <= 0) // -90 - 0 > 0 - 90
            s.r_degree = s.r_degree + 90;
        else if (s.r_dir_x > 0 && s.r_dir_y > 0) // 0 - 90 > 90 - 180
            s.r_degree = s.r_degree + 90;
        else if (s.r_dir_x < 0 && s.r_dir_y > 270) // -90 - 0 > 180 - 270
            s.r_degree = s.r_degree + 0;
        else if (s.r_dir_x < 0 && s.r_dir_y < 270) // 0 - 90 > 180 - 270
            s.r_degree = s.r_degree + 270;
        s.tex_x = ((1024) / (t->win_h / 2)) * (s.r_degree + j); // calc x starting point in texture
        if (s.tex_x > 1024)
            return ;
        s.tex_y_incr = (128.0 / (t->win_h / 2)); // calc y incrementation for texture
        // s.tex_y_incr = 128.0 / (t->win_h / 2); // calc y incrementation for texture
        y = -1;
        while (++y < t->win_h / 2)
            ft_putpxl(t, x, y, ft_getpxl(t->addr[6], t->line_len[6], t->bpp[6], s.tex_x, y * s.tex_y_incr));
    }
    // j = j + 0.25;
    j = (j > 360.0) ? 0 : j;
}

void put_skybox2(t_cub3d *t)
{
    t_psv s;
    int x;
    int y;
    static double j;
    unsigned int texel;

    x = -1;
    while (++x < t->win_w)
    {
        t->scrn_x = 2 * x / (double)t->win_w - 1;
        s.r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
        s.r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);
        s.r_degree = atan(s.r_dir_y / s.r_dir_x) * 180 / M_PI; // calc degree
        if (s.r_dir_x >= 0 && s.r_dir_y <= 0) // -90 - 0 > 0 - 90
            s.r_degree = s.r_degree + 90;
        else if (s.r_dir_x > 0 && s.r_dir_y > 0) // 0 - 90 > 90 - 180
            s.r_degree = s.r_degree + 90;
        else if (s.r_dir_x < 0 && s.r_dir_y > 270) // -90 - 0 > 180 - 270
            s.r_degree = s.r_degree + 0;
        else if (s.r_dir_x < 0 && s.r_dir_y < 270) // 0 - 90 > 180 - 270
            s.r_degree = s.r_degree + 270;
        s.tex_x = (1024.0 / 360.0) * (s.r_degree + j); // calc x starting point in texture
        // if (s.tex_x > 1024)
        //     return ;
        s.tex_y_incr = (128.0 / (t->win_h / 2)); // calc y incrementation for texture
        // s.tex_y_incr = 128.0 / (t->win_h / 2); // calc y incrementation for texture
        y = -1;
        while (++y < t->win_h / 2)
        {
            texel = ft_getpxl(t->addr[8], t->line_len[8],
            t->bpp[8], s.tex_x, y * s.tex_y_incr);
            if (texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
                ft_putpxl(t, x, y, texel);
            // ft_putpxl(t, x, y, ft_getpxl(t->addr[8], t->line_len[8], t->bpp[8], s.tex_x, y * s.tex_y_incr));
        }
    }
    j = j + 0.05;
    j = (j > 360.0) ? 0 : j;
}
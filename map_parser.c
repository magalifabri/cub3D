#include "cub3d.h"

static int ft_charset (char i)
{
    return (i == '0' || i == '1' || i == '2' || i == 'N' || i == 'S' || i == 'E'
    || i == 'W' || i == ' ' || i == '\n');
}

static int ft_get_height(char *map)
{
    int len;

    len = 1;
    while (*map && ft_charset(*map))
        if (*map++ == '\n')
            len++;
    return (len);
}

static int ft_get_width(char *map)
{
    int i;
    int wid;

    i = 0;
    wid = 0;
    while (*map)
    {
        if (*map++ == '\n')
        {
            wid = (i > wid) ? (i) : (wid);
            i = 0;
            map++;
        }
        i++;
    }
    return (wid);
}

static void ft_find_player(cub3d *t)
{
    int y;
    int x;

    y = -1;
    while (++y < t->map_h)
    {
        x = -1;
        while (++x < t->map_w)
        {
            if (t->map[y][x] == 'N' || t->map[y][x] == 'E' 
            || t->map[y][x] == 'S' || t->map[y][x] == 'W')
            {
                t->p_y = y;
                t->p_x = x;
                if (t->map[y][x] == 'N')
                {
                    t->p_dir_x = 0;
                    t->p_dir_y = -1;
                    t->plane_x = 0.66;
                    t->plane_y = 0;
                }
                else if (t->map[y][x] == 'E')
                {
                    t->p_dir_x = 1;
                    t->p_dir_y = 0;
                    t->plane_x = 0;
                    t->plane_y = 0.66;
                }
                else if (t->map[y][x] == 'S')
                {
                    t->p_dir_x = 0;
                    t->p_dir_y = 1;
                    t->plane_x = -0.66;
                    t->plane_y = 0;
                }
                else
                {
                    t->p_dir_x = -1;
                    t->p_dir_y = 0;
                    t->plane_x = 0;
                    t->plane_y = -0.66;
                }
                return ;
            }
        }
    }
}

static void sprites(cub3d *t)
{
    int y;
    int x;

    t->sprite_n = 0;
    y = -1;
    while (++y < t->map_h)
    {
        x = -1;
        while (++x < t->map_w)
            if (t->map[y][x] == '2')
                t->sprite_n++;
    }
    
    int i;

    t->spr = malloc(sizeof(sprite) * t->sprite_n);
    i = 0;
    y = -1;
    while (++y < t->map_h)
    {
        x = -1;
        while (++x < t->map_w)
        {
            if (t->map[y][x] == '2')
            {
                t->spr[i].y = y;
                t->spr[i++].x = x;
            }
        }
    }
    t->spr[i].y = t->map_h;
}

void ft_map_parser(cub3d *t, char *file)
{
    t->map_w = ft_get_width(file);
    printf("width = %d\n", t->map_w);
    t->map_h = ft_get_height(file);
    printf("length = %d\n", t->map_h);
    t->map = ft_split_var(file, t);
    ft_find_player(t);
    sprites(t);

    int i = 0;
    while (t->spr[i].y != t->map_h)
    {
        printf("%d, %d\n", t->spr[i].y, t->spr[i].x);
        i++;
    }
    
    int y = 0;
    int x = 0;
    while (y < t->map_h)
    {
        while (x <= t->map_w)
        {
            printf("%c", t->map[y][x]);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
}

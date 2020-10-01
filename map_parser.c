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
                t->p_y = y * 64;
                t->p_x = x * 64;
                (t->map[y][x] == 'N') && (t->p_dir = 90);
                (t->map[y][x] == 'E') && (t->p_dir = 0);
                (t->map[y][x] == 'S') && (t->p_dir = 270);
                (t->map[y][x] == 'W') && (t->p_dir = 180);
                return ;
            }
        }
    }
}

void ft_map_parser(cub3d *t, char *file)
{
    t->map_w = ft_get_width(file);
    printf("width = %d\n", t->map_w);
    t->map_h = ft_get_height(file);
    printf("length = %d\n", t->map_h);
    t->map = ft_split_var(file, t);
    ft_find_player(t);
    
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

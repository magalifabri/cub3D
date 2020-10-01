#include "cub3d.h"

static int check_charset (char i)
{
    return (i == '0' || i == '1' || i == '2' || i == 'N' || i == 'S' || i == 'E'
    || i == 'W' || i == ' ' || i == '\n');
}

static int get_height(char *map)
{
    int len;

    len = 1;
    while (*map && check_charset(*map))
        if (*map++ == '\n')
            len++;
    return (len);
}

static int get_width(char *map)
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

static void find_player_part_2(t_cub3d *t, int y, int x)
{
    if (t->map[y][x] == 'N')
    {
        t->p_dir_y = -1;
        t->plane_x = 0.66;
    }
    else if (t->map[y][x] == 'E')
    {
        t->p_dir_x = 1;
        t->plane_y = 0.66;
    }
    else if (t->map[y][x] == 'S')
    {
        t->p_dir_y = 1;
        t->plane_x = -0.66;
    }
    else
    {
        t->p_dir_x = -1;
        t->plane_y = -0.66;
    }
}

static void find_player(t_cub3d *t)
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
                find_player_part_2(t, y, x);
                return ;
            }
        }
    }
}

static void find_sprites_part_2(t_cub3d *t)
{
    int y;
    int x;
    int i;

    t->spr = malloc(sizeof(t_sprite) * t->sprite_n);
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
                t->spr[i].x = x;
                t->spr[i].counter = 0;
                t->spr[i].health = 3;
                t->spr[i].hit = 0;
                printf("location of sprite %d: %f, %f\n", i, t->spr[i].y, t->spr[i].x);
                // printf("%d\n", t->spr[i].x);
                t->spr[i++].alive = 1; // for enemies
            }
        }
    }
    // t->spr[i].y = t->map_h;
}

static void find_sprites(t_cub3d *t)
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
    printf("map_w = %d, map_h = %d\n", t->map_w, t->map_h);
    printf("number of sprites = %d\n", t->sprite_n);
    if (t->sprite_n != 0)
        find_sprites_part_2(t);
}

void parse_map(t_cub3d *t, char *file)
{
    t->map_w = get_width(file);
    printf("width = %d\n", t->map_w);
    t->map_h = get_height(file);
    printf("length = %d\n", t->map_h);
    t->map = ft_split_var(file, t);
    find_player(t);
    find_sprites(t);

    // int i = 0;
    // while (t->spr[i].y != t->map_h)
    // {
    //     printf("%d, %d\n", t->spr[i].y, t->spr[i].x);
    //     i++;
    // }
    
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

#include "cub3d.h"

static int check_charset (char i)
{
    return (i == '0' || i == '1' || i == '2' || i == '3' || i == '5' || i == 'N' || i == 'S' || i == 'E'
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
            if (t->map[y][x] == '2' || t->map[y][x] == '3' || t->map[y][x] == '5')
            {
                t->spr[i].type = t->map[y][x];
                t->spr[i].y = y;
                t->spr[i].x = x;
                t->spr[i].y_draw = 0;
                t->spr[i].x_draw = 0;
                t->spr[i].counter = 0;
                t->spr[i].frame = 0;
                t->spr[i].hit = 0;
                if (t->spr[i].type == '3')
                {
                    t->spr[i].health = 3;
                    t->spr[i].alive = 1;
                    t->spr[i].mode = 'i';
                }
                if (t->spr[i].type == '5')
                {
                    t->spr[i].health = 3;
                    t->spr[i].alive = 1;
                }
                printf("location of sprite %d of type %c: %f, %f\n", i, t->spr[i].type, t->spr[i].y, t->spr[i].x);
                i++;
            }
        }
    }
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
            if (t->map[y][x] == '2' || t->map[y][x] == '3' || t->map[y][x] == '5')
                t->sprite_n++;
    }
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

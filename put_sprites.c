#include "cub3d.h"

static void sort_sprites(cub3d *t)
{
    int i;
    int j;
    sprite tmp;

    i = -1;
    while (++i < t->sprite_n)
        t->spr[i].dis = ((t->p_x - t->spr[i].x) * (t->p_x - t->spr[i].x) + (t->p_y - t->spr[i].y) * (t->p_y - t->spr[i].y));

    // i = 0;
    // if (t->r_dir == t->p_dir)
    // {
    //     while (t->spr[i].y != t->map_h)
    //     {
    //         printf("before: i = %d, dis = %d\n", i, t->spr[i].dis);
    //         i++;
    //     }
    // }

    i = 0;
    j = 1;
    while (t->spr[i + 1].y != t->map_h)
    {
        while (t->spr[j].y != t->map_h)
        {
            if (t->spr[i].dis < t->spr[j].dis)
            {
                tmp = t->spr[j];
                t->spr[j] = t->spr[i];
                t->spr[i] = tmp;
            }
            j++;
        }
        i++;
        j = i + 1;
    }

    // i = 0;
    // if (t->r_dir == t->p_dir)
    // {
    //     while (t->spr[i].y != t->map_h)
    //     {
    //         printf("after: i = %d, dis = %d\n", i, t->spr[i].dis);
    //         i++;
    //     }
    // }
}

void put_sprites(cub3d *t, double *z_buf)
{
    int i = 0;

    sort_sprites(t);
    while (t->spr[i].y != t->map_h)
    {
        double sprite_y = t->spr[i].y + 0.5;
        double sprite_x = t->spr[i++].x + 0.5;
        
        //translate sprite position to relative to camera
        double spriteX = sprite_x - t->p_x;
        double spriteY = sprite_y - t->p_y;
        // double spriteX = sprite[spriteOrder[i]].x - t->p_dir_x;
        // double spriteY = sprite[spriteOrder[i]].y - t->p_dir_y;

        // printf("x = %f, y = %f\n", spriteX, spriteY);

        double invDet = 1.0 / (t->plane_x * t->p_dir_y - t->p_dir_x * t->plane_y); //required for correct matrix multiplication

        double transformX = invDet * (t->p_dir_y * spriteX - t->p_dir_x * spriteY);
        double transformY = invDet * (-t->plane_y * spriteX + t->plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

        int spriteScreenX = (int)((t->win_w / 2) * (1 + transformX / transformY));

        //calculate height of the sprite on screen
        int spriteHeight = abs((int)(t->win_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + t->win_h / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + t->win_h / 2;
        if (drawEndY >= t->win_h)
            drawEndY = t->win_h - 1;
        //calculate width of the sprite
        int spriteWidth = abs((int)(t->win_h / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX >= t->win_w)
            drawEndX = t->win_w - 1;

        // int j;
        int stripe = drawStartX;
        unsigned int texel;

        while (stripe < drawEndX)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
            if (transformY > 0 && stripe > 0 && stripe < t->win_w && transformY < z_buf[stripe])
            {
                int y = drawStartY;
                while (y < drawEndY)
                {
                    int d = (y)*256 - t->win_h * 128 + spriteHeight * 128;
                    int texY = ((d * 64) / spriteHeight) / 256;
                    texel = ft_getpxl(t->addr[5], t->line_len[5],
                    t->bpp[5], texX, texY);
                    if (texel != 4278190080 && (t->tex_x1 >= 0 && t->tex_x1 < 64))
                        ft_putpxl(t, stripe, y, texel); 
                    y++;  
                }
            }
            stripe++;
        }
    }
}
#include "cub3d.h"

double ft_walls(cub3d *t, int i)
{
    double r_dir_x;
    double r_dir_y;

    t->scrn_x = 2 * i / (double)t->win_w - 1;
    r_dir_x = t->p_dir_x + (t->plane_x * t->scrn_x);
    r_dir_y = t->p_dir_y + (t->plane_y * t->scrn_x);

    //which box of the map we're in
    int map_x = (int)t->p_x;
    int map_y = (int)t->p_y;

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = fabs(1 / r_dir_x);
    double deltaDistY = fabs(1 / r_dir_y);

    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side;    //was a NS or a EW wall hit?

    //calculate step and initial sideDist
    if (r_dir_x < 0)
    {
        stepX = -1;
        sideDistX = (t->p_x - map_x) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (map_x + 1.0 - t->p_x) * deltaDistX;
    }
    if (r_dir_y < 0)
    {
        stepY = -1;
        sideDistY = (t->p_y - map_y) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (map_y + 1.0 - t->p_y) * deltaDistY;
    }

    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            map_x += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            map_y += stepY;
            side = 1;
        }
        if (t->map[map_y][map_x] == '1')
            hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (side == 0)
        perpWallDist = (map_x - t->p_x + (1 - stepX) / 2) / r_dir_x;
    else
        perpWallDist = (map_y - t->p_y + (1 - stepY) / 2) / r_dir_y;
    
    // write(1, "a\n", 2);
    // printf("i = %d, pwd = %f\n", i, perpWallDist);
    // *z_buf[i] = perpWallDist;
    // write(1, "b\n", 2);

    //Calculate height of line to draw on screen
    int lineHeight = (int)(t->win_h / perpWallDist);

    //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + t->win_h / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + t->win_h / 2;
    if (drawEnd >= t->win_h)
        drawEnd = t->win_h - 1;

    //choose texture
    int texNum;
    if (r_dir_x >= 0 && side == 0)
        texNum = 1; // west-facing: blue
    if (r_dir_x < 0 && side == 0)
        texNum = 2; // east-facing: green
    if (r_dir_y >= 0 && side == 1)
        texNum = 3; // south-facing: brown
    if (r_dir_y < 0 && side == 1)
        texNum = 4; // noth-facing: yellow

    //calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (side == 0)
        wallX = t->p_y + perpWallDist * r_dir_y;
    else
        wallX = t->p_x + perpWallDist * r_dir_x;
    wallX -= floor((wallX));

    //x coordinate on the texture
    int texX = (int)(wallX * (double)64);
    if (side == 0 && r_dir_x > 0)
        texX = 64 - texX - 1;
    if (side == 1 && r_dir_y < 0)
        texX = 64 - texX - 1;

    // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * 64 / lineHeight;
    // Starting texture coordinate
    double texPos = (drawStart - t->win_h / 2 + lineHeight / 2) * step;

    int j;
    j = -1;
    while (++j < lineHeight && j < t->win_h)
        ft_putpxl(t, i, drawStart + j, ft_getpxl(t->addr[texNum], t->line_len[texNum], t->bpp[texNum], texX, texPos + (step * j)));

    // COLOURS

    // int colour;
    // if (r_dir_x >= 0 && side == 0)
    //     colour = 0x004DC1F3; // west-facing: blue
    // if (r_dir_x < 0 && side == 0)
    //     colour = 0x0083D44D; // east-facing: green
    // if (r_dir_y >= 0 && side == 1)
    //     colour = 0x0073491A; // south-facing: brown
    // if (r_dir_y < 0 && side == 1)
    //     colour = 0x00F2DD59; // noth-facing: yellow

    // int j;
    // j = 0;
    // while (j < lineHeight && j < t->win_h)
    //     ft_putpxl(t, i, drawStart + j++, colour);
    
    return (perpWallDist);
}
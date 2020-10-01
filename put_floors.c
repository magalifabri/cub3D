#include "cub3d.h"

void put_floors(cub3d *t)
{
    int y;

    y = t->win_h / 2;
    while (++y < t->win_h)
    {
        // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
        float r_dir_x0 = t->p_dir_x - t->plane_x;
        float r_dir_y0 = t->p_dir_y - t->plane_y;
        float r_dir_x1 = t->p_dir_x + t->plane_x;
        float r_dir_y1 = t->p_dir_y + t->plane_y;

        // Current y position compared to the center of the screen (the horizon)
        int p = y - t->win_h / 2;

        // Vertical position of the camera.
        float posZ = 0.5 * t->win_h;

        // Horizontal distance from the camera to the floor for the current row.
        // 0.5 is the z position exactly in the middle between floor and ceiling.
        float rowDistance = posZ / p;

        // calculate the real world step vector we have to add for each x (parallel to camera plane)
        // adding step by step avoids multiplications with a weight in the inner loop
        float floorStepX = rowDistance * (r_dir_x1 - r_dir_x0) / t->win_w;
        float floorStepY = rowDistance * (r_dir_y1 - r_dir_y0) / t->win_w;

        // real world coordinates of the leftmost column. This will be updated as we step to the right.
        float floorX = t->p_x + rowDistance * r_dir_x0;
        float floorY = t->p_y + rowDistance * r_dir_y0;

        int x = -1;
        while (++x < t->win_w)
        {
            // the cell coord is simply got from the integer parts of floorX and floorY
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            // get the texture coordinate from the fractional part
            int tx = (int)(64 * (floorX - cellX)) & (64 - 1);
            int ty = (int)(64 * (floorY - cellY)) & (64 - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // // choose texture and draw the pixel
            // int floorTexture = 3;
            // int ceilingTexture = 6;
            // Uint32 color;

            // // floor
            // color = texture[floorTexture][64 * ty + tx];
            // color = (color >> 1) & 8355711; // make a bit darker
            // buffer[y][x] = color;

            // //ceiling (symmetrical, at t->win_h - y - 1 instead of y)
            // color = texture[ceilingTexture][64 * ty + tx];
            // color = (color >> 1) & 8355711; // make a bit darker
            // buffer[t->win_h - y - 1][x] = color;

            // int j;
            // j = -1;
            // while (++j < lineHeight && j < t->win_h)
                ft_putpxl(t, x, y, ft_getpxl(t->addr[3], t->line_len[3], t->bpp[3], tx, ty));
            // while (++j < lineHeight && j < t->win_h)
            //     ft_putpxl(t, i, drawStart + j, ft_getpxl(t->addr[4], t->line_len[4], t->bpp[4], texX, texPos + (step * j)));

        }
    }
}
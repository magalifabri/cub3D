#include "cub3d.h"

unsigned int	ft_getpxl(char *addr, int size_line, int bpp, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = addr + (y * size_line + x * (bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

unsigned int shader(unsigned int start_colour, double distance)
{
    int end_colour;
    int end_colour_r;
    int end_colour_g;
    int end_colour_b;
    double shade;

    if (start_colour == 4278190080)
        return (start_colour);
    shade = (7.5 - distance) / 10.0;
    shade = (shade < 0) ? (0.01) : (shade);
    end_colour_r = ((start_colour & 0x00FF0000) >> 16) * shade;
    end_colour_g = ((start_colour & 0x0000FF00) >> 8) * shade;
    end_colour_b = (start_colour & 0x000000FF) * shade;
    return (end_colour = (end_colour_r << 16) + (end_colour_g << 8) + end_colour_b);
}

// unsigned int shader(unsigned int start_colour)
// {
//     return ((((start_colour & 0x00FF0000) >> 17) << 16)
//      + (((start_colour & 0x0000FF00) >> 9) << 8)
//      + ((start_colour & 0x000000FF) >> 1));
// }

void            get_textures(t_cub3d *t)
{
    int     img_width[8];
    int     img_height[8];
    unsigned int texel;
    unsigned int i;

    t->tex_path[5] = "./textures/night_sky_long.xpm"; // skybox
    t->tex_path[6] = "./textures/hay_block_top.xpm"; // floor
    t->tex_path[7] = "./textures/clouds4.xpm"; // moving skybox overlay
    i = 1;
    while (i < 9)
    {
        t->texture[i - 1] = mlx_xpm_file_to_image(t->mlx, t->tex_path[i - 1], &img_width[i - 1], &img_height[i - 1]);
        t->addr[i] = mlx_get_data_addr(t->texture[i - 1], &t->bpp[i], &t->line_len[i], &t->endian[i]);
        texel = ft_getpxl(t->addr[i], t->line_len[i], t->bpp[i], 2, 2);
        printf("%u\n", texel);
        i++;
    }
}
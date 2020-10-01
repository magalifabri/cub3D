#include "cub3d.h"

unsigned int	ft_getpxl(char *addr, int size_line, int bpp, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = addr + (y * size_line + x * (bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

unsigned int shader_red(unsigned int start_colour)
{
    int end_colour;
    int end_colour_r;
    int end_colour_g;
    int end_colour_b;
    // double shade;

    if (start_colour == 4278190080)
        return (start_colour);
    // shade = (7.5 - distance) / 10.0;
    // shade = (shade < 0) ? (0.01) : (shade);
    end_colour_r = ((start_colour & 0x0000FF00) >> 8) * 1;
    end_colour_g = ((start_colour & 0x0000FF00) >> 8) * 0.5;
    end_colour_b = (start_colour & 0x000000FF) * 0.5;
    return (end_colour = (end_colour_r << 16) + (end_colour_g << 8) + end_colour_b);
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

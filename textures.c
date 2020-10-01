#include "cub3d.h"

unsigned int	ft_getpxl(char *addr, int size_line, int bpp, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = addr + (y * size_line + x * (bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}
 
void            ft_textures(cub3d *t)
{
    int     img_width[5];
    int     img_height[5];
    unsigned int texel;
    unsigned int i;

    i = 1;
    while (i < 6)
    {
        t->texture[i - 1] = mlx_xpm_file_to_image(t->mlx, t->tex_path[i - 1], &img_width[i - 1], &img_height[i - 1]);
        t->addr[i] = mlx_get_data_addr(t->texture[i - 1], &t->bpp[i], &t->line_len[i], &t->endian[i]);
        texel = ft_getpxl(t->addr[i], t->line_len[i], t->bpp[i], 2, 2);
        printf("%u\n", texel);
        i++;
    }
}
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

    if (start_colour == 4278190080 || start_colour == 16711680)
        return (start_colour);
    shade = (10 - distance) / 10.0;
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

void            get_extra_texture_paths1(t_cub3d *t)
{
    t->tex_path[5] = "./textures/night_sky_long.xpm"; // skybox
    t->tex_path[6] = "./textures/surfaces/dirt_dark.xpm"; // floor
    t->tex_path[7] = "./textures/clouds4.xpm"; // moving skybox overlay
    t->tex_path[8] = "./textures/sprite_crosshair2.xpm";
    t->tex_path[9] = "./textures/sprite_bat/bat1.2.1.xpm";
    t->tex_path[10] = "./textures/sprite_bat/bat1.2.2.xpm";
    t->tex_path[11] = "./textures/sprite_bat/bat1.2.3.xpm";
    t->tex_path[12] = "./textures/sprite_bat/bat1.2.4.xpm";
    t->tex_path[13] = "./textures/sprite_torch/sprite_torch1.xpm";
    t->tex_path[14] = "./textures/sprite_torch/sprite_torch2.xpm";
    t->tex_path[15] = "./textures/sprite_torch/sprite_torch3.xpm";
    t->tex_path[16] = "./textures/sprite_torch/sprite_torch4.xpm";
    t->tex_path[17] = "./textures/sprite_gun/sprite_gun1.xpm";
    t->tex_path[18] = "./textures/sprite_gun/sprite_gun2.xpm";
    t->tex_path[19] = "./textures/sprite_gun/sprite_gun3.xpm";
    t->tex_path[20] = "./textures/sprite_gun/sprite_gun4.xpm";
    t->tex_path[21] = "./textures/sprite_death/sprite_blood_splatter1.xpm";
    t->tex_path[22] = "./textures/sprite_death/sprite_blood_splatter2.xpm";
    t->tex_path[23] = "./textures/sprite_spider/walk/sprite_spiderv3.1.xpm";
    t->tex_path[24] = "./textures/sprite_spider/walk/sprite_spiderv3.2.xpm";
    t->tex_path[25] = "./textures/sprite_spider/walk/sprite_spiderv3.3.xpm";
    t->tex_path[26] = "./textures/sprite_spider/walk/sprite_spiderv3.4.xpm";
    t->tex_path[27] = "./textures/sprite_spider/walk/sprite_spiderv3.5.xpm";
    t->tex_path[28] = "./textures/sprite_spider/walk/sprite_spiderv3.6.xpm";
}

void            get_extra_texture_paths2(t_cub3d *t)
{
    t->tex_path[29] = "./textures/sprite_spider/attack/sprite_spider_attack1.xpm";
    t->tex_path[30] = "./textures/sprite_spider/attack/sprite_spider_attack2.xpm";
    t->tex_path[31] = "./textures/sprite_spider/attack/sprite_spider_attack3.xpm";
    t->tex_path[32] = "./textures/sprite_spider/attack/sprite_spider_attack4.xpm";
    t->tex_path[33] = "./textures/sprite_spider/attack/sprite_spider_attack5.xpm";
    t->tex_path[34] = "./textures/heart/sprite_heart1.xpm";
    t->tex_path[35] = "./textures/heart/sprite_heart2.xpm";
    t->tex_path[36] = "./textures/heart/sprite_heart3.xpm";
    t->tex_path[37] = "./textures/heart/sprite_heart4.xpm";
    t->tex_path[38] = "./textures/sprite_bullet2.xpm";
    t->tex_path[39] = "./textures/sprite_bullets/sprite_bullets1.xpm";
    t->tex_path[40] = "./textures/sprite_bullets/sprite_bullets2.xpm";
    t->tex_path[41] = "./textures/sprite_bullets/sprite_bullets3.xpm";
    t->tex_path[42] = "./textures/sprite_bullets/sprite_bullets4.xpm";
    t->tex_path[43] = "./textures/sprite_spider/sprite_spider_nest.xpm";
}

void            get_textures(t_cub3d *t)
{
    int     img_width[50];
    int     img_height[50];
    unsigned int i;
    // unsigned int texel;

    get_extra_texture_paths1(t);
    get_extra_texture_paths2(t);
    i = 1;
    while (i < 45)
    {
        t->texture[i - 1] = mlx_xpm_file_to_image(t->mlx, t->tex_path[i - 1], &img_width[i - 1], &img_height[i - 1]);
        printf("%d\n", (int)t->texture[i - 1]);
		t->addr[i] = mlx_get_data_addr(t->texture[i - 1], &t->bpp[i], &t->line_len[i], &t->endian[i]);
        // texel = ft_getpxl(t->addr[i], t->line_len[i], t->bpp[i], 2, 2);
        // printf("texture %d, %u\n", i, texel);
        i++;
    }
    printf("loading textures complete\n");
}
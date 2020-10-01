#include "cub3d.h"

static void		get_extra_texture_paths1(t_cub3d *t)
{
	t->td[5].tex_path = "./textures/night_sky_long.xpm";
	t->td[6].tex_path = "./textures/surfaces/dirt_dark.xpm";
	t->td[7].tex_path = "./textures/clouds4.xpm";
	t->td[8].tex_path = "./textures/sprite_crosshair2.xpm";
	t->td[9].tex_path = "./textures/sprite_bat/bat1.2.1.xpm";
	t->td[10].tex_path = "./textures/sprite_bat/bat1.2.2.xpm";
	t->td[11].tex_path = "./textures/sprite_bat/bat1.2.3.xpm";
	t->td[12].tex_path = "./textures/sprite_bat/bat1.2.4.xpm";
	t->td[13].tex_path = "./textures/sprite_torch/sprite_torch1.xpm";
	t->td[14].tex_path = "./textures/sprite_torch/sprite_torch2.xpm";
	t->td[15].tex_path = "./textures/sprite_torch/sprite_torch3.xpm";
	t->td[16].tex_path = "./textures/sprite_torch/sprite_torch4.xpm";
	t->td[17].tex_path = "./textures/sprite_gun/sprite_gun1.xpm";
	t->td[18].tex_path = "./textures/sprite_gun/sprite_gun2.xpm";
	t->td[19].tex_path = "./textures/sprite_gun/sprite_gun3.xpm";
	t->td[20].tex_path = "./textures/sprite_gun/sprite_gun4.xpm";
	t->td[21].tex_path = "./textures/sprite_death/sprite_blood_splatter1.xpm";
	t->td[22].tex_path = "./textures/sprite_death/sprite_blood_splatter2.xpm";
	t->td[23].tex_path = "./textures/sprite_spider/sprite_spiderv3.1.xpm";
	t->td[24].tex_path = "./textures/sprite_spider/sprite_spiderv3.2.xpm";
	t->td[25].tex_path = "./textures/sprite_spider/sprite_spiderv3.3.xpm";
	t->td[26].tex_path = "./textures/sprite_spider/sprite_spiderv3.4.xpm";
	t->td[27].tex_path = "./textures/sprite_spider/sprite_spiderv3.5.xpm";
	t->td[28].tex_path = "./textures/sprite_spider/sprite_spiderv3.6.xpm";
}

static void		get_extra_texture_paths2(t_cub3d *t)
{
	t->td[29].tex_path = "./textures/sprite_spider/sprite_spider_attack1.xpm";
	t->td[30].tex_path = "./textures/sprite_spider/sprite_spider_attack2.xpm";
	t->td[31].tex_path = "./textures/sprite_spider/sprite_spider_attack3.xpm";
	t->td[32].tex_path = "./textures/sprite_spider/sprite_spider_attack4.xpm";
	t->td[33].tex_path = "./textures/sprite_spider/sprite_spider_attack5.xpm";
	t->td[34].tex_path = "./textures/heart/sprite_heart1.xpm";
	t->td[35].tex_path = "./textures/heart/sprite_heart2.xpm";
	t->td[36].tex_path = "./textures/heart/sprite_heart3.xpm";
	t->td[37].tex_path = "./textures/heart/sprite_heart4.xpm";
	t->td[38].tex_path = "./textures/sprite_bullet2.xpm";
	t->td[39].tex_path = "./textures/sprite_bullets/sprite_bullets1.xpm";
	t->td[40].tex_path = "./textures/sprite_bullets/sprite_bullets2.xpm";
	t->td[41].tex_path = "./textures/sprite_bullets/sprite_bullets3.xpm";
	t->td[42].tex_path = "./textures/sprite_bullets/sprite_bullets4.xpm";
	t->td[43].tex_path = "./textures/sprite_spider/sprite_spider_nest.xpm";
}

void			get_textures(t_cub3d *t)
{
	int				img_width[50];
	int				img_height[50];
	unsigned int	i;
	// unsigned int texel;

	get_extra_texture_paths1(t);
	get_extra_texture_paths2(t);
	i = 0;
	while (i < 44)
	{
		t->td[i].texture = mlx_xpm_file_to_image(t->mlx, t->td[i].tex_path,
		&img_width[i], &img_height[i]);
		t->td[i].addr = mlx_get_data_addr(t->td[i].texture, &t->td[i].bpp,
		&t->td[i].line_len, &t->td[i].endian);
		// texel = ft_getpxl(t, i, 2, 2);
		// printf("texture %d, %u\n", i, texel);
		i++;
	}
	printf("loading textures complete\n");
}

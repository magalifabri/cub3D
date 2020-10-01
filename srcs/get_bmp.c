/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 10:33:37 by Magali            #+#    #+#             */
/*   Updated: 2020/04/27 16:22:38 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	*create_bmp_file_h(t_cub3d *t, t_gen_bmp_data *b, int pad_size)
{
	int				i;
	int				file_size;
	unsigned char	*file_h;

	file_size = b->file_h_size + b->info_h_size
	+ (b->bpp * t->win_w + pad_size) * t->win_h;
	if (!(file_h = malloc(b->file_h_size)))
		exit_cub3d(t);
	i = 5;
	while (++i < b->file_h_size)
		file_h[i] = 0;
	file_h[0] = (unsigned char)('B');
	file_h[1] = (unsigned char)('M');
	file_h[2] = (unsigned char)(file_size);
	file_h[3] = (unsigned char)(file_size >> 8);
	file_h[4] = (unsigned char)(file_size >> 16);
	file_h[5] = (unsigned char)(file_size >> 24);
	file_h[10] = (unsigned char)(b->file_h_size + b->info_h_size);
	return (file_h);
}

unsigned char	*create_bmp_info_h(t_cub3d *t, t_gen_bmp_data *b)
{
	int				i;
	unsigned char	*info_h;

	if (!(info_h = malloc(b->info_h_size)))
		exit_cub3d(t);
	i = -1;
	while (++i < b->info_h_size)
		info_h[i] = 0;
	info_h[0] = (unsigned char)(b->info_h_size);
	info_h[4] = (unsigned char)(t->win_w);
	info_h[5] = (unsigned char)(t->win_w >> 8);
	info_h[6] = (unsigned char)(t->win_w >> 16);
	info_h[7] = (unsigned char)(t->win_w >> 24);
	info_h[8] = (unsigned char)(t->win_h);
	info_h[9] = (unsigned char)(t->win_h >> 8);
	info_h[10] = (unsigned char)(t->win_h >> 16);
	info_h[11] = (unsigned char)(t->win_h >> 24);
	info_h[12] = (unsigned char)(1);
	info_h[14] = (unsigned char)(b->bpp * 8);
	return (info_h);
}

void			create_bmp(t_cub3d *t, t_gen_bmp_data *b)
{
	unsigned char	padding[3];
	int				pad_size;
	int				fd;
	int				y;
	int				i;

	i = -1;
	while (++i < 3)
		padding[i] = 0;
	pad_size = (4 - (t->win_w * b->bpp) % 4) % 4;
	fd = open(b->file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (write(fd, create_bmp_file_h(t, b, pad_size), b->file_h_size) == -1)
		exit_cub3d(t);
	write(fd, create_bmp_info_h(t, b), b->info_h_size);
	y = -1;
	while (++y < t->win_h)
	{
		write(fd, b->image + (y * t->win_w * b->bpp), t->win_w * b->bpp);
		write(fd, padding, pad_size);
	}
	close(fd);
}

void			initialise(t_cub3d *t, t_gen_bmp_data *b)
{
	b->bpp = 3;
	b->file_h_size = 14;
	b->info_h_size = 40;
	b->file_name = "bitmapImage.bmp";
	b->image = malloc(t->win_h * t->win_w * b->bpp);
}

void			get_bmp(t_cub3d *t)
{
	t_gen_bmp_data	b;
	int				y;
	int				x;
	int				i;
	unsigned int	texel;

	initialise(t, &b);
	y = -1;
	while (++y < t->win_h)
	{
		x = -1;
		while (++x < t->win_w)
		{
			i = (y * t->win_w * 3) + (x * 3);
			texel = get_pxl_for_bmp(t, x, t->win_h - y);
			b.image[i + 2] = (texel & 0x00FF0000) >> 16;
			b.image[i + 1] = (texel & 0x0000FF00) >> 8;
			b.image[i] = texel & 0x000000FF;
		}
	}
	create_bmp(t, &b);
	printf("Image saved!\n");
	exit_cub3d(t);
}

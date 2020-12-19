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

static unsigned char	*create_bmp_file_h(t_cub3d *t, t_gen_bmp_data *b,
						int pad_size)
{
	int				i;
	int				file_size;

	file_size = b->file_h_size + b->info_h_size
	+ (b->bpp * t->win_w + pad_size) * t->win_h;
	if (!(b->file_h = malloc(b->file_h_size)))
		bmp_creation_error(t, b);
	b->malloc_file_h = 1;
	i = 5;
	while (++i < b->file_h_size)
		b->file_h[i] = 0;
	b->file_h[0] = (unsigned char)('B');
	b->file_h[1] = (unsigned char)('M');
	b->file_h[2] = (unsigned char)(file_size);
	b->file_h[3] = (unsigned char)(file_size >> 8);
	b->file_h[4] = (unsigned char)(file_size >> 16);
	b->file_h[5] = (unsigned char)(file_size >> 24);
	b->file_h[10] = (unsigned char)(b->file_h_size + b->info_h_size);
	return (b->file_h);
}

static unsigned char	*create_bmp_info_h(t_cub3d *t, t_gen_bmp_data *b)
{
	int				i;

	if (!(b->info_h = malloc(b->info_h_size)))
		bmp_creation_error(t, b);
	b->malloc_info_h = 1;
	i = -1;
	while (++i < b->info_h_size)
		b->info_h[i] = 0;
	b->info_h[0] = (unsigned char)(b->info_h_size);
	b->info_h[4] = (unsigned char)(t->win_w);
	b->info_h[5] = (unsigned char)(t->win_w >> 8);
	b->info_h[6] = (unsigned char)(t->win_w >> 16);
	b->info_h[7] = (unsigned char)(t->win_w >> 24);
	b->info_h[8] = (unsigned char)(t->win_h);
	b->info_h[9] = (unsigned char)(t->win_h >> 8);
	b->info_h[10] = (unsigned char)(t->win_h >> 16);
	b->info_h[11] = (unsigned char)(t->win_h >> 24);
	b->info_h[12] = (unsigned char)(1);
	b->info_h[14] = (unsigned char)(b->bpp * 8);
	return (b->info_h);
}

static void				create_bmp(t_cub3d *t, t_gen_bmp_data *b)
{
	unsigned char	padding[3];
	int				pad_size;
	int				y;
	int				i;

	i = -1;
	while (++i < 3)
		padding[i] = 0;
	pad_size = (4 - (t->win_w * b->bpp) % 4) % 4;
	if ((b->fd = open(b->filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1)
		bmp_creation_error(t, b);
	if (write(b->fd, create_bmp_file_h(t, b, pad_size), b->file_h_size) == -1)
		bmp_creation_error(t, b);
	if (write(b->fd, create_bmp_info_h(t, b), b->info_h_size) == -1)
		bmp_creation_error(t, b);
	y = -1;
	while (++y < t->win_h)
	{
		if (write(b->fd, b->image + (y * t->win_w * b->bpp), t->win_w * b->bpp)
			== -1)
			bmp_creation_error(t, b);
		if (write(b->fd, padding, pad_size) == -1)
			bmp_creation_error(t, b);
	}
	close(b->fd);
}

static void				initialise(t_cub3d *t, t_gen_bmp_data *b)
{
	b->fd = -1;
	b->malloc_image = 0;
	b->malloc_file_h = 0;
	b->malloc_info_h = 0;
	b->bpp = 3;
	b->file_h_size = 14;
	b->info_h_size = 40;
	b->filename = "bitmapImage.bmp";
	if (!(b->image = malloc(t->win_h * t->win_w * b->bpp)))
		bmp_creation_error(t, b);
	b->malloc_image = 1;
}

void					get_bmp(t_cub3d *t)
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
	ft_printf("Image saved!\n");
	free_stuff(&b);
	exit_cub3d(t);
}

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

void	free_stuff(t_gen_bmp_data *b)
{
	free(b->image);
	free(b->file_h);
	free(b->info_h);
}

void	bmp_creation_error(t_cub3d *t, t_gen_bmp_data *b)
{
	if (b->fd != -1)
		close(b->fd);
	if (b->malloc_image)
		free(b->image);
	if (b->malloc_file_h)
		free(b->file_h);
	if (b->malloc_info_h)
		free(b->info_h);
	error_and_exit(t, "get_bmp.c: bmp creation error");
}

unsigned int	get_pxl_for_bmp(t_cub3d *t, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = t->addr + (y * t->line_len + x * (t->bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

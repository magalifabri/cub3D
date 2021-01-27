/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_resolution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 19:51:18 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/27 15:48:07 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_dimensions(t_cub3d *t)
{
	if (t->win_w < MIN_WINDOW_WIDTH)
	{
		ft_printf("Given width resolution too low. Set to minimum\n");
		t->win_w = MIN_WINDOW_WIDTH;
	}
	else if (t->win_w > MAX_WINDOW_WIDTH)
	{
		ft_printf("Given width resolution too high. Set to max\n");
		t->win_w = MAX_WINDOW_WIDTH;
	}
	if (t->win_h < MIN_WINDOW_HEIGHT)
	{
		ft_printf("Given height resolution too low. Set to minimum\n");
		t->win_h = MIN_WINDOW_HEIGHT;
	}
	else if (t->win_h > MAX_WINDOW_HEIGHT)
	{
		ft_printf("Given height resolution too high. Set to max.\n");
		t->win_h = MAX_WINDOW_HEIGHT;
	}
}

void		get_window_resolution(t_cub3d *t, char *file, int *index)
{
	int i;

	if (t->win_w != 0 || t->win_h != 0)
		error_and_exit(t, "duplicate resolution assigment in .cub");
	i = 0;
	while (file[i] == ' ')
		i++;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_w = t->win_w * 10 + (file[i++] - '0');
	while (file[i] == ' ')
		i++;
	while (file[i] >= '0' && file[i] <= '9')
		t->win_h = t->win_h * 10 + (file[i++] - '0');
	if (t->win_w <= 0 || t->win_h <= 0)
		error_and_exit(t, "problem with resolution in .cub");
	check_dimensions(t);
	while (file[i] == ' ')
		i++;
	*index += i;
}

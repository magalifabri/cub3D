/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:40:02 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_1(t_tab *tab)
{
	int widening;

	widening = tab->mfw - tab->len;
	while (widening-- > 0)
		ft_putchar(tab, tab->pad);
	if (tab->pre != 0)
		while (widening-- > 0)
			ft_putchar(tab, ' ');
}

void	ft_postpad_1(t_tab *tab)
{
	int widening;

	widening = tab->mfw - tab->len;
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

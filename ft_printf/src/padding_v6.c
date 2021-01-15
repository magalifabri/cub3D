/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:42:37 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_6(t_tab *tab)
{
	int widening;

	widening = tab->mfw - tab->len;
	if (tab->pad != '-')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
}

void	ft_prepad_6_neg(t_tab *tab)
{
	int widening;

	widening = tab->mfw - tab->len;
	if (tab->pad == ' ')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	ft_putchar(tab, tab->sign);
	if (tab->pad == '0')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	tab->s++;
}

void	ft_postpad_6(t_tab *tab)
{
	int widening;

	widening = tab->mfw - tab->len;
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

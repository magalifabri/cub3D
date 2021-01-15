/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:40:36 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_7(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	tab->sharp = (tab->sharp == '#' && tab->pre <= tab->len
		&& (tab->s[0] != '0' || (tab->s[0] == '0' && tab->pre != -1))
		&& (tab->pad != '0' || (tab->pad == '0' && (tab->mfw <= tab->len
			|| (tab->mfw > tab->len && tab->pre != -1))))) ? ('#') : (' ');
	(tab->sharp == '#') && (widening -= 1);
	if (tab->pad != '-')
	{
		if (tab->pre == -1)
			while (widening-- > 0)
				ft_putchar(tab, tab->pad);
		if (tab->pre != -1)
			while (widening-- > 0)
				ft_putchar(tab, ' ');
	}
	while (precising-- > 0)
		ft_putchar(tab, '0');
}

void	ft_postpad_7(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	(tab->sharp == '#') && (widening -= 1);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

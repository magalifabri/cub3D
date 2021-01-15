/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:42:17 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_5(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, tab->pad);
}

void	ft_prepad_5_neg(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 1 > tab->pre) ? (0) : (tab->pre - (tab->len - 1));
	widening = tab->mfw - (tab->len + precising);
	if (tab->pad == ' ')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	ft_putchar(tab, tab->sign);
	if (tab->pad == '0')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	tab->s++;
}

void	ft_postpad_5(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	if (tab->sharp == '#' && tab->pre == 0)
	{
		ft_putchar(tab, '.');
		widening--;
	}
	while (widening-- > 0 && (tab->pad == '-' && tab->mfw != 0))
		ft_putchar(tab, ' ');
}

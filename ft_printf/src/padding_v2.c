/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:40:22 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_2a(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 2 > tab->pre) ? (0) : (tab->pre - (tab->len - 2));
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

void	ft_prepad_2b(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 2 > tab->pre) ? (0) : (tab->pre - (tab->len - 2));
	widening = tab->mfw - (tab->len + precising);
	if (tab->pad == '0' && tab->pre == -1)
		while (widening-- > 0)
			ft_putchar(tab, '0');
	while (precising-- > 0)
		ft_putchar(tab, '0');
}

void	ft_postpad_2(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 2 > tab->pre) ? (0) : (tab->pre - (tab->len - 2));
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

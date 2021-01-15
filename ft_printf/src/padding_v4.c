/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:41:51 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_4(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - (tab->len));
	widening = tab->mfw - (tab->len + precising);
	if (tab->mfw != 0 && tab->pad == '0' && tab->pre == -1)
		while (widening-- > 0)
			ft_putchar(tab, '0');
	if (tab->mfw != 0 && tab->pad != '-')
		while (widening-- > 0)
			ft_putchar(tab, ' ');
	while (precising-- > 0)
		ft_putchar(tab, '0');
}

void	ft_postpad_4(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - (tab->len));
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

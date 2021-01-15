/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:40:36 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_3(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
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

void	ft_prepad_3_neg(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 1 > tab->pre) ? (0) : (tab->pre - (tab->len - 1));
	widening = tab->mfw - (tab->len + precising);
	if (tab->pre == -1 && tab->pad != '-')
	{
		if (tab->pad == ' ')
			while (widening-- > 0)
				ft_putchar(tab, tab->pad);
		ft_putchar(tab, tab->sign);
		if (tab->pad == '0')
			while (widening-- > 0)
				ft_putchar(tab, tab->pad);
	}
	if (tab->pre != -1 || tab->pad == '-')
	{
		if (tab->pre != -1 && tab->pad != '-')
			while (widening-- > 0)
				ft_putchar(tab, ' ');
		ft_putchar(tab, tab->sign);
		if (tab->pre != -1)
			while (precising-- > 0)
				ft_putchar(tab, '0');
	}
}

void	ft_postpad_3(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

void	ft_postpad_3_neg(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 1 > tab->pre) ? (0) : (tab->pre - (tab->len - 1));
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

void	ft_pad_3(t_tab *tab, int n)
{
	if (n == 1)
	{
		(tab->sign == '0' && (tab->pad != '-' || tab->pre != -1))
			? (ft_prepad_3(tab)) : (NULL);
		(tab->sign != '0' && (tab->pad != '-' || tab->pre != -1))
			? (ft_prepad_3_neg(tab)) : (NULL);
	}
	else
	{
		(tab->sign == '0' && tab->pad == '-' && tab->mfw != 0)
			? (ft_postpad_3(tab)) : (NULL);
		(tab->sign != '0' && tab->pad == '-' && tab->mfw != 0)
			? (ft_postpad_3_neg(tab)) : (NULL);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 09:29:36 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/05 09:48:36 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_flags(t_tab *tab)
{
	if (tab->format[tab->pos] == '*')
	{
		tab->mfw = (int)va_arg(tab->ap, int);
		(tab->mfw < 0) && (tab->pad = '-');
		(tab->mfw < 0) && (tab->mfw = -tab->mfw);
		tab->pos++;
	}
	while (tab->format[tab->pos] == '-'
			|| tab->format[tab->pos] == '0' || tab->format[tab->pos] == '+'
			|| tab->format[tab->pos] == '#' || tab->format[tab->pos] == ' ')
	{
		(tab->format[tab->pos] == '0' && tab->pad == ' ') && (tab->pad = '0');
		(tab->format[tab->pos] == '-') && (tab->pad = '-');
		(tab->format[tab->pos] == ' ' && tab->sign == '0') && (tab->sign = ' ');
		(tab->format[tab->pos] == '+') && (tab->sign = '+');
		(tab->format[tab->pos] == '#') && (tab->sharp = '#');
		tab->pos++;
	}
	if (tab->format[tab->pos] == '*')
	{
		tab->mfw = (int)va_arg(tab->ap, int);
		(tab->mfw < 0) && (tab->pad = '-');
		(tab->mfw < 0) && (tab->mfw = -tab->mfw);
		tab->pos++;
	}
}

void	ft_width(t_tab *tab)
{
	while (tab->format[tab->pos] >= '0' && tab->format[tab->pos] <= '9')
		tab->mfw = tab->mfw * 10 + tab->format[tab->pos++] - 48;
}

void	ft_precision(t_tab *tab)
{
	tab->pos++;
	tab->pre = 0;
	if (tab->format[tab->pos] == '*')
	{
		tab->pre = (int)va_arg(tab->ap, int);
		(tab->pre < 0) && (tab->pre = -1);
		tab->pos++;
	}
	while (tab->format[tab->pos] >= '0' && tab->format[tab->pos] <= '9')
		tab->pre = tab->pre * 10 + tab->format[tab->pos++] - 48;
}

void	ft_length_mod(t_tab *tab)
{
	while (tab->format[tab->pos] == 'l' || tab->format[tab->pos] == 'h'
		|| tab->format[tab->pos] == 'L')
	{
		tab->lm = tab->format[tab->pos] == 'l' && tab->lm == ' '
			? 'l' : tab->lm;
		tab->lm = tab->format[tab->pos] == 'h' && tab->lm == ' '
			? 'h' : tab->lm;
		tab->lm = tab->format[tab->pos] == 'L' && tab->lm == ' '
			? 'L' : tab->lm;
		tab->pos++;
		tab->lm = tab->format[tab->pos] == 'l' && tab->lm == 'l'
			? 'L' : tab->lm;
		tab->lm = tab->format[tab->pos] == 'h' && tab->lm == 'h'
			? 'H' : tab->lm;
	}
}

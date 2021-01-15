/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_g.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:10:09 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/10 16:26:37 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_precision_check(long double g, int pre)
{
	int i;

	i = 0;
	if (pre == -2)
	{
		while (((int)g % 10 != 0))
		{
			i++;
			g *= 10;
		}
		return (i - 1);
	}
	while (i++ < pre)
		g *= 10;
	while (pre)
	{
		if ((int)(g + 1e-9) % 10 != 0)
			return (pre);
		g /= 10;
		pre--;
	}
	return (pre);
}

static int	ft_f_or_e(long double g, int pre, t_tab *tab)
{
	int		len;
	char	e_or_f;

	pre = (pre == -1) ? (6) : (pre);
	g = (g < 0) ? (-g) : (g);
	len = 0;
	while (g >= 1)
	{
		g /= 10;
		len++;
	}
	e_or_f = (len > 1 && len > pre && pre != -1) ? ('e') : ('f');
	pre = (len > pre) ? (pre - 1) : (pre - len);
	while (len--)
		g *= 10;
	if ((pre > 0 || pre == -2) && e_or_f == 'f')
		pre = ft_precision_check(g, pre);
	pre = (pre < 0) ? (0) : (pre);
	if (!(tab->s = (e_or_f == 'e')
		? (ft_etoa(g, pre, tab->sign)) : (ft_ftoa(g, pre, tab->sign))))
		return (0);
	tab->p = tab->s;
	return (1);
}

int			ft_g(t_tab *tab)
{
	long double g;

	(tab->lm == ' ') && (g = (double)va_arg(tab->ap, double));
	(tab->lm == 'L') && (g = (long double)va_arg(tab->ap, long double));
	tab->sign = (signbit(g)) ? ('-') : (tab->sign);
	if (!(ft_f_or_e(g, tab->pre, tab)))
		return (0);
	tab->len = ft_strlen(tab->s);
	(tab->sign == '0' && tab->pad != '-') ? (ft_prepad_6(tab)) : (NULL);
	(tab->sign != '0' && tab->pad != '-') ? (ft_prepad_6_neg(tab)) : (NULL);
	while (*tab->s)
		ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_6(tab)) : (NULL);
	return (1);
}

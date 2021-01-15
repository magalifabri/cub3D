/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_cs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:49:16 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/07 10:16:45 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void		ft_c(t_tab *tab)
{
	wint_t c;

	if (tab->lm != 'l')
		c = va_arg(tab->ap, int);
	else
		c = va_arg(tab->ap, wchar_t);
	tab->len = 1;
	(tab->pad != '-' && tab->mfw != 0) ? (ft_prepad_1(tab)) : (NULL);
	ft_putchar(tab, c);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_1(tab)) : (NULL);
}

static int	ft_ls(t_tab *tab)
{
	if (!(tab->ws = va_arg(tab->ap, wchar_t *)))
		if (!(tab->ws = (wchar_t *)ft_strdup("(null)")))
			return (0);
	tab->len = ft_wstrlen(tab->ws);
	tab->len = tab->pre != -1 && tab->len > tab->pre ? tab->pre : tab->len;
	(tab->pad != '-' && tab->mfw != 0) ? (ft_prepad_1(tab)) : (NULL);
	ft_putwchar(tab, tab->ws);
	return (1);
}

int			ft_s(t_tab *tab)
{
	int i;

	i = 0;
	if (tab->lm != 'l')
	{
		if (!(tab->s = va_arg(tab->ap, char *)))
			if (!(tab->s = ft_strdup("(null)")))
				return (0);
		tab->len = ft_strlen(tab->s);
		tab->len = tab->pre != -1 && tab->len > tab->pre ? tab->pre : tab->len;
		(tab->pad != '-' && tab->mfw != 0) ? (ft_prepad_1(tab)) : (NULL);
		while (tab->s[i] && i < tab->len)
			ft_putchar(tab, tab->s[i++]);
	}
	else if (!(ft_ls(tab)))
		return (0);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_1(tab)) : (NULL);
	return (1);
}

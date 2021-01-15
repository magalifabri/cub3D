/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_pxpercent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:54:51 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/07 18:20:56 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_p(t_tab *tab, uintmax_t n)
{
	char *l_or_u;

	l_or_u = (tab->c == 8) ? ("0123456789ABCDEF") : ("0123456789abcdef");
	if (!(tab->s = ft_uitoabase(n, l_or_u, 16)))
		return (0);
	tab->p = tab->s;
	tab->len = 2 + ft_strlen(tab->s);
	(tab->mfw != 0 && (tab->pad == ' ' || (tab->pad == '0' && tab->pre != -1)))
		? (ft_prepad_2a(tab)) : (NULL);
	(tab->c == 8) ? (write(1, "0X", 2)) : (write(1, "0x", 2));
	tab->printed += 2;
	(tab->pre > 0 || (tab->pad == '0' && tab->pre == -1))
		? (ft_prepad_2b(tab)) : (NULL);
	if (!(n == 0 && tab->pre == 0))
		while (*tab->s)
			ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_2(tab)) : (NULL);
	return (1);
}

static int	ft_x(t_tab *tab, uintmax_t n)
{
	char *l_or_u;

	l_or_u = (tab->c == 7) ? ("0123456789abcdef") : ("0123456789ABCDEF");
	if (!(tab->s = ft_uitoabase(n, l_or_u, 16)))
		return (0);
	tab->p = tab->s;
	tab->len = ft_strlen(tab->s);
	tab->len = (tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0)
		? (tab->len - 1) : (tab->len);
	((tab->pad != '-' && tab->mfw != 0) || tab->pre > 0)
		? (ft_prepad_4(tab)) : (NULL);
	if (!(tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0))
		while (*tab->s)
			ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_4(tab)) : (NULL);
	return (1);
}

int			ft_p_or_x(t_tab *tab)
{
	uintmax_t	n;

	(tab->lm == ' ' && tab->c == 3)
		&& (n = (unsigned long)va_arg(tab->ap, long));
	(tab->lm == ' ' && tab->c != 3)
		&& (n = (unsigned int)va_arg(tab->ap, int));
	(tab->lm == 'H') && (n = (unsigned char)va_arg(tab->ap, int));
	(tab->lm == 'h') && (n = (unsigned short)va_arg(tab->ap, int));
	(tab->lm == 'L') && (n = (unsigned long long)va_arg(tab->ap, long long));
	(tab->lm == 'l') && (n = (unsigned long)va_arg(tab->ap, long));
	if (!((tab->c == 3 || (tab->c != 3 && tab->sharp == '#' && n > 0))
		? (ft_p(tab, n)) : (ft_x(tab, n))))
		return (0);
	return (1);
}

void		ft_percent(t_tab *tab)
{
	tab->len = 1;
	(tab->pad != '-' && tab->mfw != 0) ? (ft_prepad_1(tab)) : (NULL);
	ft_putchar(tab, '%');
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_1(tab)) : (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_diuo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:49:16 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 18:58:43 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int			ft_di(t_tab *tab)
{
	intmax_t	n;

	(tab->lm == ' ') && (n = (int)va_arg(tab->ap, int));
	(tab->lm == 'H') && (n = (signed char)va_arg(tab->ap, int));
	(tab->lm == 'h') && (n = (short)va_arg(tab->ap, int));
	(tab->lm == 'L') && (n = (long long)va_arg(tab->ap, long long));
	(tab->lm == 'l') && (n = (long)va_arg(tab->ap, long));
	tab->sign = (n < 0) ? ('-') : (tab->sign);
	if (!(tab->s = ft_itoa(tab->sign, n)))
		return (0);
	tab->p = tab->s;
	tab->len = ft_strlen(tab->s);
	tab->len = (n == 0 && tab->pre == 0) ? (tab->len - 1) : (tab->len);
	ft_pad_3(tab, 1);
	tab->sign != '0' && (tab->pad != '-' || tab->pre != -1) ? tab->s++ : NULL;
	if (!(n == 0 && tab->pre == 0))
		while (*tab->s)
			ft_putchar(tab, *tab->s++);
	ft_pad_3(tab, 2);
	return (1);
}

int			ft_u(t_tab *tab)
{
	uintmax_t	n;

	(tab->lm == ' ') && (n = (unsigned int)va_arg(tab->ap, int));
	(tab->lm == 'H') && (n = (unsigned char)va_arg(tab->ap, int));
	(tab->lm == 'h') && (n = (unsigned short)va_arg(tab->ap, int));
	(tab->lm == 'L') && (n = (uintmax_t)va_arg(tab->ap, uintmax_t));
	(tab->lm == 'l') && (n = (unsigned long)va_arg(tab->ap, unsigned long));
	if (!(tab->s = ft_uitoabase(n, "0123456789", 10)))
		return (0);
	tab->p = tab->s;
	tab->len = ft_strlen(tab->s);
	tab->len = (tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0)
		? (tab->len - 1) : (tab->len);
	(tab->s[0] != '-') ? (ft_prepad_3(tab)) : (NULL);
	if (!(tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0))
		while (*tab->s)
			ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_3(tab)) : (NULL);
	return (1);
}

int			ft_o(t_tab *tab)
{
	uintmax_t	n;

	(tab->lm == ' ') && (n = (unsigned int)va_arg(tab->ap, int));
	(tab->lm == 'H') && (n = (unsigned char)va_arg(tab->ap, int));
	(tab->lm == 'h') && (n = (unsigned short)va_arg(tab->ap, int));
	(tab->lm == 'L') && (n = (uintmax_t)va_arg(tab->ap, uintmax_t));
	(tab->lm == 'l') && (n = (unsigned long)va_arg(tab->ap, unsigned long));
	if (!(tab->s = ft_uitoabase(n, "01234567", 8)))
		return (0);
	tab->p = tab->s;
	tab->len = ft_strlen(tab->s);
	tab->len = (tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0)
		? (tab->len - 1) : (tab->len);
	(tab->s[0] != '-') ? (ft_prepad_7(tab)) : (NULL);
	(tab->sharp == '#') ? (ft_putchar(tab, '0')) : (NULL);
	if (!(tab->s[0] == '0' && tab->s[1] == '\0' && tab->pre == 0))
		while (*tab->s)
			ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_7(tab)) : (NULL);
	return (1);
}

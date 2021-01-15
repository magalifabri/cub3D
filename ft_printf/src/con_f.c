/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:02:10 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/08 11:51:34 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static double	ft_get_rnd(int pre)
{
	double rnd;

	rnd = 0.5;
	while (pre--)
		rnd /= 10;
	return (rnd);
}

static void		ft_get_int(intmax_t n_int, char *s, int len)
{
	while (n_int)
	{
		s[len--] = (n_int % 10) + '0';
		n_int /= 10;
	}
}

static void		ft_convert(char *s, long double n, int pre, int len)
{
	intmax_t	n_int;
	double		rnd;
	int			zero;
	int			dot;

	zero = (intmax_t)n == 0 ? (1) : (0);
	dot = pre > 0 ? (1) : (0);
	rnd = ft_get_rnd(pre);
	n_int = (pre == 0) ? (intmax_t)(n + 0.5) : (intmax_t)(n + rnd);
	(n_int == 0) && (s[len++] = '0');
	pre += len + dot;
	ft_get_int(n_int, s, len - 1);
	n = (n - (intmax_t)(n + rnd)) + rnd;
	(dot) && (s[len++] = '.');
	while (len < pre)
	{
		n *= 10;
		s[len++] = (int)n + '0';
		n -= (int)n;
	}
}

char			*ft_ftoa(long double n, int pre, char sign)
{
	char		*s;
	int			len;
	int			dot;
	int			zero;
	long double	n_cpy;

	zero = (intmax_t)n == 0 ? (1) : (0);
	pre = (pre == -1) ? (6) : (pre);
	dot = (pre > 0) ? (1) : (0);
	len = (sign != '0') ? (1) : (0);
	n_cpy = (n < 0) ? (-n) : (n);
	n_cpy += ft_get_rnd(pre);
	while (n_cpy >= 1)
		n_cpy = (len++) ? (n_cpy / 10) : (n_cpy / 10);
	if (!(s = malloc(sizeof(char) * len + pre + dot + zero + 1)))
		return (NULL);
	(sign != '0') ? (s[0] = sign) : (0);
	ft_convert(s, (n < 0) ? (-n) : (n), pre, len);
	s[len + pre + dot + zero] = '\0';
	return (s);
}

int				ft_f(t_tab *tab)
{
	long double f;

	(tab->lm == ' ') && (f = (double)va_arg(tab->ap, double));
	(tab->lm == 'L') && (f = (long double)va_arg(tab->ap, long double));
	tab->sign = (signbit(f)) ? ('-') : (tab->sign);
	if (!(tab->s = ft_ftoa(f, tab->pre, tab->sign)))
		return (0);
	tab->p = tab->s;
	tab->len = ft_strlen(tab->s);
	(tab->sign == '0' && tab->pad != '-') ? (ft_prepad_5(tab)) : (NULL);
	(tab->sign != '0' && tab->pad != '-') ? (ft_prepad_5_neg(tab)) : (NULL);
	while (*tab->s)
		ft_putchar(tab, *tab->s++);
	((tab->pad == '-' && tab->mfw != 0) || tab->sharp == '#')
		? (ft_postpad_5(tab)) : (NULL);
	return (1);
}

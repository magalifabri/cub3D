/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_e.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 09:17:22 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/10 16:33:07 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static long double	ft_get_rnd(int len, int pre)
{
	long double rnd;

	rnd = 0.5;
	if (len > pre)
		while (len-- > pre)
			rnd *= 10;
	else if (pre > len)
		while (pre-- > len)
			rnd /= 10;
	return (rnd);
}

static int			ft_get_len(long double n)
{
	int len;

	len = 0;
	if (n > 10)
		while (n >= 10)
			n = (len++) ? (n / 10) : (n / 10);
	if (n < 1)
		while (n < 1 && n != 0.0)
			n = (len--) ? (n * 10) : (n * 10);
	return (len);
}

static void			ft_copy(char *s, char *s2, int len, int pre)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((s[j] == '0' && (pre > 0 || len < 0)) || s[j] == '.')
		j++;
	(j == pre + 2 && len == 0) && (j = 0);
	s2[i++] = s[j++];
	(pre > 0) && (s2[i++] = '.');
	while (s[j] && pre > 0)
	{
		if (s[j] != '.')
			s2[i++] = (pre--) ? s[j++] : s[j++];
		else
			j++;
	}
	s2[i++] = 'e';
	s2[i++] = (len >= 0) ? ('+') : ('-');
	len = (len < 0) ? (-len) : (len);
	s2[i++] = ((len / 10) % 10) + '0';
	s2[i++] = (len % 10) + '0';
	s2[i] = '\0';
}

char				*ft_etoa(long double n, int pre, char sign)
{
	char	*s;
	int		len;
	int		i;
	char	*s2;
	char	*p;

	n = (n < 0) ? (-n) : (n);
	pre = (pre == -1) ? (6) : (pre);
	len = ft_get_len(n);
	if (len != 0 || (n < 10 && n + ft_get_rnd(len, pre) >= 10))
		len = ft_get_len(n + ft_get_rnd(len, pre));
	i = (pre >= 0 && (pre - len) < 1) ? (0) : (pre - len);
	if (!(s = ft_ftoa_e(n + ft_get_rnd(len, pre), i, sign)))
		return (NULL);
	p = s;
	if (!(s2 = malloc(sizeof(char) * (pre + ((pre > 0) ? (1) : (0)) +
	((sign != '0') ? (1) : (0)) + 6))))
		return (NULL);
	(sign != '0') && (*s2++ = *s++);
	ft_copy(s, s2, len, pre);
	free(p);
	return (sign != '0' ? s2 - 1 : s2);
}

int					ft_e(t_tab *tab)
{
	long double e;

	(tab->lm == ' ') && (e = (double)va_arg(tab->ap, double));
	(tab->lm == 'L') && (e = (long double)va_arg(tab->ap, long double));
	tab->sign = (signbit(e)) ? ('-') : (tab->sign);
	if (!(tab->s = ft_etoa(e, tab->pre, tab->sign)))
		return (0);
	tab->len = ft_strlen(tab->s);
	(tab->sharp == '#') ? (ft_e_sharp(tab)) : (NULL);
	if (!tab->s)
		return (0);
	tab->p = tab->s;
	(tab->sign == '0' && tab->pad != '-') ? (ft_prepad_8(tab)) : (NULL);
	(tab->sign != '0' && tab->pad != '-') ? (ft_prepad_8_neg(tab)) : (NULL);
	while (*tab->s)
		ft_putchar(tab, *tab->s++);
	(tab->pad == '-' && tab->mfw != 0) ? (ft_postpad_8(tab)) : (NULL);
	return (1);
}

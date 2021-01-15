/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:02:10 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:08 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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
	int			zero;
	int			dot;

	zero = (intmax_t)n == 0 ? (1) : (0);
	dot = pre > 0 ? (1) : (0);
	n_int = (intmax_t)n;
	(n_int == 0) && (s[len++] = '0');
	pre += len + dot;
	ft_get_int(n_int, s, len - 1);
	n = n - (intmax_t)n;
	s[len++] = '.';
	while (len < pre)
	{
		n *= 10;
		s[len++] = (int)n + '0';
		n -= (int)n;
	}
}

char			*ft_ftoa_e(long double n, int pre, char sign)
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
	while (n_cpy >= 1)
		n_cpy = (len++) ? (n_cpy / 10) : (n_cpy / 10);
	if (!(s = malloc(sizeof(char) * len + pre + dot + zero + 1)))
		return (NULL);
	(sign != '0') ? (s[0] = sign) : (0);
	ft_convert(s, (n < 0) ? (-n) : (n), pre, len);
	s[len + pre + dot + zero] = '\0';
	return (s);
}

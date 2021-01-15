/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:25:00 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:08 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_itoa(char sign, intmax_t n)
{
	char		*str;
	int			len;
	intmax_t	n_cpy;

	n = (n < 0) ? (-n) : (n);
	n_cpy = n;
	len = 0;
	(n == 0) && (len++);
	(sign != '0') && (len++);
	while (n)
	{
		len++;
		n /= 10;
	}
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	(!n_cpy) && (str[len--] = '0');
	while (n_cpy)
	{
		str[len--] = (n_cpy % 10) + '0';
		n_cpy /= 10;
	}
	(sign != '0') && (str[len--] = sign);
	return (str);
}

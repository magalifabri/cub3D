/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:28:26 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_uitoa(uintmax_t n)
{
	char		*str;
	int			len;
	uintmax_t	n_cpy;

	n_cpy = n;
	len = 0;
	(n == 0) && (len++);
	while (n)
		n = (len++) ? (n / 10) : (n / 10);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	(!n_cpy) && (str[len--] = '0');
	while (n_cpy)
	{
		str[len--] = (n_cpy % 10) + '0';
		n_cpy /= 10;
	}
	return (str);
}

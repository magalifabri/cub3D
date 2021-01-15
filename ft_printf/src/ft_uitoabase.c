/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoabase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:15:48 by mfabri            #+#    #+#             */
/*   Updated: 2020/11/25 08:39:41 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_uitoabase(uintmax_t n, char *base, int base_size)
{
	int			len;
	char		*s;
	uintmax_t	n_cpy;

	n_cpy = n;
	len = (n == 0) ? (1) : (0);
	while (n > 0)
		n = (len++) ? (n / base_size) : (n / base_size);
	if (!(s = malloc(sizeof(char) * len + 1)))
		return (NULL);
	s[len--] = '\0';
	(!n_cpy) && (s[len--] = '0');
	while (n_cpy > 0)
	{
		s[len--] = base[n_cpy % base_size];
		n_cpy /= base_size;
	}
	return (s);
}

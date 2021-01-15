/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:29:51 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:08 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	if (!(str = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	str[i] = '\0';
	return (str);
}

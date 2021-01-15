/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:26:59 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/07 12:06:37 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putwchar(t_tab *tab, wchar_t *c)
{
	int		s_len;
	int		len;
	char	con[4];

	s_len = ft_wstrlen(c);
	while (*c && s_len >= 0)
	{
		if (s_len > 1 && *c >= 194 && *c <= 244)
		{
			len = 0;
			con[len++] = *c++;
			while ((*c >= 128 && *c <= 191) && s_len--)
				con[len++] = *c++;
			write(1, con, len);
			s_len++;
			tab->printed += len;
		}
		else
			ft_putchar(tab, *c++);
		s_len--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_v8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:42:17 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 19:03:32 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_prepad_8(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, tab->pad);
}

void	ft_prepad_8_neg(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len - 1 > tab->pre) ? (0) : (tab->pre - (tab->len - 1));
	widening = tab->mfw - (tab->len + precising);
	if (tab->pad == ' ')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	ft_putchar(tab, tab->sign);
	if (tab->pad == '0')
		while (widening-- > 0)
			ft_putchar(tab, tab->pad);
	tab->s++;
}

void	ft_postpad_8(t_tab *tab)
{
	int widening;
	int precising;

	precising = (tab->len > tab->pre) ? (0) : (tab->pre - tab->len);
	widening = tab->mfw - (tab->len + precising);
	while (widening-- > 0)
		ft_putchar(tab, ' ');
}

void	ft_e_sharp(t_tab *tab)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	while (tab->s[i] && tab->s[i] != '.')
		i++;
	if (i < tab->len)
		return ;
	if (!(s = malloc(sizeof(char) * (tab->len + 2))))
	{
		tab->s = NULL;
		return ;
	}
	tmp = tab->s;
	i = 0;
	while (*tab->s)
	{
		(*tab->s == 'e') && (s[i++] = '.');
		s[i++] = *tab->s++;
	}
	s[i] = '\0';
	free(tmp);
	tab->s = s;
}

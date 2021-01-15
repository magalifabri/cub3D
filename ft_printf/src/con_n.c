/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 10:16:54 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/04 18:58:58 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_n(t_tab *tab)
{
	(tab->lm == ' ') && (*va_arg(tab->ap, int *) = tab->printed);
	(tab->lm == 'H') && (*va_arg(tab->ap, int *) = (signed char)tab->printed);
	(tab->lm == 'h') && (*va_arg(tab->ap, int *) = (short)tab->printed);
	(tab->lm == 'L') && (*va_arg(tab->ap, int *) = (long long)tab->printed);
	(tab->lm == 'l') && (*va_arg(tab->ap, int *) = (long)tab->printed);
}

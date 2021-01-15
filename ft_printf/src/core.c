/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 09:31:30 by mfabri            #+#    #+#             */
/*   Updated: 2020/12/07 19:03:30 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_check_conv(t_tab *tab)
{
	int ret;

	ret = 1;
	(tab->c == 1) ? ft_c(tab) : NULL;
	(tab->c == 2) && (ret = ft_s(tab));
	(tab->c == 3 || tab->c == 7 || tab->c == 8) && (ret = ft_p_or_x(tab));
	(tab->c >= 4 && tab->c <= 5) && (ret = ft_di(tab));
	(tab->c == 6) && (ret = ft_u(tab));
	(tab->c == 9) ? ft_percent(tab) : NULL;
	(tab->c == 10) ? ft_n(tab) : NULL;
	(tab->c == 11) && (ret = ft_f(tab));
	(tab->c == 12) && (ret = ft_e(tab));
	(tab->c == 13) && (ret = ft_g(tab));
	tab->pos++;
	return (ret);
}

static void	ft_reinit(t_tab *tab)
{
	tab->c = 0;
	tab->len = 0;
	tab->mfw = 0;
	tab->pad = ' ';
	tab->sign = '0';
	tab->sharp = ' ';
	tab->pre = -1;
	tab->lm = ' ';
	tab->s = NULL;
	tab->p = NULL;
}

static int	ft_check_specifier(t_tab *tab)
{
	ft_reinit(tab);
	tab->pos++;
	if (tab->format[tab->pos] == '-' || tab->format[tab->pos] == '*'
		|| tab->format[tab->pos] == '0' || tab->format[tab->pos] == '+'
		|| tab->format[tab->pos] == '#' || tab->format[tab->pos] == ' ')
		ft_flags(tab);
	if (tab->format[tab->pos] >= '0' && tab->format[tab->pos] <= '9')
		ft_width(tab);
	(tab->format[tab->pos] == '.') ? (ft_precision(tab)) : (NULL);
	if (tab->format[tab->pos] == 'l' || tab->format[tab->pos] == 'h'
		|| tab->format[tab->pos] == 'L')
		ft_length_mod(tab);
	while (tab->convs[tab->c])
		if (tab->convs[tab->c++] == tab->format[tab->pos])
		{
			tab->pre = (tab->pre == -1 && (tab->c == 1 || tab->c == 9
			|| tab->c == 10)) ? (0) : (tab->pre);
			return (ft_check_conv(tab));
		}
	return (1);
}

static void	ft_init(t_tab *tab, char *format)
{
	tab->pos = 0;
	tab->convs = "cspdiuxX%nfeg";
	tab->format = format;
	tab->printed = 0;
}

int			ft_printf(char *format, ...)
{
	t_tab	*tab;
	int		printed;

	if (!(tab = malloc(sizeof(t_tab))))
		return (-1);
	ft_init(tab, format);
	va_start(tab->ap, format);
	while (tab->format[tab->pos])
	{
		if (tab->format[tab->pos] == '%')
		{
			if (!(ft_check_specifier(tab)))
			{
				free(tab);
				return (-1);
			}
			(tab->p && tab->c != 2) ? (safefree((void **)&tab->p)) : (NULL);
		}
		else
			ft_putchar(tab, tab->format[tab->pos++]);
	}
	va_end(tab->ap);
	printed = tab->printed;
	free(tab);
	return (printed);
}

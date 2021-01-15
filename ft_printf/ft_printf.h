/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 09:32:47 by mfabri            #+#    #+#             */
/*   Updated: 2020/10/05 16:25:46 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdio.h>
# include <wchar.h>
# include <math.h>

typedef struct	s_tab
{
	va_list		ap;
	char		*format;
	int			pos;
	char		sharp;
	char		sign;
	char		pad;
	int			mfw;
	int			pre;
	char		*convs;
	int			c;
	char		*s;
	char		*p;
	wchar_t		*ws;
	int			len;
	int			printed;
	char		lm;
}				t_tab;

int				ft_printf(char *format, ...);
char			*ft_strdup(const char *s1);
void			ft_putchar(t_tab *tab, wint_t c);
void			ft_putwchar(t_tab *tab, wchar_t *c);
void			ft_flags(t_tab *tab);
void			ft_width(t_tab *tab);
void			ft_precision(t_tab *tab);
void			ft_length_mod(t_tab *tab);
void			ft_c(t_tab *tab);
int				ft_s(t_tab *tab);
int				ft_p_or_x(t_tab *tab);
int				ft_di(t_tab *tab);
int				ft_u(t_tab *tab);
void			ft_percent(t_tab *tab);
void			ft_n(t_tab *tab);
int				ft_f(t_tab *tab);
int				ft_e(t_tab *tab);
int				ft_g(t_tab *tab);
int				ft_o(t_tab *tab);
char			*ft_itoa(char sign, intmax_t n);
char			*ft_uitoa(uintmax_t n);
char			*ft_uitoabase(uintmax_t n, char *base, int base_size);
char			*ft_ftoa(long double n, int precision, char sign);
char			*ft_ftoa_e(long double n, int precision, char sign);
char			*ft_etoa(long double n, int precision, char sign);
size_t			ft_strlen(const char *s);
size_t			ft_wstrlen(const wchar_t *s);
void			ft_prepad_1(t_tab *tab);
void			ft_postpad_1(t_tab *tab);
void			ft_prepad_2a(t_tab *tab);
void			ft_prepad_2b(t_tab *tab);
void			ft_postpad_2(t_tab *tab);
void			ft_pad_3(t_tab *tab, int n);
void			ft_prepad_3(t_tab *tab);
void			ft_prepad_3_neg(t_tab *tab);
void			ft_postpad_3(t_tab *tab);
void			ft_postpad_3_neg(t_tab *tab);
void			ft_prepad_4(t_tab *tab);
void			ft_postpad_4(t_tab *tab);
void			ft_prepad_5(t_tab *tab);
void			ft_prepad_5_neg(t_tab *tab);
void			ft_postpad_5(t_tab *tab);
void			ft_prepad_6(t_tab *tab);
void			ft_prepad_6_neg(t_tab *tab);
void			ft_postpad_6(t_tab *tab);
void			ft_prepad_7(t_tab *tab);
void			ft_postpad_7(t_tab *tab);
void			ft_prepad_8(t_tab *tab);
void			ft_prepad_8_neg(t_tab *tab);
void			ft_postpad_8(t_tab *tab);
void			ft_e_sharp(t_tab *tab);
void			safefree(void **ptr);

#endif

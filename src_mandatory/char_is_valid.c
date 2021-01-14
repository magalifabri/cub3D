/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_is_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:08:58 by mfabri            #+#    #+#             */
/*   Updated: 2021/01/14 19:31:08 by mfabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_is_valid(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' || c == 'E'
    || c == 'W' || c == ' ' || c == '\n');
}

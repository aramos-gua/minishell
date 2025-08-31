/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:20 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 11:52:18 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	find_unintlen(unsigned int u)
{
	int	digits;

	digits = 0;
	if (u == 0)
		digits += 1;
	while (u > 0)
	{
		u /= 10;
		digits++;
	}
	return (digits);
}

int	ft_print_u(unsigned int u)
{
	char	val;

	if (u <= 9)
	{
		val = u + '0';
		write(1, &val, 1);
	}
	else if (u > 9)
	{
		val = u % 10 + '0';
		ft_print_u(u / 10);
		write(1, &val, 1);
	}
	return (find_unintlen(u));
}

int	ft_print_u_flags(unsigned int u, char type, t_flags s_flags)
{
	int		len;
	char	width;

	len = 0;
	width = ' ';
	s_flags.hash = 0;
	s_flags.plus = 0;
	s_flags.space = 0;
	if (s_flags.precision < 0 && u != 0)
		s_flags.width -= find_unintlen(u);
	len += wpl(type, width, s_flags);
	if (s_flags.precision >= 0 || (s_flags.precision == -1 && u != 0)
		|| (s_flags.precision == -2 && u != 0))
		len += ft_print_u(u);
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(width);
	return (len);
}

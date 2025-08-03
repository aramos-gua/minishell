/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:26:08 by mtice             #+#    #+#             */
/*   Updated: 2025/02/10 18:14:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_flag(char c)
{
	if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '.')
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	else
		return (0);
}

int	is_spec(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	else
		return (0);
}

int	hps(char type, t_flags s_flags)
{
	int	len;

	len = 0;
	if (type == '-')
		len += ft_print_c('-');
	if (s_flags.space == 1)
		len += ft_print_c(' ');
	if (s_flags.plus == 1)
		len += ft_print_c('+');
	if (s_flags.hash == 1 && type == 'X' )
		len += ft_print_s("0X");
	else if (s_flags.hash == 1 && (type == 'x' || type == 'p'))
		len += ft_print_s("0x");
	return (len);
}

int	wpl(char type, char width, t_flags s_flags)
{
	int	len;

	len = 0;
	if (s_flags.zero == 1)
		width = '0';
	if (s_flags.left_adjust == 0)
	{
		while (s_flags.width-- > 0)
			len += ft_print_c(width);
		if (s_flags.hash == 1 || s_flags.plus == 1
			|| s_flags.space == 1 || type == '-')
			len += hps(type, s_flags);
		while (s_flags.precision-- > 0)
			len += ft_print_c('0');
	}
	else if (s_flags.left_adjust == 1)
	{
		if (s_flags.hash == 1 || s_flags.plus == 1
			|| s_flags.space == 1 || type == '-')
			len += hps(type, s_flags);
		while (s_flags.precision-- > 0)
			len += ft_print_c('0');
	}
	return (len);
}

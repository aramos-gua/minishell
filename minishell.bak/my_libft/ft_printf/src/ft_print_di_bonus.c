/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:13 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 14:07:53 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	find_intlen(int n)
{
	int	digits;

	digits = 0;
	if (n == -2147483648)
		return (10);
	else if (n < 0)
		n *= -1;
	if (n == 0)
		digits += 1;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

int	ft_print_di(int n)
{
	char	val;
	int		len;

	len = find_intlen(n);
	if (n == -2147483648)
		len = ft_print_s("2147483648");
	if (n >= 0 && n <= 9)
	{
		val = n + '0';
		write(1, &val, 1);
	}
	else if (n > 9)
	{
		val = n % 10 + '0';
		ft_print_di(n / 10);
		write(1, &val, 1);
	}
	return (len);
}

static void	negativen(int *n, char *type, t_flags *s_flags)
{
	if (*n < 0)
	{
		if (*n != -2147483648)
			*n *= -1;
		s_flags -> space = 0;
		s_flags -> plus = 0;
		*type = '-';
	}
}

int	ft_print_di_flags(int n, char type, t_flags s_flags)
{
	int		len;
	char	width;

	len = 0;
	width = ' ';
	s_flags.hash = 0;
	if (s_flags.precision < 0 && n != 0)
		s_flags.width -= find_intlen(n);
	if ((s_flags.plus == 1 || s_flags.space == 1 || n < 0)
		&& s_flags.width >= 1)
		s_flags.width -= 1;
	negativen(&n, &type, &s_flags);
	if (s_flags.zero == 1 && s_flags.width > 0)
	{
		len += hps(type, s_flags);
		s_flags.space = 0;
		s_flags.plus = 0;
		type = 'b';
	}
	len += wpl(type, width, s_flags);
	if (s_flags.precision >= 0 || (s_flags.precision < 0 && n != 0))
		len += ft_print_di(n);
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(width);
	return (len);
}

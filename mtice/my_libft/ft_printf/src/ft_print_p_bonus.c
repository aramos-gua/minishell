/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:13:04 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 14:09:19 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_print_p(void *p, char type)
{
	unsigned long	address;
	int				len;

	if (p == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	address = (unsigned long)p;
	len = ft_print_x(address, type);
	return (len);
}

static void	ifpnull(void *p, t_flags *s_flags)
{
	if (p == NULL)
	{
		if (s_flags -> width >= 5)
			s_flags -> width -= 4;
		else
			s_flags -> width = 0;
		s_flags -> hash = 0;
	}
}

int	ft_print_p_flags(void *p, char type, t_flags s_flags)
{
	int		len;
	char	width;

	len = 0;
	width = ' ';
	s_flags.space = 0;
	s_flags.plus = 0;
	s_flags.hash = 1;
	s_flags.precision = 0;
	ifpnull(p, &s_flags);
	if (s_flags.width >= 2 && s_flags.hash == 1)
		s_flags.width -= 2;
	else if (s_flags.width == 1 && s_flags.hash == 1)
		s_flags.width -= 1;
	if (s_flags.zero == 1 && s_flags.width > 0)
	{
		len += hps(type, s_flags);
		s_flags.hash = 0;
	}
	len += wpl(type, width, s_flags);
	len += ft_print_p(p, type);
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(width);
	return (len);
}

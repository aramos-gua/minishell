/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:23 by mtice             #+#    #+#             */
/*   Updated: 2025/02/10 17:36:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_print_c(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_print_c_flags(char c, t_flags s_flags)
{
	int	len;

	len = 0;
	if (s_flags.width >= 1)
		s_flags.width -= 1;
	s_flags.precision = 0;
	s_flags.zero = 0;
	s_flags.hash = 0;
	s_flags.plus = 0;
	s_flags.space = 0;
	while (s_flags.left_adjust == 0 && s_flags.width-- > 0)
		len += ft_print_c(' ');
	len += ft_print_c(c);
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(' ');
	return (len);
}

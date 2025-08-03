/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:39 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 15:32:35 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_print_m(t_flags *s_flags, const char *fmt, int i, va_list args)
{
	int	len;

	len = 0;
	flag_combo(s_flags, args, fmt[i]);
	if (fmt[i] == 'c')
		len += ft_print_c_flags(va_arg(args, int), *s_flags);
	else if (fmt[i] == 's')
		len += ft_print_s_flags(va_arg(args, char *), *s_flags);
	else if (fmt[i] == 'p')
		len += ft_print_p_flags(va_arg(args, void *), fmt[i], *s_flags);
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		len += ft_print_di_flags(va_arg(args, int), fmt[i], *s_flags);
	else if (fmt[i] == 'u')
		len += ft_print_u_flags(va_arg(args, unsigned int), fmt[i], *s_flags);
	else if (fmt[i] == 'x' || fmt[i] == 'X')
		len += ft_print_x_flags(va_arg(args, unsigned long), fmt[i], *s_flags);
	else if (fmt[i] == '%')
		len += ft_print_c('%');
	else
		return (0);
	return (len);
}

void	ft_flags(t_flags *s_flags, const char *fmt, int i)
{
	while (fmt[i] == '%' || fmt[i] == '-' || fmt[i] == '#'
		|| fmt[i] == '+' || fmt[i] == ' ' || fmt[i] == '0')
	{
		if (fmt[i] == '-')
			s_flags -> left_adjust = 1;
		else if (fmt[i] == '+')
			s_flags -> plus = 1;
		else if (fmt[i] == ' ')
			s_flags -> space = 1;
		else if (fmt[i] == '#')
			s_flags -> hash = 1;
		else if (fmt[i] == '0')
			s_flags -> zero = is_zero(fmt);
		i++;
	}
	if ((fmt[i] >= '1' && fmt[i] <= '9') || fmt[i] == '.')
		find_wp(s_flags, fmt, i);
}

int	ft_print_b(const char *fmt, int i, va_list args)
{
	t_flags	s_flags;
	int		len;

	init_struct(&s_flags);
	len = 0;
	ft_flags(&s_flags, fmt, i);
	while (is_spec(fmt[i]) != 1 && fmt[i] != '%')
		i++;
	if (is_spec(fmt[i]) == 1 || fmt[i] == '%')
		len += ft_print_m(&s_flags, fmt, i, args);
	else
		return (0);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	int		i;
	int		len;
	va_list	args;	

	i = 0;
	len = 0;
	va_start(args, fmt);
	if (fmt[i] == '\0')
		return (0);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
		{
			len += ft_print_b(fmt, i + 1, args);
			i++;
			while (is_flag(fmt[i]) == 1 || is_flag(fmt[i]) == 2)
				i++;
		}
		else
			len += ft_print_c(fmt[i]);
		i++;
	}
	va_end(args);
	return (len);
}
/*
#include <limits.h>
#include <stdio.h>

int main(void)
{
	int len;
	char *s = NULL;

	len = ft_printf(" %-13p %-14p ", ULONG_MAX, -ULONG_MAX);
	printf("\n%d\n", len);
	return (0);
}*/

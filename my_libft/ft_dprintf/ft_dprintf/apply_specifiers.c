/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_specifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:57 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:37:02 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	apply_next_0(t_form *format, va_list args);
static void	apply_next_1(t_form *format, va_list args);
static void	change_flags(t_form *format);

void	apply_specifier(t_form *format, va_list args)
{
	const char		*str;

	if (format-> f_specifier == 'c')
		pbonus_c((char)va_arg(args, int), format);
	if (format-> f_specifier == 's')
	{
		str = va_arg(args, char *);
		if (!str)
		{
			if (!(format -> precision >= 6 || format -> precision < 0))
				return ;
			else
				str = "(null)";
		}
		pbonus_s(str, format, args);
	}
	else
		apply_next_0(format, args);
}

static void	apply_next_0(t_form *format, va_list args)
{
	unsigned int	number;

	if (format -> f_specifier == 'p')
		pbonus_p(va_arg(args, int *), format);
	else if (format-> f_specifier == 'd' || format-> f_specifier == 'i')
	{
		change_flags(format);
		pbonus_di(va_arg(args, int), format);
	}
	else if (format-> f_specifier == 'u')
	{
		number = (unsigned int) va_arg(args, int);
		change_flags(format);
		pbonus_u(number, format);
	}
	else
		apply_next_1(format, args);
}

static void	apply_next_1(t_form *format, va_list args)
{
	unsigned int	number;

	if (format -> f_specifier == 'x')
	{
		number = (unsigned )va_arg(args, int);
		change_flags(format);
		print_hx(number, format, 0);
	}
	else if (format -> f_specifier == 'X')
	{
		number = (unsigned) va_arg(args, int);
		change_flags(format);
		print_hx(number, format, 1);
	}
	else if (format -> f_specifier == '%')
		format->p_chars += dprintf_putchar('%', format->fd);
}

static void	change_flags(t_form *format)
{
	if ((format -> precision >= 0) || (format -> flags & FLAG_MINUS))
		if (format -> flags & FLAG_ZERO)
			format -> flags &= ~FLAG_ZERO;
	if ((format -> flags & FLAG_PLUS) && (format -> flags & FLAG_SPACE))
		format -> flags &= ~FLAG_SPACE;
}

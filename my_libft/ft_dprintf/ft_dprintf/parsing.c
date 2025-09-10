/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:36:39 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:36:43 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	parse_flags(const char **str, t_form *format)
{
	while (**str == '-' || **str == '0' || **str == '#' || \
**str == '+' || **str == ' ')
	{
		if (**str == '-')
			format -> flags |= FLAG_MINUS;
		if (**str == '0')
			format -> flags |= FLAG_ZERO;
		if (**str == '#')
			format -> flags |= FLAG_HASH;
		if (**str == '+')
			format -> flags |= FLAG_PLUS;
		if (**str == ' ')
			format -> flags |= FLAG_SPACE;
		(*str)++;
	}
}

void	parse_width(const char **str, t_form *format, va_list args)
{
	if (**str >= '0' && **str <= '9')
	{
		format -> width = dprintf_atoi(*str);
		while (**str >= '0' && **str <= '9')
			(*str)++;
	}
	else if (**str == '*')
	{
		format -> width = va_arg(args, int);
		(*str)++;
	}
}

void	parse_precision(const char **str, t_form *format, va_list args)
{
	if (**str == '.')
	{
		(*str)++;
		if (**str >= '0' && **str <= '9')
		{
			format -> precision = dprintf_atoi(*str);
			while (**str >= '0' && **str <= '9')
				(*str)++;
		}
		else if (**str == '*')
		{
			format -> precision = va_arg(args, int);
			(*str)++;
		}
		else
			format -> precision = 0;
	}
}

void	parse_specifier(const char **str, t_form *format)
{
	format -> f_specifier = **str;
}

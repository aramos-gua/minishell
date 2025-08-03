/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:26:08 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 15:30:38 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	init_struct(t_flags *s_flags)
{
	s_flags -> left_adjust = 0;
	s_flags -> plus = 0;
	s_flags -> space = 0;
	s_flags -> hash = 0;
	s_flags -> zero = 0;
	s_flags -> width = 0;
	s_flags -> precision = 0;
}

int	is_zero(const char *fmt)
{
	int	i;

	i = 0;
	if (fmt[i] == '\0')
		return (0);
	while (fmt[i] != '%' && fmt[i] != '\0')
		i++;
	if (fmt[i] == '%')
	{
		if (fmt[i + 1] == '0')
			return (1);
		while (fmt[i] != '0' && fmt[i] != '\0')
			i++;
		if (fmt[i] == '0' && is_flag(fmt[i - 1]) == 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	find_wp(t_flags *s_flags, const char *fmt, int i)
{
	while (is_flag(fmt[i]) == 2 && is_spec(fmt[i]) != 1
		&& fmt[i] != '.' && fmt[i] != '\0')
	{
		s_flags -> width = s_flags -> width * 10 + (fmt[i] - '0');
		i++;
	}
	if (fmt[i] == '.' && fmt[i] != '\0')
	{
		i++;
		if ((is_spec(fmt[i]) == 1 && s_flags -> width == 0)
			|| (fmt[i] == '0' && is_spec(fmt[i + 1]) == 1))
			s_flags -> precision = -1;
		else if (is_spec(fmt[i]) == 1 && s_flags -> width > 0)
			s_flags -> precision = -2;
		while (is_flag(fmt[i]) == 2 && is_spec(fmt[i]) != 1 && fmt[i] != '\0')
		{
			if (s_flags -> precision == -1)
				break ;
			s_flags -> precision = s_flags -> precision * 10 + (fmt[i] - '0');
			i++;
		}
	}
}

static void	combo_two(t_flags *s_flags, int arg_len)
{
	if (s_flags -> zero == 1 && (s_flags -> left_adjust == 1
			|| s_flags -> precision > 0 || s_flags -> precision < 0))
		s_flags -> zero = 0;
	if (s_flags -> width > arg_len && s_flags -> precision >= 0)
		s_flags -> width -= arg_len;
	else if (s_flags -> width <= arg_len && s_flags -> precision >= 0)
		s_flags -> width = 0;
	if ((s_flags -> precision > arg_len) && s_flags -> precision >= 0)
		s_flags -> precision -= arg_len;
	else if (s_flags -> precision <= arg_len && s_flags -> precision >= 0)
		s_flags -> precision = 0;
	if ((s_flags -> width > s_flags -> precision) && s_flags -> precision >= 0)
		s_flags -> width -= s_flags -> precision;
	else if ((s_flags -> width <= s_flags -> precision)
		&& s_flags -> precision >= 0)
		s_flags -> width = 0;
}

void	flag_combo(t_flags *s_flags, va_list args, char type)
{
	va_list	args_copy;
	int		arg_len;

	va_copy(args_copy, args);
	arg_len = 0;
	if (type == 'c' || type == 's')
		return ;
	else if (type == 'd' || type == 'i')
		arg_len += find_intlen(va_arg(args_copy, int));
	else if (type == 'u')
		arg_len += find_unintlen(va_arg(args_copy, unsigned int));
	else if (type == 'x' || type == 'X')
		arg_len += find_hexlen(va_arg(args_copy, unsigned int));
	else if (type == 'p')
		arg_len += find_hexlen(va_arg(args_copy, unsigned long));
	combo_two(s_flags, arg_len);
}

/*int main(void)
{
	t_flags s_flags;
  	int i = 0;
	int width;
  	const char fmt[] = "%7p";
	init_struct(&s_flags);
	width = find_wp(&s_flags, fmt, 1);
	//printf("width: %d", s_flags.width);
	//printf("precision: %d", s_flags.precision);
	printf("width: %d", s_flags.width);
	return (0);
}*/

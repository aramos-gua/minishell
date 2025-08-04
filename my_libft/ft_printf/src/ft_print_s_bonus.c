/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:07:50 by mtice             #+#    #+#             */
/*   Updated: 2025/02/11 13:37:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_strlen(const char *fmt)
{
	int	i;

	i = 0;
	if (fmt[i] == '\0')
		return (0);
	while (fmt[i] != '\0')
		i++;
	return (i);
}

int	ft_print_s(char *s)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	find_p(char *s, t_flags *s_flags)
{
	int	p;

	if (s != NULL)
		p = ft_strlen(s);
	else
		p = 6;
	if (s_flags -> precision > 0 && s_flags -> precision < p)
		p = s_flags -> precision;
	if (s_flags -> width >= p && s_flags -> precision >= 0)
		s_flags -> width -= p;
	else if (s_flags -> width < p && s_flags -> precision >= 0)
		s_flags -> width = 0;
	return (p);
}

int	ft_print_s_flags(char *s, t_flags s_flags)
{
	int	len;
	int	i;
	int	p;

	len = 0;
	i = 0;
	if (s == NULL && s_flags.precision == -1 && s_flags.width == 0)
		return (0);
	s_flags.zero = 0;
	s_flags.hash = 0;
	s_flags.plus = 0;
	s_flags.space = 0;
	p = find_p(s, &s_flags);
	while (s_flags.left_adjust == 0 && s_flags.width-- > 0)
		len += ft_print_c(' ');
	if (s == NULL && (s_flags.precision >= 6 || s_flags.precision == 0))
		len += ft_print_s("(null)");
	else if (s != NULL && s_flags.precision >= 0)
	{
		while (s[i] != '\0' && i < p)
			len += ft_print_c(s[i++]);
	}
	while (s_flags.left_adjust == 1 && s_flags.width-- > 0)
		len += ft_print_c(' ');
	return (len);
}

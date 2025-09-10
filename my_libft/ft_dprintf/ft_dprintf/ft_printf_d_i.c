/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d_i.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:37:29 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:37:34 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	pd(int n, int len, t_form *format, char **str);
static void	pad_helper(int padding, t_form *format);
static char	*prefix(int n, t_form *format);

//%d and %i specifiers
void	pbonus_di(int n, t_form *format)
{
	char	*str;
	int		len;
	int		padding;

	str = ft_printf_itoa(n);
	if (n == 0 && ((format -> width == 0) || (format -> precision == 0)))
		len = 0;
	else
		len = append_0(&str, format);
	padding = pd(n, len, format, &str);
	if (!(format -> flags & FLAG_MINUS))
		pad_helper(padding, format);
	if (!(n == 0 && ((format -> width == 0) || (format -> precision == 0))))
		(format->p_chars) += dprintf_putstr(str, format->fd);
	format -> pad = ' ';
	if (format -> flags & FLAG_MINUS)
		pad_helper(padding, format);
	free(str);
}

int	append_0(char **str, t_form *format)
{
	int		len;
	int		difference;
	char	*new_str;

	if (!str || !*str || !format)
		return (0);
	len = dprintf_strlen(*str);
	if ((format -> precision) > len)
	{
		difference = (format -> precision) - len;
		new_str = malloc ((difference + len + 1) * sizeof(char));
		if (!new_str)
			return (0);
		dprintf_memset(new_str, '0', difference);
		dprintf_strlcpy(new_str + difference, *str, (difference + len + 1));
		free(*str);
		*str = new_str;
		len += difference;
	}
	return (len);
}

static int	pd(int n, int len, t_form *format, char **str)
{
	int		padding;
	char	*new_str;

	padding = 0;
	if (n < 0 || format->flags & FLAG_PLUS || format->flags & FLAG_SPACE)
	{
		if (format -> flags & FLAG_ZERO)
		{
			(format->p_chars) += dprintf_putstr(prefix(n, format), format->fd);
			format -> pad = '0';
		}
		else
		{
			new_str = dprintf_strjoin(prefix(n, format), *str);
			free(*str);
			*str = new_str;
		}
		(len)++;
	}
	if (format -> flags & FLAG_ZERO)
		format -> pad = '0';
	if (format -> width > len)
		padding = (format -> width) - len;
	return (padding);
}

static char	*prefix(int n, t_form *format)
{
	if (n < 0)
		return ("-");
	if (format -> flags & FLAG_PLUS)
		return ("+");
	if (format -> flags & FLAG_SPACE)
		return (" ");
	return ("");
}

static void	pad_helper(int padding, t_form *format)
{
	while (padding--)
		(format->p_chars) += dprintf_putchar(format -> pad, format->fd);
}

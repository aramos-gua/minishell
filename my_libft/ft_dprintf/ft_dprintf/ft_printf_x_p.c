/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:37:44 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 11:37:49 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	p_padding(int len, t_form *format);
static void	hx_padding(int len, t_form *format);

//%x specifier
void	print_hx(unsigned int n, t_form *format, int upp)
{
	int		len;
	char	*str;

	str = ft_hxtoa(n, upp);
	if (n == 0 && (format -> width == 0 || format -> precision == 0))
		len = 0;
	else
		len = append_0(&str, format);
	if (format -> flags & FLAG_HASH && n != 0)
	{
		if (upp == 0)
			(format->p_chars) += dprintf_putstr("0x", format->fd);
		if (upp == 1)
			(format->p_chars) += dprintf_putstr("0X", format->fd);
		len += 2;
	}
	if (!(format -> flags & FLAG_MINUS))
		hx_padding(len, format);
	if (!(n == 0 && (format -> width == 0 || format -> precision == 0)))
		(format->p_chars) += dprintf_putstr(str, format->fd);
	if (format -> flags & FLAG_MINUS)
		hx_padding(len, format);
	free(str);
}

static void	hx_padding(int len, t_form *format)
{
	int		padding;

	padding = 0;
	if (format -> width > len)
		padding = format -> width - len;
	if (format -> flags & FLAG_ZERO)
		format -> pad = '0';
	while (padding--)
		(format->p_chars) += dprintf_putchar(format -> pad, format->fd);
}

//%p specifier
void	pbonus_p(void *address, t_form *format)
{
	unsigned long	number;
	char			*hex;
	char			*str;
	int				len;

	number = (unsigned long)address;
	hex = ft_hxtoa(number, 0);
	if (!address)
	{
		str = malloc(6 * sizeof(char));
		dprintf_strlcpy(str, "(nil)", 6);
	}
	else
		str = dprintf_strjoin("0x", hex);
	len = dprintf_strlen(str);
	if (!(format -> flags & FLAG_MINUS))
		p_padding(len, format);
	(format->p_chars) += dprintf_putstr(str, format->fd);
	if (format -> flags & FLAG_MINUS)
		p_padding(len, format);
	free(hex);
	free(str);
}

static void	p_padding(int len, t_form *format)
{
	int		padding;

	padding = 0;
	if (format -> width > len)
		padding = format -> width - len;
	if (format -> precision > len)
		padding = format -> precision - len;
	while (padding--)
		(format->p_chars) += dprintf_putchar(' ', format->fd);
}

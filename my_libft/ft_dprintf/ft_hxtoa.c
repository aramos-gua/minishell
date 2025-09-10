/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hxtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:55:02 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:55:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

static void	x_to_alpha(char *c);

int	get_len(unsigned long num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

char	*ft_hxtoa(unsigned long n, int upp)
{
	unsigned long	num;
	char			*num_in_hex;
	char			*lookup_array;
	int				len;

	num = (unsigned long)n;
	len = 0;
	if (n == 0)
		len = 1;
	else
		len = get_len(num);
	num_in_hex = malloc((len + 1) * sizeof (char));
	if (!num_in_hex)
		return (NULL);
	lookup_array = "0123456789abcdef";
	num_in_hex[len] = '\0';
	while (len > 0)
	{
		num_in_hex[--len] = lookup_array[num % 16];
		num /= 16;
	}
	if (upp == 1)
		x_to_alpha(num_in_hex);
	return (num_in_hex);
}

static void	x_to_alpha(char *c)
{
	while (*c)
	{
		*c = (char)dprintf_toupper(*c);
		c++;
	}
}

int	ft_print_hex(unsigned long number, int upp)
{
	char			*num_hex;
	int				chars_printed;

	num_hex = ft_hxtoa(number, upp);
	chars_printed = dprintf_putstr(num_hex, 1);
	free(num_hex);
	return (chars_printed);
}

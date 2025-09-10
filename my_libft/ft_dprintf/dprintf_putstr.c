/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:59:15 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:59:16 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

int	dprintf_putstr(char *s, int fd)
{
	int	count;

	count = 0;
	while (*s)
	{
		dprintf_putchar(*s, fd);
		count++;
		s++;
	}
	return (count);
}

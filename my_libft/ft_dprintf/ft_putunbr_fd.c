/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:59:22 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:59:23 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

int	dprintf_putunbr(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
	count++;
	return (count);
}

//int	main(void)
//{
//	ft_putnbr_fd(-2147483648LL, 1);
//}

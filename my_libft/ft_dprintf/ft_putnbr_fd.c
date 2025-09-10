/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:59:07 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:59:09 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

int	dprintf_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			count++;
			n = 147483648;
		}
		else
			n = -n;
		count++;
	}
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

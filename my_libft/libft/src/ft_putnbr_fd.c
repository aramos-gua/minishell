/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:33:25 by mtice             #+#    #+#             */
/*   Updated: 2024/12/11 17:51:13 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	val;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 0 && n <= 9)
	{
		val = n + '0';
		write(fd, &val, 1);
	}
	else if (n > 9)
	{
		val = n % 10 + '0';
		ft_putnbr_fd(n / 10, fd);
		write(fd, &val, 1);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(-0, 1);
	return (0);
}*/

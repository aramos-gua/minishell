/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:54:24 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:54:29 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

int	dprintf_atoi(const char *nptr)
{
	int			num;
	int			sign;

	sign = 1;
	num = 0;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		if (*(nptr + 1) >= '0' && *(nptr + 1) <= '9')
		{
			nptr++;
			break ;
		}
		return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
		num = num * 10 + (*nptr++ - '0');
	return (num * sign);
}

//#include <stdio.h>
//
//int	main(void)
//{
//	const char	my_numbers [] = "2147483647";
//
//	printf("Original:%d\n", atoi(my_numbers));
//	printf("Mine:%d\n",ft_atoi(my_numbers));
//	return (0);
//}	

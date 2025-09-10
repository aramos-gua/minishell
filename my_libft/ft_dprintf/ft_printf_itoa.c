/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:29 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:58:30 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

static int	num_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_printf_itoa(int n)
{
	long	num;
	char	*result;
	int		len;

	num = (long)n;
	if (n < 0)
		num = -num;
	len = num_len(num);
	result = (char *) malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num == 0)
	{
		result[0] = '0';
		return (result);
	}
	while (num > 0)
	{
		result[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
//
//#include <stdio.h>
//
//int	main(void)
//{
//	int	number;
//
//	number = -2147483648;
//	printf("%s\n", printf_itoa(number));
//	return (0);
//}

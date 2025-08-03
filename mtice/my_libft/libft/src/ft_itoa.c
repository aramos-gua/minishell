/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:18:33 by mtice             #+#    #+#             */
/*   Updated: 2024/12/12 17:50:29 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digits(long n)
{
	int	digits;

	digits = 0;
	if (n == -2147483648)
		digits += 11;
	else if (n < 0)
	{
		digits += 1;
		n = n * (-1);
	}
	else if (n == 0)
		digits += 1;
	while (n > 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static void	ft_i_in_pointer(char *p, int n, int i, int len)
{
	if (n < 0)
	{
		p[i] = '-';
		i++;
		n = n * (-1);
	}
	while (n >= 0 && len >= (1 + i))
	{
		p[len - 1] = ((n % 10) + '0');
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	int		end;
	char	*p;

	i = 0;
	len = ft_digits((long)n);
	end = len;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		p[i] = '-';
		i++;
		p[i] = 2 + '0';
		i++;
		n = 147483648;
	}
	ft_i_in_pointer(p, n, i, len);
	p[end] = '\0';
	return (p);
}
/*
int	main(void)
{
	char	*result;

	result = ft_itoa(-2147483648);
	printf("%s", result);
	free(result);
	return (0);
}*/

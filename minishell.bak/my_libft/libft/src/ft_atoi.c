/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:26:09 by mtice             #+#    #+#             */
/*   Updated: 2024/12/05 16:52:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0')
	{
		if ((nptr[i] >= '0' && nptr[i] <= '9'))
			number = number * 10 + (nptr[i] - '0');
		else
			break ;
		i++;
	}
	return (number * sign);
}
/*
int	main(void)
{
	char	*str = "      -1111111";
	printf("atoi: %i\n", atoi(str));
	printf("ft_atoi: %i", ft_atoi(str));
	return (0);
}*/

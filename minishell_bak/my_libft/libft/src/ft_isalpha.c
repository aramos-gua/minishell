/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:12:23 by mtice             #+#    #+#             */
/*   Updated: 2024/11/28 15:04:16 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	int	result;

	result = ft_isalpha(97);
	printf("Result: %d", result);
	return (0);
}
*/
/*TEST
int	 main (void)
{
	printf("%d", isalpha(91));
	return (0);
}*/

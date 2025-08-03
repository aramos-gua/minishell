/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:05:12 by mtice             #+#    #+#             */
/*   Updated: 2024/11/30 18:57:47 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}
/*
int	main(void)
{
	int	result;

	result = ft_strlen(" ");
	printf("%d", result);
	return (0);
}*/
/*TEST
int	main(void)
{
	int	result;

	result = strlen(" ");
	printf("%d", result);
	return (0);
}*/

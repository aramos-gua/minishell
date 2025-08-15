/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:33:56 by mtice             #+#    #+#             */
/*   Updated: 2024/12/05 17:03:32 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((s1[i] > s2[i]) || (s1[i] < s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[3] = "ABE";
	char	str2[10] = "ABED";

	printf("strncmp: %d\n", strncmp(str1, str2, 10));
	printf("ft_strncmp: %d", ft_strncmp(str1, str2, 10));
	return (0);
}*/

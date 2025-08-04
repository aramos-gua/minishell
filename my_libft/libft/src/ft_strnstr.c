/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:21:46 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 14:55:05 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*l;
	size_t	i;
	size_t	j;

	b = (char *)big;
	l = (char *)little;
	i = 0;
	if (l[0] == '\0')
		return (b);
	while (b[i] != '\0' && (i < len))
	{
		if (b[i] == l[0])
		{
			j = 0;
			while (b[i + j] == l[j] && (i + j < len) && l[j] != '\0')
			{
				if (l[j + 1] == '\0')
					return (&b[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	big[] = "lorem ipsum dolor sit amet";
	char	little[] = "ipsum";

	printf("This is big: %s\n", big);
	printf("This is little: %s\n", little);
	printf("This is little in big: %s\n", ft_strnstr(big, little, 30));

	return (0);
}*/

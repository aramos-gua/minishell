/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:45:52 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 16:18:20 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	p = (char *)s;
	c = (char)c;
	while (p[i] != '\0')
	{
		if (p[i] == c)
			return (&p[i]);
		i++;
	}
	if (c == '\0')
		return (&p[i]);
	return (NULL);
}
/*
int	main(void)
{
	char str[] = "This is my mention";

	printf("ft_strchr: %s\n", ft_strchr(str, 't' + 256));
	printf("strchr: %s", strchr(str, 't' + 256));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:07:58 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 17:03:44 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		f;
	char		*p;

	f = ft_strlen(s);
	p = (char *)s;
	c = (char)c;
	if (c == 0)
		return (&p[f]);
	while (f != 0)
	{
		f--;
		if (p[f] == c)
			return (&p[f]);
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "bonjour";

	printf("%s", ft_strrchr(str, 'b'));
	return (0);
}*/

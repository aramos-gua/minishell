/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:47:48 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 16:01:06 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	ptn;
	size_t			i;

	src = (unsigned char *)s;
	ptn = (unsigned char)c;
	if (c == 0 && n != 0)
		return (&src[ft_strlen(s)]);
	if (n == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (src[i] == ptn)
			return ((void *)&src[i]);
		i++;
	}
	if (ptn == '\0')
		return ((void *)&src[i]);
	return (NULL);
}
/*
int	main(void)
{
	char str[] = "";

	printf("ft_memchr: %s\n", (char *)ft_memchr((void *)str, 0, 1));
	printf("memchr: %s", (char *)memchr((void *)str, 0, 1));
	return (0);
}*/

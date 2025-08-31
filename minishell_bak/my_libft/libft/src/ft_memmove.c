/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:27:05 by mtice             #+#    #+#             */
/*   Updated: 2024/12/12 15:14:21 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (src == NULL && dest == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (d < s || d >= s + n)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}
/*
int	main(void)
{
	char	str[] = "abcde";
	char	dest[] = "fghijk";

	printf("dest: %s\n", dest);
	printf("ft_memmove: %s\n", (char *)ft_memmove(dest, str, 1));
	printf("memmove: %s\n", (char *)memmove(dest, str, 1));
	return (0);
}*/

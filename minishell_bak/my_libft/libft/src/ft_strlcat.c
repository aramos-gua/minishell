/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:10:23 by mtice             #+#    #+#             */
/*   Updated: 2024/12/02 12:35:58 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dst_len;
	unsigned int	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
	{
		return (size + src_len);
	}
	while (src[i] != '\0' && (size - 1) > (dst_len + i))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int	main(void)
{
	const char	src1[] = "efghijk";
	char	dst1[] = "abcd";

	printf("Size of Dest: %d\n", ft_strlen_static(dst1));
	printf("Strlcat: %zu\n", ft_strlcat(dst1, src1, 7));
	printf("Mod Dest: %s\n", dst1);
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:59:31 by mtice             #+#    #+#             */
/*   Updated: 2024/11/30 20:02:11 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dst_size;
	unsigned int	src_len;

	i = 0;
	dst_size = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	else if (size <= dst_size || size > dst_size)
	{
		while (src[i] != '\0' && size != 1)
		{
			dst[i] = src[i];
			i++;
			size--;
		}
	}
	dst[i] = '\0';
	return (src_len);
}
/*
int	main(void)
{
	const char	src1[] = "efghijk";
	char	dst1[4];

	printf("Size of Dest: %d", ft_strlen_static(dst1));
	printf("Strlcpy: %zu\n", ft_strlcpy(dst1, src1, 7));
	printf("Mod Dest: %s\n", dst1);
	return (0);
}*/	

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:00:07 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:00:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

size_t	dprintf_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	len_dst = dprintf_strlen(dst);
	len_src = dprintf_strlen(src);
	i = 0;
	j = len_dst;
	if (size == 0)
		return (len_src);
	if (size <= len_dst)
		return (size + len_src);
	while (src[i] != '\0' && j < size - 1)
	{
		dst [j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (len_dst + len_src);
}

//int	main(void)
//{
//	char	dst[6] = "Hello.";
//	char	src[11] = " Cat";
//
//	printf("\n%zu\n",  ft_strlcat(dst, src, 4));
//	printf("%s", dst);
//	return (0);
//}

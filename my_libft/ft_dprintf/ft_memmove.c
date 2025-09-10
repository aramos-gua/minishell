/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:12 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 12:58:13 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

void	*dprintf_memmove(void *dest, const void *src, size_t n)
{
	void	*ptr;

	if (n == 0)
		return (dest);
	ptr = dest;
	if (src < dest && dest <= src + (n -1))
	{
		while (n-- > 0)
			*((unsigned char *)dest + n) = *((unsigned const char *)src + n);
	}
	else
		ft_memcpy(dest, src, n);
	return (ptr);
}

//int	main(void)
//{
//	char	src[100] = "abcd"
//
//	memmove(src, src + 2, 4);
//	printf("%s", )
//}

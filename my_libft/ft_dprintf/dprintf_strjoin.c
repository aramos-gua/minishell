/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:00:00 by aramos            #+#    #+#             */
/*   Updated: 2025/02/21 13:00:01 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdft.h"

char	*dprintf_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*ptr_3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = (char *) malloc((dprintf_strlen(s1) + dprintf_strlen(s2)) + 1);
	if (s3 == NULL)
		return (NULL);
	s3[0] = '\0';
	ptr_3 = s3;
	dprintf_strlcat(s3, s1, (dprintf_strlen(s1) + dprintf_strlen(s2)) + 1);
	dprintf_strlcat(s3, s2, (dprintf_strlen(s1) + dprintf_strlen(s2)) + 1);
	return (ptr_3);
}

//int	main (void)
//{
//	char	*s1;
//	char	*s2;
//
//	s1 = "";
//	s2 = " como estas?";
//	printf("Mine: %s", ft_strjoin(s1, s2));
//	return (0);
//}
//

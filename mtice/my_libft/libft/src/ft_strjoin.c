/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:08:36 by mtice             #+#    #+#             */
/*   Updated: 2024/12/06 16:26:09 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*cat;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	cat = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (cat == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		cat[i] = s2[j];
		i++;
		j++;
	}
	cat[i] = '\0';
	return (cat);
}
/*
int	main(void)
{
	char	str1[] = "Hello ";
	char	str2[] = "World!";
	char	*result;

	result = ft_strjoin(str1, str2);
	printf("cat: %s", result);
	free(result);
	return (0);
}*/

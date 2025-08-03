/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:37:02 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 19:15:43 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < start && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	i = 0;
	while (i < len && s[start + i] != '\0')
		i++;
	sub = (char *)malloc((i + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
int	main(void)
{
	char	str[] = "Hello World!";
	char	*result;

	result = ft_substr(str, 4, 3);
	printf("string: %s\n", str);
	printf("substring: %s", result);
	free(result);
	return (0);
}*/

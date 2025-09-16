/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:54:35 by mtice             #+#    #+#             */
/*   Updated: 2024/12/04 17:57:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		s_len;
	char	*dup;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	dup = malloc(sizeof (char) * s_len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
int	main(void)
{
	char *original = "abc";
	char *duplicate = "";
	int	original_len;
	int	duplicate_len;

	duplicate = ft_strdup(original);
	original_len = ft_strlen(original);
	duplicate_len = ft_strlen(duplicate);
	printf("Original string: %s Length: %d\n", original, original_len);
	printf("Duplicate string: %s Length: %d\n", duplicate, duplicate_len);
	free(duplicate);
	return (0);
}*/

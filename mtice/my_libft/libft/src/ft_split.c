/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:46:53 by mtice             #+#    #+#             */
/*   Updated: 2025/07/03 18:43:01 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*static int	ft_string_counter(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			j++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (j);
}*/

static int	ft_string_counter(char const *s, char c)
{
	int	i;
	int	string;

	i = 0;
	string = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			string++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (string);
}

static char	*ft_string_in_pointer(char const *s, char c, int i, int len)
{
	char	*p;
	int		j;

	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	j = 0;
	while (s[i - len] != c && len - 1 >= 0)
	{
		p[j] = s[i - len];
		len--;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		strings;
	int		len;
	char	**arr;

	i = 0;
	k = 0;
	strings = ft_string_counter(s, c);
	arr = (char **)malloc(sizeof(char *) * (strings + 1));
	if (arr == NULL)
		return (NULL);
	while (s[i] != '\0' && k < strings)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		arr[k++] = ft_string_in_pointer(s, c, i, len);
	}
	return (arr[k] = NULL, arr);
}

/*int	main(void)
{
	char str[] = "  Hi   this string has  7  strings  inside    ";
	char del = ' ';
	char **result;
	int	j;

	result = ft_split(str, del);
	j = 0;
	while (j < ft_string_counter(str, del))
	{
		printf("%s\n", result[j]);
		j++;
	}
	free (result)
	int count;
	count = ft_string_counter(str, ' ');
	printf("%d\n", count);
	return (0);
}*/

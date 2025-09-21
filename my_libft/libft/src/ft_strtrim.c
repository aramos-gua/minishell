/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:53:08 by mtice             #+#    #+#             */
/*   Updated: 2024/12/15 19:47:00 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);

static void	ft_in_trim(char *trim, char const *s1,
				unsigned int i, unsigned int j)
{
	unsigned int	k;

	k = 0;
	while (i <= j)
	{
		trim[k] = s1[i];
		k++;
		i++;
	}
	trim[k] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*trim;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (ft_strrchr(set, s1[j]) != NULL && j != 0)
		j--;
	if (j < i)
		return (ft_strdup(""));
	trim = (char *)malloc((j - i + 2) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_in_trim(trim, s1, i, j);
	return (trim);
}
/*
int	main(void)
{
	char	str[] = "abcbabcb";
	char	set[] = "abc";
	char	*result;

	result = ft_strtrim(str, set);
	printf("str: %s\n", str);
	printf("set: %s\n", set);
	printf("trim: %s", result);
	free(result);
    return (0);
}*/

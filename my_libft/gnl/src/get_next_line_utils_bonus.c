/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:05:24 by mtice             #+#    #+#             */
/*   Updated: 2025/03/12 15:05:35 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void		*ft_memmove2(void *dest, const void *src, size_t n);
char		*ft_trim(const char *s, char set);
static char	*find_cat(char const *s1, char const *s2, char *cat);
char		*ft_strjoin2(char const *s1, char const *s2);

void	*ft_memmove2(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (src == NULL && dest == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	s = (char *)src;
	d = (char *)dest;
	i = 0;
	if (d < s || d >= s + n)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}

static char	*mini_trim(char set)
{
	char	*trim;

	trim = (char *)malloc(2 * sizeof(char));
	if (trim == NULL)
		return (NULL);
	trim[0] = set;
	trim[1] = '\0';
	return (trim);
}

char	*ft_trim(const char *s, char set)
{
	int		i;
	int		j;
	char	*trim;

	i = 0;
	j = 0;
	if (s[0] == set)
	{
		trim = mini_trim(set);
		return (free(mini_trim(set)), trim);
	}
	while (s[i] != set)
		i++;
	i++;
	trim = (char *)malloc((i + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	while (j < i)
	{
		trim[j] = s[j];
		j++;
	}
	trim[j] = '\0';
	return (trim);
}

static char	*find_cat(char const *s1, char const *s2, char *cat)
{
	unsigned int	i;
	unsigned int	j;

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

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char			*cat;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		cat = (char *)malloc((ft_stringlen(s2) + 1));
	else
		cat = (char *)malloc((ft_stringlen(s1) + ft_stringlen(s2) + 1));
	if (cat == NULL)
		return (NULL);
	cat = find_cat(s1, s2, cat);
	free((void *)s1);
	return (cat);
}

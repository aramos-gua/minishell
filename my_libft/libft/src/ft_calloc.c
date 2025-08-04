/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:47:05 by mtice             #+#    #+#             */
/*   Updated: 2024/12/05 17:30:29 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	p = malloc(size * nmemb);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, (nmemb * size));
	return (p);
}
/*
int	main(void)
{
	int	i;
	char	*arr = "Apples";

	i = 0;
	arr = (char *)ft_calloc(10, 0);
	if (arr == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	while (i < 10)
	{	
		printf("%d", arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:35:49 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 15:36:55 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//subsitutes char sub by char r (replace) in string s
void	sub_char(char *s, char sub, char r)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == sub)
			s[i] = r;
		i++;
	}
}

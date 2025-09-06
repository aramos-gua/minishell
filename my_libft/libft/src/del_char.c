/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:31:07 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 15:35:31 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
//deletes a char at position pos from a string s
void	del_char(char *s, int pos)
{
	int	i;
	int	new;
	
	i = 0;
	if (pos >= ft_strlen(s))
		return ;
	while (s[i] != '\0')
	{
		if (i == pos)
		{
			new = i;
			while (s[new] != '\0')
			{
				s[new] = s[new + 1];
				new++;
			}
			return ;
		}
		else
			i++;
	}
}
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char s[]= "hiiii'|'";
//
// 	printf("old: %s\n", s);
// 	printf("old_len: %ld\n", strlen(s));
// 	del_char(s, 10);
// 	//del_char(s, 6);
// 	printf("new: %s\n", s);
// 	printf("new_len: %ld\n", strlen(s));
// 	return (0);
// }

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
//deletes char d from a string s
void	del_char(char *s, char d)
{
	int		i;
	int		new;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
		{
			new = i;
			while (s[new] != '\0')
			{
				s[new] = s[new + 1];
				new++;
			}
		}
		else
			i++;
	}
}
// int main(void)
// {
// 	char s[]= "hiiii'|'";
//
// 	printf("old: %s\n", s);
// 	printf("old_len: %ld\n", strlen(s));
// 	del_char(s, '\'');
// 	printf("new: %s\n", s);
// 	printf("new_len: %ld\n", strlen(s));
// 	return (0);
// }

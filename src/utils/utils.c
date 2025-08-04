/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:05:24 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 20:11:01 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//returns a non-zero value if the string is a builtin
//returns zero if not
int	is_builtin(char *s)
{
	if (!ft_strncmp("echo\0", s, 5))
		return (1);
	else if (!ft_strncmp("cd\0", s, 3))
		return (2);
	else if (!ft_strncmp("pwd\0", s, 4))
		return (3);
	else if (!ft_strncmp("export\0", s, 7))
		return (4);
	else if (!ft_strncmp("unset\0", s, 6))
		return (5);
	else if (!ft_strncmp("env\0", s, 4))
		return (6);
	else if (!ft_strncmp("exit\0", s, 5))
		return (7);
	else
		return (0);
}

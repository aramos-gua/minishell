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

int	is_shell_var(char *s)
{
	if (!ft_strncmp("ENV\0", s, 4))
		return (1);
	else if (!ft_strncmp("HOME\0", s, 5))
		return (2);
	else if (!ft_strncmp("IFS\0", s, 4))
		return (3);
	else if (!ft_strncmp("LANG\0", s, 5))
		return (4);
	else if (!ft_strncmp("LC_ALL\0", s, 7))
		return (5);
	else if (!ft_strncmp("LC_COLLATE\0", s, 11))
		return (6);
	else if (!ft_strncmp("LC_CTYPE\0", s, 9))
		return (7);
	else if (!ft_strncmp("LC_MESSAGES\0", s, 12))
		return (8);
	else if (!ft_strncmp("LINENO\0", s, 7))
		return (9);
	else if (!ft_strncmp("NLSPATH\0", s, 8))
		return (10);
	else if (!ft_strncmp("PATH\0", s, 5))
		return (11);
	else if (!ft_strncmp("PPID\0", s, 5))
		return (12);
	else if (!ft_strncmp("PS1\0", s, 4))
		return (13);
	else if (!ft_strncmp("PS2\0", s, 4))
		return (14);
	else if (!ft_strncmp("PS4\0", s, 4))
		return (15);
	else if (!ft_strncmp("PWD\0", s, 4))
		return (16);
	else
		return (0);
}

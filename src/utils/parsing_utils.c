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

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//returns 1 if a string has a whitespace character
//akin to ft_strchr(char *s, ft_isspace(char c) == 1)
int	has_whitespace(char *s)
{
	if (ft_strchr(s, ' ') || ft_strchr(s, '\t')
		|| ft_strchr(s, '\n') || ft_strchr(s, '\v')
		|| ft_strchr(s, '\f') || ft_strchr(s, '\r'))
		return (1);
	else
		return (0);
}

char	*find_command(t_data *all, int process_nbr)
{
	t_token	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		if (temp->process_nbr == process_nbr && temp->type == COMMAND)
			return (temp->token);
		temp = temp->next;
	}
	return (NULL);
}

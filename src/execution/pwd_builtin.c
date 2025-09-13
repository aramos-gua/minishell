/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:00:37 by aramos            #+#    #+#             */
/*   Updated: 2025/09/13 20:06:01 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if argument contains something other than L or P when arg[0] == '-'
static	int	not_only_lps(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'L' && str[i] != 'P')
			return (1);
		i++;
	}
	return (0);
}

//checks if the argument passed to pwd is valid
static	int	not_good_arg(t_data *all, t_token *cmd)
{
	char	*arg;

	arg = cmd->next->token;
	if (arg && arg[0] == '-')
	{
		if (ft_strlen(arg) > 2)
		{
			if (not_only_lps(arg))
				return (all->return_val = 1, 1);
		}
		else if (ft_strlen(arg) == 2)
		{
			if (ft_strncmp(arg, "--\0", 3))
			{
				all->return_val = 1;
				return (1);
			}
		}
		return (0);
	}
	return (0);
}

//replicates pwd behavior. Prints Working Directory
int	ft_pwd(t_data *all, t_token *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (all->return_val = 1);
	if (cmd->next != cmd && not_good_arg(all, cmd))
	{
		ft_dprintf(2, "minishell: pwd %s: %s\n", cmd->next->token, INV_OPT);
		ft_dprintf(2, "pwd: usage: pwd [-LP]\n");
		return (all->return_val = 2);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", pwd);
	free(pwd);
	return (all->return_val = 0);
}

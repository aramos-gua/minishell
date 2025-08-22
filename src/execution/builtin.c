/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:42:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/21 12:41:59 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(char *cmd)
{
	char	*pwd;

	dprintf(2, "running [%s]\n", cmd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		dprintf(2, "Error with pwd\n");
	dprintf(2, "%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_cd(char *cmd, t_data *all)
{
	t_token	*cd_node;

	dprintf(2, "running [%s]\n", cmd);
	cd_node = all->tokens->next;
	dprintf(2, "token in node is [%s]\n", cd_node->token);
	while (ft_strncmp(cd_node->token, "cd", 2))
		cd_node = cd_node->next;
	chdir((const char *)cd_node->next->token);
	return (0);
}

int	which_builtin(char *cmd, t_data *all)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
	{
		dprintf(2, "builtin [%s] not implemented\n", cmd);
		return (0);
	}
	else if (!ft_strncmp(cmd, "cd", len))
	{
		//dprintf(2, "builtin [%s] not implemented\n", cmd);
		ft_cd(cmd, all);
		return (1);

	}
	else if (!ft_strncmp(cmd, "pwd", len))
	{
		//dprintf(2, "starting ft_pwd\n");
		ft_pwd(cmd);
		return (1);

	}
	else if (ft_strncmp(cmd, "export", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (0);

	}
	else if (ft_strncmp(cmd, "unset", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (0);

	}
	else if (ft_strncmp(cmd, "env", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (0);

	}
	else if (ft_strncmp(cmd, "exit", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (0);

	}
	return (0);
}

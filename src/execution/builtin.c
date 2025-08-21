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

void	ft_pwd(void)
{
	char	*pwd;

	ft_printf("starting ft_pwd\n");
	pwd = getcwd(NULL, 0);
	dprintf(2, "%s\n", pwd);
	free(pwd);
	//return (0);
}

int	which_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "echo", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (1);
	}
	if (ft_strncmp(cmd, "cd", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		
		return (1);

	}
	if (ft_strncmp(cmd, "pwd", len))
	{
		ft_pwd();
		dprintf(2, "builtin [%s]\n", cmd);
		//return (1);

	}
	if (ft_strncmp(cmd, "export", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (1);

	}
	if (ft_strncmp(cmd, "unset", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (1);

	}
	if (ft_strncmp(cmd, "env", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (1);

	}
	if (ft_strncmp(cmd, "exit", len))
	{
		dprintf(2, "builtin [%s]\n", cmd);
		return (1);

	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:57 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/23 18:10:56 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_path_set(t_data *all)
{
	int	j;

	j = 0;
	while (all->c_envp[j] != NULL && ft_strncmp("PATH=", all->c_envp[j], 5))
		j++;
	if (all->c_envp[j] == NULL)
		return (0);
	return (1);
}

int	command_not_found(t_data *all, t_token *cmd)
{
	all->return_val = 127;
	if (!is_path_set(all))
	{
		(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(cmd->token, 2));
		(ft_putstr_fd(": ", 2), ft_putendl_fd(NO_FILE_OR_D, 2));
	}
	else if (!cmd->token || !ft_strncmp("\0", cmd->token, 1))
		ft_dprintf(STDERR_FILENO, "'': command not found\n");
	else if (errno == EACCES || errno == ENOEXEC)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->token);
		ft_return_val(all, errno);
	}
	else
		(ft_putstr_fd(cmd->token, 2), ft_putendl_fd(": command not found", 2));
	return (all->return_val);
}

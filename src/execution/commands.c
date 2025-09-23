/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/23 18:19:09 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_command(t_data *all, int i, int piped)
{
	t_token	*cmd;
	char	*path;
	int		fds_bak[2];
	int		pid;
	int		nodes;

	nodes = ft_lstsize(all->tokens, i);
	cmd = get_process(all->tokens, i);
	if (!cmd)
	{
		if (!piped)
			return (0);
		if (all->c_envp)
		free_double_char(all->c_envp);
		if (all->c_exp)
		free_double_char(all->c_exp);
		free_all(all);
		exit (0);
	}
	if (is_builtin(cmd->token))
	{
		if (!ft_strncmp(cmd->token, "exit", 5))
			ft_exit(all, nodes, cmd, 1);
		fds_bak[0] = dup(STDIN_FILENO);
		fds_bak[1] = dup(STDOUT_FILENO);
		if (get_fd(all, i))
			return (all->return_val = 1, 1);
		which_builtin(cmd->token, all, i);
		dup2(fds_bak[0], STDIN_FILENO);
		dup2(fds_bak[1], STDOUT_FILENO);
		close(fds_bak[0]);
		close(fds_bak[1]);
		if (!piped)
			return (0);
		if (all->c_envp)
		free_double_char(all->c_envp);
		if (all->c_exp)
		free_double_char(all->c_exp);
		free_all(all);
		exit (0);
	}
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!cmd->token || cmd->token[0] == '\0' || !path)
	{
		// dprintf(2, "get_cmd_path not found\n");
		return (all->return_val = 127, command_not_found(all, cmd));
	}
	array_builder(all, i);
	if (!piped)
	{
		pid = fork();
		if (pid == 0)
		{
			if (get_fd(all, i))
				return (free(path), all->return_val = 1, 1);
			default_sigquit();
			if (execve(path, all->arr, all->c_envp) == -1)
			{
				perror("minishell: \n");
				free(path);
				ft_return_val(all, errno);
				return (ft_exit(all, nodes, cmd, 0));
			}
		}
		else
			waitpid(all->info[i].pid, NULL, 0);
	}
	else
	{
		if (get_fd(all, i))
			return (free(path), all->return_val = 1, 1);
		// dprintf(2, "comming till here\n");
		default_sigquit();
		if (execve(path, all->arr, all->c_envp) == -1)
		{
			perror("minishell: \n");
			free(path);
			ft_return_val(all, errno);
			return (ft_exit(all, nodes, cmd, 0));
		}
	}
	free(path);
	return (0);
}

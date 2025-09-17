/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/13 18:32:38 by aramos           ###   ########.fr       */
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

	// dprintf(2, "starting execute command\n");
	nodes = ft_lstsize(all->tokens, i);
	cmd = get_process(all->tokens, i);
	if (!cmd)
		write(2, "exited after cmd\n", 17);
	if (is_builtin(cmd->token))
	{
		fds_bak[0] = dup(STDIN_FILENO);
		fds_bak[1] = dup(STDOUT_FILENO);
		if (!ft_strncmp(cmd->token, "exit\0", 5) && cmd->next == cmd)
			return (ft_exit(all, nodes, cmd, fds_bak));
		if (get_fd(all, i))
			return (all->return_val = 1, 1);
		which_builtin(cmd->token, all, i);
		dup2(fds_bak[0], STDIN_FILENO);
		dup2(fds_bak[1], STDOUT_FILENO);
		close(fds_bak[0]);
		close(fds_bak[1]);
		if (piped)
			exit(0);
		return (0);
	}
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!path)
		return (command_not_found(all, cmd));
	// dprintf(2, "starting array builder\n");
	array_builder(all, i);
	// dprintf(2, "after array builder\n");
	// int c = 0;
	// while (all->arr)
	// {
	// 	dprintf(2, "item[%d]-> %s\n", c, all->arr[c]);
	// }
	if (!piped)
	{
		pid = fork();
		if (pid == 0)
		{
			if (get_fd(all, i))
				return (all->return_val = 1, 1);
			// dprintf(2, "comming till here 1\n");
			if (execve(path, all->arr, all->c_envp) == -1)
			{
				perror("minishell: execve\n");
				free(path);
				all->return_val = 1;
				return (ft_exit(all, nodes, cmd, fds_bak));
			}
		}
		else
			waitpid(all->info[i].pid, NULL, 0);
	}
	else
	{
		if (get_fd(all, i))
			return (all->return_val = 1, 1);
		// dprintf(2, "comming till here\n");
		if (execve(path, all->arr, all->c_envp) == -1)
		{
			perror("minishell: execve\n");
			free(path);
			all->return_val = 1;
			return (ft_exit(all, nodes, cmd, fds_bak));
		}
	}
	free(path);
	return (0);
}

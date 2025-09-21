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
	t_proc	*current;

	current = all->info;
	nodes = ft_lstsize(all->tokens, i);
	cmd = get_process(all->tokens, i);
	if (!cmd)
	{
		while (current->process_nbr != i)
			current = current->next;
		dprintf(2, "fd_in [%d] fd_out [%d]\n", current->in_fd, current->out_fd);
		if (current->in_fd != STDIN_FILENO)
			close(current->in_fd);
		if (current->out_fd != STDOUT_FILENO)
			close(current->out_fd);
		if (!piped)
			return (0);
		exit (0);
	}
	if (is_builtin(cmd->token))
	{
		if (!ft_strncmp(cmd->token, "exit", 5))
			ft_exit(all, nodes, cmd);
		fds_bak[0] = dup(STDIN_FILENO);
		fds_bak[1] = dup(STDOUT_FILENO);
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
	array_builder(all, i);
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
				return (ft_exit(all, nodes, cmd));
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
			return (ft_exit(all, nodes, cmd));
		}
	}
	free(path);
	return (0);
}

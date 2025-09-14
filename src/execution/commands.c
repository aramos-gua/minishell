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

#include "../inc/minishell.h"

int	execute_command(t_data *all, int i, int piped)
{
	t_token	*cmd;
	char	*path;
	// char	**cmd_arr;
	int		fds_bak[2];
	int		pid;

	cmd = get_process(all->tokens, i);
	dprintf(2, "cmd for proc[%d] is [%s]\n", i, cmd->token);
	if (!cmd)
		write(2, "exited after cmd\n", 17);
	if (is_builtin(cmd->token))
	{
		fds_bak[0] = dup(STDIN_FILENO);
		fds_bak[1] = dup(STDOUT_FILENO);
		if (!ft_strncmp(cmd->token, "exit\0", 5))
		{
			dprintf(2, "about to call which_builtin\n");
			which_builtin(cmd->token, all, i, fds_bak);
			restore(all, fds_bak);
		}
		dprintf(2, "redirecting FDs\n");
		// redirect_fds(all, i);
		get_fd(all, i, 0);
		get_fd(all, i, 1);
		dprintf(2, "about to call which_builtin\n");
		which_builtin(cmd->token, all, i, fds_bak);
		dprintf(2, "\nrestoring FDs\n");
		dup2(fds_bak[0], STDIN_FILENO);
		dup2(fds_bak[1], STDOUT_FILENO);
		close(fds_bak[0]);
		close(fds_bak[1]);
		if (piped)
			exit(0);
		return (0);
	}
	path = get_cmd_path(cmd->token, all->c_envp);
	dprintf(2, "path is [%s]\n", path);
	if (!path)
		return (command_not_found(all, cmd));
	array_builder(all, i);
	if (!piped)
	{
		dprintf(2, "not piped\n");
		pid = fork();
		if (pid == 0)
		{
			get_fd(all, i, 0);
			get_fd(all, i, 1);
			if (execve(path, all->arr, all->c_envp) == -1)
			{
				ft_printf("exited after execve\n");
				free(path);
				exit (1);
			}
		}
		else
			waitpid(all->info[i].pid, NULL, 0);
	}
	else
	{
		dprintf(2, "piped\n");
		get_fd(all, i, 0);
		get_fd(all, i, 1);
		if (execve(path, all->arr, all->c_envp) == -1)
		{
			ft_printf("exited after execve\n");
			free(path);
			exit (1);
		}
	}
	free(path);
	return (0);
}

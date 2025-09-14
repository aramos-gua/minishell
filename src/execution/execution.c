/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/14 21:44:19 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_fd(t_data *all, int proc, bool out)
{
	t_proc	*current;
	int		fd;

	if (!all->info)
		return (-1);
	current = all->info;
	while (current->process_nbr != proc)
		current = current->next;
	if (out == 0)
		fd = current->in_fd;
	else
		fd = current->out_fd;
	if (fd > 2 && !out)
	{
		dup2(fd, STDIN_FILENO);
		all->info->rev_fds = 1;
	}
	else if (fd > 2 && out)
	{
		dup2(fd, STDOUT_FILENO);
		all->info->rev_fds = 1;
	}
	return (0);
}

int	get_pipe(int *pipes, int flag)
{
	if (flag == 0)
	{
		if (dup2(pipes[flag], STDIN_FILENO) == -1)
			dprintf(2, "error get_pipe\n");
	}
	else if (flag == 1)
	{
		if (dup2(pipes[flag], STDOUT_FILENO) == -1)
			dprintf(2, "error get_pipe\n");
	}
	close(pipes[0]);
	close(pipes[1]);
	return (0);
}

int	executron(t_data *all, int i)
{
	int	pipe_fds[2];
	int	first_fork_pid;
	int	second_fork_pid;

	pipe(pipe_fds);
	first_fork_pid = fork();
	if (first_fork_pid == 0)
	{
		get_pipe(pipe_fds, 1);
		execution(all, i, 1, 1);
	}
	else
	{
		second_fork_pid = fork();
		if (second_fork_pid == 0)
		{
			get_pipe(pipe_fds, 0);
			execution(all, i + 1, 1, 0);
		}
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}
	}
	waitpid(first_fork_pid, NULL, 0);
	waitpid(second_fork_pid, NULL, 0);
	return (0);
}

int	execution(t_data *all, int i, int piped, bool run)
{
	set_signals_noninteractive();
	ft_dprintf(2, "----------EXECUTION-----------------\n");
	if (i + 1 == all->info->total_proc || run)
		execute_command(all, i, piped);
	else
		executron(all, i);
	if (g_signal != SA_RESTART)
		write(1, "\n", 1);
	return (0);
}

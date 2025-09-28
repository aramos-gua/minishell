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

//gets the node corresponding to each process and redirects the stdin/stdout
//if there is an fd different than the macros assigned by default
int	get_fd(t_data *all, int proc)
{
	t_proc	*current;
	int		fd_in;
	int		fd_out;

	if (!all->info)
		return (-1);
	current = all->info;
	while (current->process_nbr != proc)
		current = current->next;
	fd_in = current->in_fd;
	fd_out = current->out_fd;
	if (fd_in != STDIN_FILENO)
	{
		if (fd_in > 0)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
			return (all->info->rev_fds = 1, 0);
		}
		return (all->return_val = 1, 1);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (fd_out > 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			return (all->info->rev_fds = 1, 0);
		}
		return (all->return_val = 1, 1);
	}
	return (0);
}

//redirects input and output to the pipe per process
static int	get_pipe(t_data *all, int *pipes, int flag)
{
	if (flag == 0)
	{
		if (dup2(pipes[flag], STDIN_FILENO) == -1)
			return (all->return_val = 1, perror("dup2 pipe"), 1);
	}
	else if (flag == 1)
	{
		if (dup2(pipes[flag], STDOUT_FILENO) == -1)
			return (all->return_val = 1, perror("dup2 pipe"), 1);
	}
	close(pipes[0]);
	close(pipes[1]);
	return (0);
}

//forks and calls execution recursively until last command is reached
static int	executron(t_data *all, int i)
{
	int	pipe_fds[2];
	int	first_fork_pid;
	int	second_fork_pid;
	int	status;
	int	status2;

	status = 0;
	status2 = 0;
	pipe(pipe_fds);
	first_fork_pid = fork();
	if (first_fork_pid == 0)
		(get_pipe(all, pipe_fds, 1), execution(all, i, 1, 1));
	else
	{
		second_fork_pid = fork();
		if (second_fork_pid == 0)
			(get_pipe(all, pipe_fds, 0), execution(all, i + 1, 1, 0));
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
		}
	}
	waitpid(first_fork_pid, &status, 0);
	if (WIFEXITED(status))
		all->return_val = WEXITSTATUS(status);
	waitpid(second_fork_pid, &status2, 0);
	if (WIFEXITED(status2))
		all->return_val = WEXITSTATUS(status2);
	return (0);
}

int	execution(t_data *all, int i, int piped, bool run)
{
	int	return_val;
	// dprintf(2, "executing now\n");
	set_signals_noninteractive(all);
	if (i + 1 == all->info->total_proc || run)
	{
		return_val = (execute_command(all, i, piped));
		if (return_val == 0)
		{
			if (all->return_val != 0)
			{
				if (all->c_envp)
				free_double_char(all->c_envp);
				if (all->c_exp)
				free_double_char(all->c_exp);
				free_all(all);
				exit (all->return_val);
			}
		}
		if (return_val == 1)
		{
			if (all->return_val != 0)
			{
				if (!piped)
					return (0);
				if (all->c_envp)
				free_double_char(all->c_envp);
				if (all->c_exp)
				free_double_char(all->c_exp);
				free_all(all);
				exit (all->return_val);
			}

		}
	}
	else
		executron(all, i);
	return (0);
}

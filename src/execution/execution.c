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
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		all->info->rev_fds = 1;
	}
	else if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		all->info->rev_fds = 1;
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
	waitpid(first_fork_pid, NULL, 0);
	waitpid(second_fork_pid, NULL, 0);
	return (0);
}

int	only_ops(t_data *all, int proc)
{
	t_token	*list_tail;
	t_token	*list_head;
	int		command_flag;

	command_flag = proc;
	list_tail = all->tokens;
	list_head = list_tail->next;
	if (list_head == list_tail)
	{
		if (list_head->type == COMMAND)
			return (-1);
		else if (list_head->type == APPEND || list_head->type == RE_IN || list_head->type == RE_OUT)
			return (proc);
	}
	while (list_head->process_nbr != proc)
		list_head = list_head->next;
	while (list_head->process_nbr == proc && list_head != list_tail)
	{
		if (list_head->type == COMMAND)
			return (command_flag = -1, command_flag);
		list_head = list_head->next;
	}
	return (command_flag);
}

int	execution(t_data *all, int i, int piped, bool run)
{
	if (only_ops(all,i) != -1)
		all->info->which_hangs = (only_ops(all, i));
	else
		all->info->which_hangs = -1;
	set_signals_noninteractive();
	if (i + 1 == all->info->total_proc || run)
	{
		dprintf(2, "executing now\n");
		if (all->info->which_hangs == i)
		{
			if (i == 0 && all->total_proc == 1)
				return (1);
			exit(1);
		}
		execute_command(all, i, piped);
	}
	else
	{
		if (only_ops(all, i))
			all->info->which_hangs = i;
		executron(all, i);
	}
	if (g_signal == SIGQUIT)
		all->return_val = 131;
	return (0);
}

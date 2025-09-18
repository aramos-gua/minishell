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
			// return (all->info->rev_fds = 1, 0);
		}
		else
		{
			// dup2(all->info->bak[0], STDIN_FILENO);
			return (all->return_val = 1, 1);
		}
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (fd_out > 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			// return (all->info->rev_fds = 1, 0);
		}
		else
		{
			// if (all->info->rev_fds == 1)
			// 	dup2(all->info->bak[1], STDOUT_FILENO);
			return (all->return_val = 1, 1);
		}
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

int	 only_ops(t_data *all, int proc)
{
	t_token *temp;

	temp = all->tokens->next;
	if (all->tokens == all->tokens->next)
	{
		if (temp->type == COMMAND)
			return (-1);
		else if (temp->type == APPEND || temp->type == RE_IN || temp->type == RE_OUT)
			return (proc);
	}
	while (temp->process_nbr != proc)
		temp = temp->next;
	while (temp->process_nbr == proc && temp != all->tokens)
	{
		if (temp->type == COMMAND)
			return (-1);
		temp = temp->next;
	}
	if (temp->type == COMMAND)
		return (-1);
	return (proc);
}

int	close_fd(t_data *all, int proc, bool out)
{
	t_proc *node;

	node = all->info;
	while (all->info->process_nbr != proc)
		node = node->next;
	if (!out && node->in_fd != -1 && node->in_fd > 2)
		return(node->in_fd);
	if (out && node->out_fd != -1 && node->out_fd > 2)
		return(node->out_fd);
	return (-1) ;
}

int	execution(t_data *all, int i, int piped, bool run)
{
	all->info->which_hangs = (only_ops(all, i));
	set_signals_noninteractive();
	if (i + 1 == all->info->total_proc || run)
	{
		// dprintf(2, "executing now\n");
		if (all->info->which_hangs == i)
		{
			if (all->total_proc == i + 1)
				return (1);
			else
			{
				close(close_fd(all, i, 0));
				close(close_fd(all, i, 1));
				exit(1);
			}
		}
		if (execute_command(all, i, piped))
			return (all->return_val = 1, 1);
	}
	else
		executron(all, i);
	return (1);
}

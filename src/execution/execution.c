/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/21 12:02:04 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fd(t_data *all, int proc, bool out)
{
	t_proc	*current;
	int		fd;

  dprintf(2, "Starting get_fd\n");
  dprintf(2, "current proc: [%d]\n", proc);
	if (!all->info)
		return (-1);
	current = all->info;
	while (current->process_nbr != proc)
  {
    dprintf(2, "current proc: [%d]\n", current->process_nbr);
		current = current->next;
  }
  dprintf(2, "current [%d] -> proc [%d] \n", current->process_nbr, proc);
	if (out == 0)
		fd = current->in_fd;
  else
		fd = current->out_fd;
	if (fd > 2 && !out)
	{
		dup2(fd, STDIN_FILENO);
	}
  else if (fd > 2 && out)
	{
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

int get_pipe(int *pipes, int flag)
{
  if (flag == 0)
    dup2(pipes[flag], STDIN_FILENO);
  if (flag == 1)
    dup2(pipes[flag], STDOUT_FILENO);
  close(pipes[0]);
  close(pipes[1]);
}

int  executron(t_data *all, int i)
{
  int pipe_fds[2];
  int first_fork_pid;
  int second_fork_pid;

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
	ft_printf("\n----------EXECUTION---------\n");
//////////////////////////////////////////////////////////////////////////////////
///	int		curr_proc;
///	t_token	*tail;
///	t_token	*current;
///	tail = all->tokens;
///	current = tail->next;
///	curr_proc = current->process_nbr;
///  dprintf(2, "fd_in -> [%d] -> fd_out ->[%d]\n", all->info->in_fd, all->info->out_fd);
///	while (1)
///	{
///		if (current->process_nbr != curr_proc)
///			curr_proc = current->next->process_nbr;
///		if (current->type == COMMAND || current->builtin)
///		{
///			ft_printf("[%d], command: %s   ", curr_proc, current->token);
///		}
///		else if (current->type == ARGUMENT)
///		{
///			ft_printf(" arg: %s ", current->token);
///		}
///		if (current == tail)
///			break ;
///		current = current->next;
///	}
///	ft_printf("\n\n");
/////////////////////////////////////////////////////////////////////////////////////
  //dup2(all->info->in_fd, STDIN_FILENO);
  //dup2(all->info->out_fd, STDOUT_FILENO);
	if (i + 1 == all->info->total_proc || run)
		execute_command(all, i, piped);
	else
		executron(all, i);
	return (0);
}

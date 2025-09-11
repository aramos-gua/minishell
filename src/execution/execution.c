/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 20:17:40 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

// void  pipe_n_run(t_data *all, int i, int *pipes, int out)
// {
//   if (out)
//   {
//     get_pipe(pipes, out),
//     execution(all, i, 1, 1);
//   }
//   else
//   {
//     get_pipe(pipes, out),
//     execution(all, i + 1, 1, 0);
//   }
// }

int  executron(t_data *all, int i)
{
  int pipe_fds[2];
  int first_fork_pid;
  // int second_fork_pid;

  pipe(pipe_fds);
  first_fork_pid = fork();
  if (first_fork_pid == 0)
  {
     get_pipe(pipe_fds, 1);
     execution(all, i, 1, 1);
    // pipe_n_run(all, i, pipe_fds, 0);
  }
	else
	{
    first_fork_pid = fork();
    if (first_fork_pid == 0)
    {
         get_pipe(pipe_fds, 0);
         execution(all, i + 1, 1, 0);
        // pipe_n_run(all, i, pipe_fds, 0);
    }
    else
    {
      close(pipe_fds[0]);
      close(pipe_fds[1]);
    }
	}
	waitpid(first_fork_pid, NULL, 0);
  // waitpid(second_fork_pid, NULL, 0);
	return (0);
}

int	execution(t_data *all, int i, int piped, bool run)
{
  if (i == 0)
    ft_dprintf(2, "----------EXECUTION-----------------\n");
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

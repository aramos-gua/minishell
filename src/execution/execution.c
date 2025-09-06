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

int get_fd(t_proc *list, int proc, bool in)
{
  t_proc  *current;
  int     fd;

  if (!list)
    return (-1);
  current = list;
  while (current->process_nbr != proc)
    current = current->next;
  if (in)
    return (fd = current->in_fd);
  return (fd = current->out_fd);

}

int  executron(t_data *all, int i)
{
  int pipe_fds[2];
  int first_fork_pid;
  int second_fork_pid;

  if (all->total_proc > 1)
  {
    int new_out;
    int new_in;

    pipe(pipe_fds);
    new_in = get_fd(all->info, i, 1);
    new_out = get_fd(all->info, i, 0);
    dup2(new_in, pipe_fds[0]);
    dup2(new_out, pipe_fds[1]);
    close(new_in);
    close(new_out);
    dprintf(2, "pipes[0] fd:[%d] -> ", pipe_fds[0]);
    dprintf(2, "pipe[1] fd:[%d]\n", pipe_fds[1]);
  }
  first_fork_pid = fork();
  if (first_fork_pid == 0)
  {
    dup2(pipe_fds[0], STDIN_FILENO);
    dup2(pipe_fds[1], STDOUT_FILENO);
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    execute_command(all, i);
    return (0);
  }
  else
  {
    second_fork_pid = fork();
    if (second_fork_pid == 0)
    {
      dup2(pipe_fds[0], STDIN_FILENO);
      dup2(pipe_fds[1], STDOUT_FILENO);
      close(pipe_fds[0]);
      close(pipe_fds[1]);
      int j = i + 1;
      if (j < all->total_proc - 1)
        executron(all, j);
      else
      {
        execute_command(all, j);
      }
    }
    else
    {
      close(pipe_fds[0]);
      close(pipe_fds[1]);
      int l = 0;
      while (l++ < all->total_proc)
        waitpid(-1, NULL, 0);
      return (0);
    }
  }
  return (0);
}
int	one_command(t_data *all)
{
  t_token *cmd;

  cmd = get_process(all->tokens, 0);
  dprintf(2, "one_command cmd is [%s]\n", cmd->token);
  if (which_builtin(cmd->token, all, 0) == 1)
  {
    //handle_builtin(all, i);
    return (0);
  }
  all->info->pid = fork();
  if (all->info->pid == 0)//child
  {
    (execute_command(all, 0));
    
  }
  //parent
  else if (all->info->pid > 0)
    waitpid(all->info->pid, NULL, 0);
  else
    perror("minishell");
	return (0);
}

int	execution(t_data *all)
{
	//int	pipes[2];

  //all->info->in_fd = 0;
  //all->info->out_fd = 1;
	ft_printf("\nStarting exec\n");
	ft_printf("\n----------EXECUTION---------\n");
///////////////////////////////////////////////////////////////////////////////
	int		curr_proc;
	t_token	*tail;
	t_token	*current;
	tail = all->tokens;
	current = tail->next;
	curr_proc = current->process_nbr;
  dprintf(2, "fd_in -> [%d] -> fd_out ->[%d]\n", all->info->in_fd, all->info->out_fd);
	while (1)
	{
		if (current->process_nbr != curr_proc)
			curr_proc = current->next->process_nbr;
		if (current->type == COMMAND || current->builtin)
		{
			ft_printf("[%d], command: %s   ", curr_proc, current->token);
		}
		else if (current->type == ARGUMENT)
		{
			ft_printf(" arg: %s ", current->token);
		}
		if (current == tail)
			break ;
		current = current->next;
	}
	ft_printf("\n\n");
//////////////////////////////////////////////////////////////////////////////////
  //dup2(all->info->in_fd, STDIN_FILENO);
  //dup2(all->info->out_fd, STDOUT_FILENO);
	if (all->info->total_proc == 1)
		one_command(all);
  else if (all->info->total_proc > 1)
	{
    executron(all, 0);
    if (all->info->in_fd != 0)
      close(all->info->in_fd);
    if (all->info->out_fd != 1)
    {
      close(all->info->in_fd);
      close(all->info->out_fd);
    }
  }
	return (0);
}

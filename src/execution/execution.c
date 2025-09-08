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

// void	close_fds(t_data *all, int i)
// {
// 	int j = 0;
// 	while (j < all->total_proc - 1)
// 	{
// 	t_proc	*delete_fd = all->info;
// 	if (j == i)
// 		j++;
// 	while (delete_fd->process_nbr != j)
// 		delete_fd = delete_fd->next;
// 	if (delete_fd->in_fd > 2)
// 		close(delete_fd->in_fd);
// 	if (delete_fd->out_fd > 2)
// 		close(delete_fd->out_fd);
// 	j++;
// }

int	get_fd(t_data *all, int proc, bool out, int *pipes)
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
    close(pipes[0]);
		close(fd);
	}
	else if (fd > 2 && out)
	{
		dup2(fd, STDOUT_FILENO);
    close(pipes[1]);
		close(fd);
	}
	return (0);
}

int get_pipe(int *pipes)
{
  dup2(pipes[0], STDIN_FILENO);
  dup2(pipes[1], STDOUT_FILENO);
}

int  executron(t_data *all, int i)
{
  int pipe_fds[2];
  int first_fork_pid;
  int second_fork_pid;

  if (i < (all->total_proc - 1))
    pipe(pipe_fds);
  first_fork_pid = fork();
  if (first_fork_pid == 0)
  {
	//fist child
    if (all->info->in_fd != STDIN_FILENO)
      get_fd(all, i, 0, pipe_fds);
    else if (all->info->out_fd != STDOUT_FILENO)
      get_fd(all, i, 1, pipe_fds);
    else
    {
      get_pipe(pipe_fds);
    }
    execute_command(all, i);
    return (0);
  }
	else
	{
    //parent
    //close(pipe_fds[1]);
    second_fork_pid = fork();
    if (second_fork_pid == 0)
    {
      //child
      if (all->info->in_fd != STDIN_FILENO)
        get_fd(all, i, 0, pipe_fds);
      if (all->info->in_fd != STDOUT_FILENO)
        get_fd(all, i, 1, pipe_fds);
      else
      {
        get_pipe(pipe_fds);
      }
      int j = i + 1;
      if (j < all->total_proc - 1)
      {
        dprintf(2, "jamon\n");
        executron(all, j);
      }
      else
      {
        if (all->info->in_fd != STDIN_FILENO)
          get_fd(all, j, 0, pipe_fds);
        if (all->info->in_fd != STDOUT_FILENO)
          get_fd(all, j, 1, pipe_fds);
        else
        {
          get_pipe(pipe_fds);
        }
        execute_command(all, j);
      }
    }
    else
    {
      //parent
      close(pipe_fds[0]);
    }
	}
	waitpid(first_fork_pid, NULL, 0);
	if (i < all->total_proc - 1)
		waitpid(-1, NULL, 0);
	return (0);
}

int	one_command(t_data *all)
{
	t_token *cmd;

	cmd = get_process(all->tokens, 0);
	if (which_builtin(cmd->token, all, 0))
		return (0);
	all->info->pid = fork();
	if (all->info->pid == 0)//child
	{
		if (all->info->in_fd > 2)
		{
			dup2(all->info->in_fd, STDIN_FILENO);
			close(all->info->in_fd);
		}
		if (all->info->out_fd > 2)
		{
			dup2(all->info->out_fd, STDOUT_FILENO);
			close(all->info->out_fd);
		}
		execute_command(all, 0);
	}
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
    //if (all->info->in_fd != 0)
    //  close(all->info->in_fd);
    //if (all->info->out_fd != 1)
    //{
    //  close(all->info->in_fd);
    //  close(all->info->out_fd);
    //}
	}
	return (0);
}

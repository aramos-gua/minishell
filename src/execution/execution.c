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

int	child_process(int i, t_data *all, int *pipes)
{
	//int	j;

	//j = 0;
  dprintf(2, "process [%d] command [%d] out of [%d] commands\n", i, i +1, all->info->total_proc);
  if (i == 0)
    first_command(all, pipes);
  else if (i != 0 && i < (all->info->total_proc - 1))
  {
    dprintf(2, "middle command\n");
    dup2(pipes[0], STDIN_FILENO);
    //close(pipes[0]);
    dup2(pipes[1], STDOUT_FILENO);
    //close(pipes[1]);
  }
  if (i == (all->info->total_proc - 1))
    last_command(all, pipes);
  //else if (i != 0 && i < (all->info->total_proc - 1))
  //{
  //  dup2(pipes[1], STDOUT_FILENO);
  ////  dup2(pipes[1][1], STDOUT_FILENO);
  ////  close(pipes[1][1]);
  //}
	//while (j < (all->info->total_proc - 1))
	//{
	//	close(pipes[j][0]);
	//	close(pipes[j][1]);
  //  j++;
	//}
	if (execute_command(all, i) == 0)
    return (0);
  ft_printf("execute failed\n");
  return (1);
}

int	fork_init(t_data *all, int *pipes)
{
	int	  	i;
	t_token *token;

	i = 0;
	while (i < all->info->total_proc)
	{
		all->info->pid = fork();
		if (all->info->pid < 0)
		{
			sh_putstr("Error: Fork Failure\n", 2);
			exit(1);
		}
		if (all->info->pid == 0)
		{
      if (child_process(i, all, pipes))
        return (0);
      exit (1);
		}
    else
    {
      token = all->tokens;
      while (token->next->process_nbr != 0)
        token = token->next;
      all->info->last_pid = all->info->pid;
    }
		i++;
	}
  return (0);
}

void	open_pipes(int *pipes, t_data *all)
{
	int	i;

	//i = 0;
	//ft_printf("opening pipes\n");
	//while (i < all->info->total_proc - 1)
	//{
	//	if (pipe(pipes[i]) == -1)
	//	{
	//		ft_printf("Error: Pipes Failure\n");
	//		exit(1);
	//	}
	//	i++;
	//	ft_printf("%d pipe opened\n\n", i);
	//}
  if (pipe(pipes) == -1)
  {
    dprintf(2, "Error opening pipes\n");
    exit (1);
  }
	fork_init(all, pipes);
  close(pipes[0]);
  close(pipes[1]);
  //i = 0;
  //while (i < all->info->total_proc - 1)
  //{
  //  close(pipes[i][0]);
  //  close(pipes[i][1]);
  //  i++;
  //}
  i = 0;
  while (i < all->info->total_proc)
  {
    write(2, "waiting\n", 8);
    waitpid(-1, NULL, 0);
    i++;
  }
	//return (pipes);
}

int  executron(t_data *all, int i)
{
  int pipe_fds[2];
  int first_fork_pid;
  int second_fork_pid;

  if (all->total_proc > 1)
    pipe(pipe_fds);
  first_fork_pid = fork();
  if (first_fork_pid == 0)
  {
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
      close(pipe_fds[0]);
      close(pipe_fds[1]);
      int j = i + 1;
      if (j < all->total_proc - 1)
        executron(all, j);
      else
        execute_command(all, j);
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

//void  executron(t_data *all, int i)
//{
//  int pipe_fds[2];
//  int first_fork_pid;
//  int second_fork_pid;
//
//  if (all->total_proc > 1)
//    pipe(pipe_fds);
//  first_fork_pid = fork();
//  second_fork_pid = fork();
//  if (first_fork_pid == 0)
//  {
//    if (i == 0)
//      dup2(all->info->in_fd, STDIN_FILENO);
//    dup2(pipe_fds[1], STDOUT_FILENO);
//    close(pipe_fds[0]);
//    close(pipe_fds[1]);
//    execute_command(all, i);
//  }
//  else if (first_fork_pid > 0)
//  {
//    close(pipe_fds[0]);
//    close(pipe_fds[1]);
//    //int l = 0;
//    waitpid(first_fork_pid, NULL, 0);
//  }
//  if (second_fork_pid == 0)
//  {
//    if (i == all->total_proc)
//      dup2(all->info->out_fd, STDOUT_FILENO);
//    dup2(pipe_fds[0], STDIN_FILENO);
//    close(pipe_fds[0]);
//    close(pipe_fds[1]);
//    int j = i + 1;
//    if (j < all->total_proc - 1)
//      executron(all, j);
//    else
//    {
//      if (j == all->total_proc)
//      {
//        dup2(pipe_fds[1], all->info->out_fd);
//        close(pipe_fds[1]);
//      }
//      execute_command(all, j);
//    }
//  }
//  else if (second_fork_pid > 0)
//  {
//    //int l = 0;
//    waitpid(second_fork_pid, NULL, 0);
//  }
//  close(pipe_fds[0]);
//  close(pipe_fds[1]);
//}

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

  all->info->in_fd = 0;
//  all->info->out_fd = 1;
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
  dup2(all->info->in_fd, STDIN_FILENO);
  dup2(all->info->out_fd, STDOUT_FILENO);
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

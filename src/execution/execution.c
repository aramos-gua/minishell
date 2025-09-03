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

void  executron(t_data *all, int i, int in_fd)
{
  int pipe_fds[2];
  int first_fork_pid;
  int second_fork_pid;

  if (i == all->total_proc -1)
  {
    if (fork() == 0)
    {
      dup2(all->info->in_fd, STDIN_FILENO);
      close(all->info->in_fd);
      execute_command(all, i);
    }
    close(all->info->in_fd);
    wait(NULL);
    return ;
  }
  pipe(pipe_fds);
  if (fork() == 0)
  {
    dup2(all->info->in_fd, STDIN_FILENO);
    dup2(all->info->out_fd, STDOUT_FILENO);
    close(all->info->in_fd);
    close(all->info->in_fd);
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    execute_command(all, i);
  }
  close(all->info->in_fd);
  close(pipe_fds[1]);
  executron(all, i + 1, pipe_fds[0]);
  wait(NULL);
}

//void  executron(t_data *all, int i)
//{
//  int pipe_fds[2];
//  int first_fork_pid;
//  int second_fork_pid;
//
//  if (i < all->total_proc)
//    pipe(pipe_fds);
//  first_fork_pid = fork();
//  if (first_fork_pid == 0)
//  {
//    //TODO:Child process
//    dup2(pipe_fds[1], STDOUT_FILENO);
//    close(pipe_fds[0]);
//    close(pipe_fds[1]);
//    execute_command(all, i);
//  }
//  else
//  {
//    //TODO:Parent
//    second_fork_pid = fork();
//    if (second_fork_pid == 0)
//    {
//      //TODO:Second child
//      dup2(pipe_fds[0], STDIN_FILENO);
//      close(pipe_fds[0]);
//      close(pipe_fds[1]);
//      int j = i + 1;
//      if (j < all->total_proc)
//        executron(all, j);
//      else
//        execute_command(all, 0);
//    }
//    else
//    {
//      int k = 0;
//      close(pipe_fds[0]);
//      close(pipe_fds[1]);
//      //while (k < all->total_proc)
//      waitpid(-1, NULL, 0);
//    }
//  }
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
	int	pipes[2];

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
	if (all->info->total_proc == 1)
		one_command(all);
  else if (all->info->total_proc > 1)
	{
    executron(all, 0, all->info->in_fd);
  }
	return (0);
}

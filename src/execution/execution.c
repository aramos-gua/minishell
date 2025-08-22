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

int	child_process(int i, t_data *all, int **pipes)
{
	int	j;

	j = 0;
  if (i == 0)
    write(2, "starting child, [0]\n", 20);
  else if (i == 1)
    write(2, "starting child, [1]\n", 20);
  //if (all->info->in_fd != 0 || all->info->out_fd != 1)
  //{
    if (i == 0)
      first_command(all, pipes);
    else
    {
      dup2(pipes[i - 1][0], STDIN_FILENO);
    }
    if (i == all->info->total_proc - 1)
    {
      last_command(all, pipes);
    }
    else if (i < all->info->total_proc - 1)
      dup2(pipes[i][1], STDOUT_FILENO);
  //}
	while (j < all->info->total_proc - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
    j++;
	}
	//close(all->info->in_fd);
	//close(all->info->out_fd);
  write(2, "about to execute_command\n", 25);
	execute_command(all, i);
  ft_printf("execute failed\n");
  return (1);
}

int	pipes_init(int ***pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("starting pipes_init\n");
	ft_printf("total_proc = [%d]\n", all->info->total_proc);
	*pipes = malloc((all->info->total_proc - 1) * sizeof (int *));
	if (!*pipes)
		return (ft_printf("Error: Malloc Failure\n"), 1);
  else
    ft_printf("pipes pointer created\n");
	while (i < all->info->total_proc - 1)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!*pipes)
		{
			while (--i >= 0)
				free (*pipes[i]);
			free(*pipes);
			return (ft_printf("Error: Malloc Failure\n"), 1);
		}
		i++;
		ft_printf("%d pipe created\n", i);
	}
	return (0);
}

int	fork_init(t_data *all, int **pipes)
{
	int	  	i;
  //t_token  *cmd;
	//pid_t 	pid;
	t_token *token;

	i = 0;
	ft_printf("starting fork_init\n");
	while (i < all->info->total_proc)
	{
		all->info->pid = fork();
		if (all->info->pid < 0)
		{
			ft_printf("Error: Fork Failure\n");
			exit(1);
		}
		if (all->info->pid == 0)
		{
      //close(pipes[i][0]);
      //cmd = get_process(all->tokens, i);
      //if (which_builtin(cmd->token) == 1)
      //{
      //  //handle_builtin(all, i);
      //  return (0);
      //}
      child_process(i, all, pipes);
      exit (1);
		}
    else
    {
      //close(pipes[i][1]);
      token = all->tokens;
      while (token->next->process_nbr != 0)
        token = token->next;
      all->info->last_pid = all->info->pid;
 //     waitpid(all->info->pid, NULL, 0);
    }
		i++;
	}
  //waitpid(all->info->last_pid, NULL, 0);
  //while (wait(0) > 0);
 // i = 0;
 // while (i < all->info->total_proc)
 // {
 //   write(2, "waiting\n", 8);
 //   waitpid(-1, NULL, 0);
 //   i++;
 // }
  dprintf(2, "finished forking\n");
  return (0);
}

void	open_pipes(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("opening pipes\n");
	while (i < all->info->total_proc - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error: Pipes Failure\n");
			exit(1);
		}
		i++;
		ft_printf("%d pipe opened\n\n", i);
	}
	fork_init(all, pipes);
	i = 0;
	while (i < all->info->total_proc - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
  i = 0;
  while (i < all->info->total_proc)
  {
    write(2, "waiting\n", 8);
    waitpid(-1, NULL, 0);
    i++;
  }
	//return (pipes);
}

//TODO: Delete this after, mtice will do this in parsing
int	get_files(t_data *all)
{
	if (all->info->infile)
		all->info->in_fd = open(all->info->infile, O_RDONLY);
  else if (!all->info->infile)
    all->info->in_fd = 0;
	if (all->info->in_fd < 0)
		ft_printf("Error: %s not found\n", all->info->infile);
	if (all->info->outfile)
		all->info->out_fd = open(all->info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  else if (!all->info->outfile)
    all->info->out_fd = 1;
	if (all->info->out_fd < 0)
		ft_printf("Error: %s incorrect permissions\n", all->info->infile);
	if (all->info->append)
		all->info->app_fd = open(all->info->append, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (all->info->app_fd < 0)
		ft_printf("Error: %s incorrect permissions\n", all->info->infile);
  ft_printf("in fd: [%d]\n", all->info->in_fd);
  ft_printf("out fd: [%d]\n", all->info->out_fd);
	return (0);
}

int	one_command(t_data *all)
{
  t_token *cmd;

  cmd = get_process(all->tokens, 0);
  if (which_builtin(cmd->token) == 1)
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
	int	**pipes;

	//if its builtin, dont exit
	//builtin(all);
	//if needs fork
  all->info->in_fd = 0;
  all->info->out_fd = 1;
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
		if (current->type == COMMAND || current->type == BUILTIN)
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
	//get_files(all);
	if (all->info->total_proc == 1)
		one_command(all);
  else if (all->info->total_proc > 1)
	{
    //int j = 0;
		pipes_init(&pipes, all);
		open_pipes(pipes, all);
    //close(all->info->in_fd);
    //close(all->info->out_fd);
    //while (j < all->info->total_proc - 1)
    //{
    //  close(pipes[j][0]);
    //  close(pipes[j][1]);
    //  j++;
    //}
	//	if (execute_command(all))
	//		return (1);
	}
	return (0);
}

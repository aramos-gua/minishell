/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/21 12:22:34 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_data *all, int i, int piped)
{
	t_token *cmd;
	char	  *path;
	char    **cmd_arr;

  //if (all->info->in_fd != STDIN_FILENO)
  //  get_fd(all, i, 0);
  //else if (all->info->out_fd != STDOUT_FILENO)
  //  get_fd(all, i, 1);
	cmd = get_process(all->tokens, i);
  dprintf(2, "the cmd [%d] found after get_process is [%s]\n", i, cmd->token);
	if (!cmd)
  {
    write(2, "exited after cmd\n", 17);
	  exit (1);
  }
  if (is_builtin(cmd->token) && !piped)
  {
    if (all->info->in_fd != STDIN_FILENO)
      get_fd(all, i, 0);
    if (all->info->out_fd != STDOUT_FILENO)
      get_fd(all, i, 1);
    which_builtin(cmd->token, all, i);
    if (piped)
      exit (0);
    return (0);
  }
	path = get_cmd_path(cmd->token, all->c_envp);
  dprintf(2, "path is [%s]\n", path);
	if (!path)
	{
    all->return_val = 127;
    ft_printf("%s:command not found\n", cmd->token);
		exit (1);
	}
	cmd_arr = array_builder(all, i);
  //TODO:Delete this printing loop. Debug only
  //////////////////////////////////////////////////////////////////////////////////////////
  int j = 0;
  int k = 0;
  while (cmd_arr[j])
  {
    k = 0;
    dprintf(2, "[");
    while (cmd_arr[j][k])
      dprintf(2, "%c", cmd_arr[j][k++]);
    dprintf(2, "]");
    dprintf(2, " -> ");
    j++;
  }
  if (cmd_arr[j] == NULL)
    dprintf(2, " [NULL] ");
  write(2, "\n", 1);
  //////////////////////////////////////////////////////////////////////////////////////////
  int pid;
  if (!piped)
  {
    pid = fork();
    if (pid == 0)
    {
      if (all->info->in_fd != STDIN_FILENO)
        get_fd(all, i, 0);
      if (all->info->out_fd != STDOUT_FILENO)
        get_fd(all, i, 1);
      if (execve(path, cmd_arr, all->c_envp) == -1)
      {
        ft_printf("exited after execve\n");
        //perror(cmd_arr[0]);
        free(path);
        //free_split(all->tokens->next->token);
        exit (1);
      }
    }
    else
      waitpid(pid, NULL, 0);
  }
  else
  {
    if (all->info->in_fd != STDIN_FILENO)
      get_fd(all, i, 0);
    if (all->info->out_fd != STDOUT_FILENO)
      get_fd(all, i, 1);
    if (execve(path, cmd_arr, all->c_envp) == -1)
    {
      ft_printf("exited after execve\n");
      //perror(cmd_arr[0]);
      free(path);
      //free_split(all->tokens->next->token);
      exit (1);
    }
  }
  free(path);
  //free_split(&all->tokens->next->token);
  return(0);
}

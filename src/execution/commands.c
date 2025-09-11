/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 20:33:25 by Alejandro Ram    ###   ########.fr       */
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
  }
  if (is_builtin(cmd->token))
  {
    if (!piped)
    {
      int fds_bak[2];

      fds_bak[0] = dup(STDIN_FILENO);//3
      fds_bak[1] = dup(STDOUT_FILENO);//4
      redirect_fds(all, i);
      which_builtin(cmd->token, all, i);
      dup2(fds_bak[0], STDIN_FILENO);
      dup2(fds_bak[1], STDOUT_FILENO);
      close(fds_bak[0]);
      close(fds_bak[1]);
      ft_dprintf(2, "reverting fds\n");
      return (0);
    }
    // else if (piped)
    // {
    //   // int pid;
    //   //
    //   // pid = fork();
    //   // if (pid == 0)
    //   {
    //     // redirect_fds(all, i);
    //     which_builtin(cmd->token, all, i);
    //   }
    //   // else
    //   // waitpid(pid, NULL, 0);
    //   return (0);
    // }
  }
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!path)
    return (command_not_found(all, cmd));
	cmd_arr = array_builder(all, i);
  int pid;
  if (!piped)
  {
    pid = fork();
    if (pid == 0)
    {
      redirect_fds(all, i);
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
    redirect_fds(all, i);
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

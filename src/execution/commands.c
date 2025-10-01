/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/30 00:53:56 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	call_execve(t_data *all, int i, char *path, t_token *cmd)
{
	if (get_fd(all, i))
		return (free(path), all->return_val = 1, 1);
	default_sigquit();
	if (execve(path, all->arr, all->c_envp) == -1)
	{
		// ft_dprintf(2, "minishell: %s", cmd->token);
		// perror(": ");
		ft_dprintf(2, "minishell: ");
		perror(cmd->token);
		free(path);
		return (ft_return_val(all, errno), 0);
	}
	return (0);
}

static int	call_builtins(t_data *all, t_token *cmd, int i, int piped)
{
	int		fds_bak[2];
	int		nodes;

	nodes = ft_lstsize(all->tokens, i);
	if (!ft_strncmp(cmd->token, "exit", 5))
		ft_exit(all, nodes, cmd, 1);
	fds_bak[0] = dup(STDIN_FILENO);
	fds_bak[1] = dup(STDOUT_FILENO);
	if (get_fd(all, i))
		return (all->return_val = 1, 1);
	which_builtin(cmd->token, all, i);
	dup2(fds_bak[0], STDIN_FILENO);
	dup2(fds_bak[1], STDOUT_FILENO);
	close(fds_bak[0]);
	close(fds_bak[1]);
	if (!piped)
		return (2);
	if (all->c_envp)
		free_double_char(all->c_envp);
	if (all->c_exp)
		free_double_char(all->c_exp);
	free_all(all);
	exit (0);
}

static int	exit_cmd_not_found(t_data *all, int piped)
{
	if (!piped)
		return (0);
	if (all->c_envp)
		free_double_char(all->c_envp);
	if (all->c_exp)
		free_double_char(all->c_exp);
	free_all(all);
	exit (0);
}

void	parent_waiting(t_data *all, int i)
{
	int		status;

	waitpid(all->info[i].pid, &status, 0);
	if (WIFEXITED(status))
		all->return_val = WEXITSTATUS(status);
}

int	execute_command(t_data *all, int i, int piped)
{
	t_token	*cmd;
	char	*path;

	cmd = get_process(all->tokens, i);
	if (!cmd)
		return (exit_cmd_not_found(all, piped));
	if (is_builtin(cmd->token))
		return (call_builtins(all, cmd, i, piped));
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!cmd->token || cmd->token[0] == '\0' || !path)
		return (command_not_found(all, cmd), 1);
	array_builder(all, i);
	if (!piped)
	{
		all->info->pid = fork();
		if (all->info->pid == 0)
			return (call_execve(all, i, path, cmd));
		else
			parent_waiting(all, i);
	}
	else
		return (call_execve(all, i, path, cmd));
	free(path);
	return (-1);
}

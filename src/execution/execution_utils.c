/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:54:03 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/13 20:17:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*get_process(t_token *list, int i)
{
	t_token	*current;
	t_token	*cmd;

	if (!list)
		return (NULL);
	current = list;
	while (current->process_nbr != i)
		current = current->next;
	cmd = get_cmd_node(current, i);
	return (cmd);
}

t_token	*get_cmd_node(t_token *list, int i)
{
	t_token	*current;
	bool	seen_before;

	seen_before = false;
	if (!list)
		return (NULL);
	current = list;
	while ((current->type != COMMAND && current->builtin != 1) \
		|| current->process_nbr != i)
	{
		if ((current == list && seen_before) || current->process_nbr > i)
			return (NULL);
		seen_before = true;
		current = current->next;
	}
	return (current);
}

int	ft_lstsize(t_token *list, int proc)
{
	t_token	*current;
	int		i;

	i = 0;
	if (!list)
		return (0);
	current = list;
	while (1)
	{
		if (current->process_nbr == proc)
			i++;
		current = current->next;
		if (current == list)
			break ;
	}
	return (i);
}

// else if (WIFSIGNALED(status))
// 	all->return_val = 128 + WTERMSIG(status);
void	return_n_signal(t_data *all)
{
	int	status;
	int	pid;

	status = 0;
	while (42)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == all->info->last_pid)
		{
			if (WIFEXITED(status))
				all->return_val = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 3)
					ft_dprintf(2, "Quit (core dumped)\n");
				if (WTERMSIG(status) == 2)
					ft_dprintf(2, "\n");
				all->return_val = 128 + WTERMSIG(status);
			}
		}
	}
}

void	echo_loop(t_data *all, t_token *arg, int n, int arg_count)
{
	while (n--)
	{
		if (arg->type == ARGUMENT)
		{
			if (ft_strncmp(arg->token, "$?", 3))
				all->return_val = 0;
			if (arg->token[0] == '\0')
			{
				if (n != arg_count-- && arg_count > 0)
					ft_printf(" ");
				arg = arg->next;
				continue ;
			}
			ft_printf("%s", arg->token);
			if (n != arg_count-- && arg_count > 0)
				ft_printf(" ");
		}
		arg = arg->next;
	}
}

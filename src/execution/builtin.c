/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:42:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/30 00:36:01 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_data *all, t_token *arg, int line_flag)
{
	int	n;
	int	arg_count;

	n = tokens_in_process(all->tokens, arg->prev->process_nbr) - 1;
	arg_count = count_cmd_arg(all->tokens, arg->prev->process_nbr) - 1;
	while (arg->token && only_n(arg->token) && n-- && arg_count--)
	{
		line_flag = 0;
		arg = arg->next;
	}
	echo_loop(all, arg, n, arg_count);
	if (line_flag)
		ft_printf("\n");
	return (all->return_val = 0, 0);
}

static void	delete_element(t_token *arg, char **arr)
{
	int		i;
	int		count;
	char	*temp;

	count = 0;
	i = exist_in_arr(arg->token, arr, false);
	while (arr[count])
		count++;
	if (i > -1)
	{
		temp = arr[i];
		arr[i] = arr[count - 1];
		free (temp);
		arr[count - 1] = NULL;
	}
}

int	ft_unset(t_data *all, t_token *cmd_node, int proc)
{
	t_token	*arg;

	if (all->total_proc > 1)
		return (1);
	if (cmd_node->next->type == ARGUMENT)
		arg = cmd_node->next;
	else
		return (1);
	if (arg->token[0] == '-')
	{
		ft_dprintf(2, "minishell: unset: %s: invalid option\n", arg->token);
		ft_dprintf(2, "unset: usage: unset [-f] [-v] [-n] [name ...]\n");
		all->return_val = 2;
	}
	else
		all->return_val = 0;
	while (arg->type == ARGUMENT && arg->process_nbr == proc)
	{
		delete_element(arg, all->c_envp);
		delete_element(arg, all->c_exp);
		arg = arg->next;
	}
	return (1);
}

int	exit_helper(t_data *all)
{
	rl_clear_history();
	if (all->c_envp)
	{
		free_double_char(all->c_envp);
		all->c_envp = NULL;
	}
	if (all->c_exp)
	{
		free_double_char(all->c_exp);
		all->c_exp = NULL;
	}
	all->shlvl -= 1;
	if (all->shlvl >= 1)
	{
		find_envp(all, all->envp);
		return (1);
	}
	else
	{
		free_all(all);
		exit(all->return_val);
	}
	return (0);
}

int	ft_exit(t_data *all, int nodes, t_token *cmd_node, bool print)
{
	(void)print;
	if (nodes == 1)
		return (exit_helper(all));
	else if (nodes == 2 && !(isnt_number(all->tokens->token)))
	{
		all->return_val = ft_atoi(all->tokens->token);
		if (exit_helper(all))
			return (1);
	}
	else if (nodes >= 2 && isnt_number(cmd_node->next->token))
	{
		all->return_val = 2;
		ft_dprintf(2, "%s exit: %s%s", PROG, \
			cmd_node->next->token, INV_EXIT);
		if (exit_helper(all))
			return (1);
	}
	else if (nodes > 2 && !(isnt_number(cmd_node->next->token)))
		return (ft_dprintf(2, "minishell: exit: too many arguments\n"), \
		all->return_val = 1, 1);
	return (0);
}

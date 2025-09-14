/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:42:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/13 17:00:51 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_data *all, t_token *cmd_node)
{
	int		line_flag;
	t_token	*arg;

	line_flag = 1;
	arg = cmd_node->next;
	while (arg->token && only_n(arg->token))
	{
		line_flag = 0;
		arg = arg->next;
	}
	while (arg->type == ARGUMENT)
	{
		close(STDOUT_FILENO);
		if (printf("%s", arg->token) < 0)
		{
			dprintf(2, "jamoncito in echo");
			return (all->return_val = 1, perror("minishell"), 1);
		}
		if (arg->next->type == ARGUMENT)
			ft_printf(" ");
		arg = arg->next;
	}
	if (line_flag)
		ft_printf("\n");
	return (all->return_val = 0, 0);
}

static void	delete_element(t_token *arg, char **arr)
{
	int	i;
	int	count;

	count = 0;
	i = exist_in_arr(arg->token, arr, false);
	while (arr[count])
		count++;
	if (i > -1)
	{
		arr[i] = arr[count - 1];
		arr[count - 1] = NULL;
	}
}

int	ft_unset(t_data *all, t_token *cmd_node)
{
	t_token	*arg;

	if (all->total_proc > 1)
		return (1);
	if (cmd_node->next->type == ARGUMENT)
		arg = cmd_node->next;
	else
		return (1);
	delete_element(arg, all->c_envp);
	delete_element(arg, all->c_exp);
	return (1);
}

int	exit_helper(t_data *all)
{
	(rl_clear_history(), free_double_char(all->c_envp), free_all(all));
	if (all->c_exp)
		free_double_char(all->c_exp);
	//find_envp()//TODO:revuild envp and exp
	// if (all->shlvl > 1)
	// 	return (1);
	// else
		exit (all->return_val);
	return (0);
}

int	ft_exit(t_data *all, int nodes, t_token *cmd_node)
{
	if (all->info->total_proc == 1)
	{
		if (nodes == 1)
			return (all->return_val = 0, exit_helper(all), 1);
		else if (nodes == 2 && !(isnt_number(all->tokens->token)))
		{
			all->return_val = ft_atoi(all->tokens->token);
			exit_helper(all);
		}
		else if (nodes >= 2 && isnt_number(cmd_node->next->token))
		{
			all->return_val = 255;
			ft_dprintf(2, "%sexit: %s%s", PROG, all->tokens->token, INV_EXIT);
			exit_helper(all);
		}
		else if (nodes > 2 && !(isnt_number(cmd_node->next->token)))
		{
			all->return_val = 255;
			ft_dprintf(2, "exit\nminishell: exit: too many arguments.");
			return (1);
		}
	}
	return (0);
}

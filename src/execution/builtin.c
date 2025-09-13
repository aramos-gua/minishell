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
		ft_printf("%s", arg->token);
		if (arg->next->type == ARGUMENT)
			ft_printf(" ");
		arg = arg->next;
	}
	if (line_flag)
		ft_printf("\n");
	return (all->return_val = 0, 0);
}

int	ft_unset(t_data *all, int proc, t_token *cmd_node)
{
	(void)proc;
	int		i;
	t_token	*arg;

	if (cmd_node->next->type == ARGUMENT)
		arg = cmd_node->next;
	else
		return (0);
	i = exist_in_arr(arg->token, all->c_envp, false);
	if (i > -1)
		all->c_envp[i][0] = '\0';
	i = exist_in_arr(arg->token, all->c_exp, true);
	if (i > -1)
		all->c_exp[i][0] = '\0';
	return (all->return_val = 0, 0);
}

int	ft_exit(t_data *all, int nodes, t_token *cmd_node, int fds_bak[2])
{
	(void)fds_bak;
	ft_dprintf(2, "total proc: [%d]\n", all->info->total_proc);
	if (all->info->total_proc == 1)
	{
		if (nodes == 1)
		{
			all->return_val = 0;
			exit ((int)all->return_val);
		}
		else if (nodes == 2 && !(isnt_number(all->tokens->token)))
		{
			all->return_val = ft_atoi(all->tokens->token);
			exit (all->return_val);
		}
		else if (nodes >= 2 && isnt_number(cmd_node->next->token))
		{
			all->return_val = 255;
			ft_dprintf(2, "minishell: exit: %s: numeric argument required.", all->tokens->token);
			exit (all->return_val);
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

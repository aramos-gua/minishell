/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:44:46 by mtice             #+#    #+#             */
/*   Updated: 2025/09/25 15:49:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_init(t_data *all)
{
	all->shlvl = 1;
	all->return_val = 0;
	all->c_envp = NULL;
	all->c_exp = NULL;
	init_all(all);
}

void	init_all(t_data *all)
{
	g_signal = SA_RESTART;
	all->procs = NULL;
	all->info = NULL;
	all->tokens = NULL;
	all->arr = NULL;
	all->total_proc = 0;
}

int	is_minishell(char *input)
{
	int	i;

	if (!ft_strncmp("./minishell\0", input, 12))
		return (1);
	else if (!ft_strncmp("./minishell", input, 11))
	{
		i = 11;
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	subtract_shlvl(t_data *all)
{
	all->shlvl--;
	if (all->shlvl > 2)
	{
		rl_clear_history();
		free_double_char(all->c_envp);
		if (all->c_exp)
			free_double_char(all->c_exp);
		find_envp(all, all->envp);
	}
}

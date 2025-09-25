/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:39:56 by mtice             #+#    #+#             */
/*   Updated: 2025/09/25 15:40:45 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//frees all variables, if they exist
void	free_all(t_data *all)
{
	if (all->procs)
		free_double_char(all->procs);
	if (all->info)
		free_t_proc(all->info, all->total_proc);
	if (all->tokens)
		free_t_token(all->tokens);
	if (all->arr)
		free_double_char(all->arr);
	unlink_heredocs(all->total_proc);
}

//-----------------------------------------------------------------------------
//frees the variables that only need to be freed at the end of the program
void	last_free(t_data *all)
{
	rl_clear_history();
	if (all->c_envp)
		free_double_char(all->c_envp);
	if (all->c_exp)
		free_double_char(all->c_exp);
	if (all->arr)
		free_double_char(all->arr);
	free_all(all);
}

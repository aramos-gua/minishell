/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:47:06 by mtice             #+#    #+#             */
/*   Updated: 2025/07/12 18:59:12 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//frees a 2-dimensional array
void	free_double_char(char **arr)
{
	int	j;

	j = 0;
	while (arr[j] != NULL)
		free(arr[j++]);
	free(arr);
}

//-----------------------------------------------------------------------------
//frees the t_proc struct
void	free_t_proc(t_proc *info, int total_procs)
{
	int		len;

	len = total_procs;
	while (len--)
		del_t_proc(&info, 0);
}

//-----------------------------------------------------------------------------
//frees the t_token struct
void	free_t_token(t_token *tokens)
{
	t_token	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != tokens->next)
	{
		if (i == -1)
		{
			temp = tokens->next;
			i++;
		}
		temp = temp->next;
		i++;
	}
	while (i--)
		del_t_token(&tokens, i);
}

static void	free_t_error(t_error *errors)
{
	t_error	*temp;
	int		i;

	temp = NULL;
	i = -1;
	while (temp != errors->next)
	{
		if (i++ == -1)
			temp = errors->next;
		i++;
	}
	while (i--)
		del_t_error(&errors, i);
}

//-----------------------------------------------------------------------------
//unlinks heredocs, in case they exist
void	unlink_heredocs(int total_procs)
{
	int		len;
	char	*path;
	char	*proc_nbr;

	len = total_procs;
	while (len--)
	{
		proc_nbr = ft_itoa(len);
		path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
		if (!access(path, F_OK))
			unlink(path);
		(free(proc_nbr)), (free(path));
	}
}

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
	if (all->errors)
		free_t_error(all->errors);
	// if (all->arr)
	// 	free_double_char(all->arr);
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
	free_all(all);
}

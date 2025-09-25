/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:48:45 by mtice             #+#    #+#             */
/*   Updated: 2025/09/17 21:30:10 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO: check if path has been correctly freed
static int	open_redir(int type, t_token *tkn_ptr, t_proc *info_ptr)
{
	char	*proc_nbr;
	char	*path;

	proc_nbr = ft_itoa(tkn_ptr->process_nbr);
	path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
	if ((type == RE_IN || type == HERE_DOC) && info_ptr->in_fd > 2)
		close(info_ptr->in_fd);
	else if ((type == RE_OUT || type == APPEND) && info_ptr->out_fd > 2)
		close(info_ptr->out_fd);
	if (type == RE_IN)
		info_ptr->in_fd = open(tkn_ptr->token, O_RDONLY);
	else if (type == HERE_DOC)
		info_ptr->in_fd = open(path, O_RDONLY);
	else if (type == RE_OUT)
		info_ptr->out_fd
			= open(tkn_ptr->token, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (type == APPEND)
		info_ptr->out_fd
			= open(tkn_ptr->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
	(free(proc_nbr), free(path));
	if (info_ptr->in_fd < 0 || info_ptr->out_fd < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(tkn_ptr->token), 1);
	return (0);
}

//TODO: check permissions for executables
int	redirects(t_data *all)
{
	t_token	*token_temp;
	t_proc	*info_temp;
	int		i;

	token_temp = NULL;
	info_temp = all->info->next;
	i = -1;
	while (token_temp != all->tokens->next)
	{
		if (i++ == -1)
			token_temp = all->tokens->next;
		if (token_temp->process_nbr != info_temp->process_nbr)
			info_temp = info_temp->next;
		if (open_redir(token_temp->type, token_temp, info_temp))
		{
			all->return_val = 1;
			if (all->total_proc == 1)
				return (1);
			while (token_temp->process_nbr == info_temp->process_nbr)
				token_temp = token_temp->next;
		}
		else
			token_temp = token_temp->next;
	}
	return (0);
}

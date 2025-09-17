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

void	redir_errors(t_error *errors)
{
	t_error	*temp;
	int		i;

	temp = NULL;
	i = -1;
	if (!errors)
		return ;
	while (temp != errors->next)
	{
		if (i++ == -1)
			temp = errors->next;
		(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(temp->filename, 2));
		(ft_putstr_fd(" ", 2), ft_putendl_fd(NO_FILE_OR_D, 2));
		temp = temp->next;
	}
}

//TODO: check if path has been correctly freed
static int	open_redir(t_data *all, int type, t_token *tkn_ptr, t_proc *info_ptr)
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
	(void)all;
	if (info_ptr->in_fd < 0 || info_ptr->out_fd < 0)
		return (all->errors = add_t_error(all->errors, tkn_ptr->token), 1);
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
		if (open_redir(all, token_temp->type, token_temp, info_temp))
		{
			while (token_temp->process_nbr == info_temp->process_nbr)
				token_temp = token_temp->next;
		}
		else
			token_temp = token_temp->next;
	}
	return (0);
}

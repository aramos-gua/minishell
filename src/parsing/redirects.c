/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:48:45 by mtice             #+#    #+#             */
/*   Updated: 2025/08/28 21:01:38 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		if (token_temp->type == RE_IN)
		{
			if (info_temp->in_fd > 2)
				close (info_temp->in_fd);
			info_temp->in_fd = open(token_temp->token, O_RDONLY);
		}
		else if (token_temp->type == HERE_DOC)
		{
			if (info_temp->in_fd > 2)
				close (info_temp->in_fd);
			info_temp->in_fd = open(ft_strjoin("/tmp/.heredoc_p", ft_itoa(token_temp->process_nbr)), O_RDONLY);
		}
		else if (token_temp->type == RE_OUT)
		{
			if (info_temp->out_fd > 2)
				close(info_temp->out_fd);
			info_temp->out_fd = open(token_temp->token, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (token_temp->type == APPEND)
		{
			if (info_temp->out_fd > 2)
				close(info_temp->out_fd);
			info_temp->out_fd = open(token_temp->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (info_temp->out_fd < 0 || info_temp->in_fd < 0)
			return (ft_putstr_fd("minishell: ", 2), perror(token_temp->token), 1);
		token_temp = token_temp->next;
	}
	return (0);
}

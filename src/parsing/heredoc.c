/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/08/23 15:53:43 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	open_heredoc(t_token *tkn_ptr)
{
	int		here_fd[2];
	char	*line;

	*here_fd = open(ft_strjoin(".", tkn_ptr->token), O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (*here_fd < 0)
	{
		perror(ft_strjoin(".", tkn_ptr->token));
		return (1);
	}
	close(here_fd[0]);
	line = readline("> ");
	while (ft_strncmp(line, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1))
	{
		// if (write(here_fd[1], line, ft_strlen(line)) < 0)
		// 	return (1);
		// if (write(here_fd[1], "\n", 1) < 0)
		// 	return (1);
		ft_putendl_fd(line, here_fd[1]);
		line = readline("> ");
	}
	return (0);
}


//------------------------------------------------------------------------------
//find_heredoc() finds all the heredoc tokens, and fills the delimiter array, with the delimiter names
//create_tmp() creates all the temp files for each heredoc
//fill_tmp() populates each temp file with the lines read up to the delimiter
//heredoc_expansion() checks each delimiter for expansion, and checks each line for expansion as well
int	heredoc(t_data *all)
{
	int		i;
	t_token	*temp;

	i = -1;
	temp = NULL;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		if (temp->type == HERE_DOC)
		{
			if (open_heredoc(temp))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

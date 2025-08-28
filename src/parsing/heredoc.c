/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/08/28 21:01:39 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int	expand_heredoc(char *line)
// {
//
// }
//
// static int unlink_heredoc(t_token *tkn_ptr)
// {
// 	unlink(ft_strjoin("/tmp/heredoc_p", ft_itoa(tkn_ptr->process_nbr)));
// }

static int	write_heredoc(t_data *all, t_token *tkn_ptr, int to_expand)
{
	char	*path;
	int		here_fd;
	char	*line;

	path = ft_strjoin("/tmp/.heredoc_p", ft_itoa(tkn_ptr->process_nbr));
	here_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (here_fd < 0)
	{
		perror(ft_strjoin("bash: ", path));
		return (1);
	}
	line = readline("> ");
	while (ft_strncmp(line, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1))
	{
		if (!to_expand)
			ft_putendl_fd(line, here_fd); //heredoc expansion
		else
			ft_putendl_fd(do_expansion(all, line), here_fd);
		line = readline("> ");
	}
	close(here_fd);
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
	int		to_expand;

	i = -1;
	temp = NULL;
	while (temp != all->tokens->next)
	{
		to_expand = 0;
		if (i++ == -1)
			temp = all->tokens->next;
		if (temp->type == HERE_DOC)
		{
			// if (temp->process_nbr == temp->next->process_nbr)
			// 	unlink_heredoc(temp);
			if (ft_strlen(ft_strchr(temp->token, '"')) > ft_strlen(ft_strchr(temp->token, '\'')))
			{
				del_char(temp->token, '"');
				to_expand = 1;
			}
			else if (ft_strlen(ft_strchr(temp->token, '\'')) > ft_strlen(ft_strchr(temp->token, '\'')))
			{
				del_char(temp->token, '\'');
				to_expand = 1;
			}
			if (write_heredoc(all, temp, to_expand))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

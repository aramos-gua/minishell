/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/08/28 21:01:38 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	heredoc_error(t_token *tkn_ptr, int line_n)
{
	char	*num;

	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	num = ft_itoa(line_n);
	ft_putstr_fd(num, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(tkn_ptr->token, 2);
	ft_putendl_fd("')", 2);
}

static int	write_heredoc(t_data *all, t_token *tkn_ptr, int to_expand)
{
	char		*proc_nbr;
	char		*path;
	int			here_fd;
	char		*line;
	int			line_n = 0;

	proc_nbr = ft_itoa(tkn_ptr->process_nbr);
	path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
	here_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (here_fd < 0)
	{
		perror(ft_strjoin("minishell: ", path));
		return (1);
	}
	line = readline("> ");
	while (ft_strncmp(line, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1) && ++line_n
			&& g_last_signal != SIGINT)
	{
		if (!line)
		{
			heredoc_error(tkn_ptr, line_n - 1);
			break;
		}
		if (!to_expand)
			ft_putendl_fd(line, here_fd);
		else
		{
			char *expanded;
			expanded = do_expansion(all, line);
			ft_putendl_fd(expanded, here_fd);
			free(expanded);
		}
		line = readline("> ");
	}
	(free(proc_nbr), free(path), close(here_fd));
	if (g_last_signal == SIGINT)
		return (1);
	return (0);
}

//------------------------------------------------------------------------------
//heredoc()
//TODO:notes
int	heredoc(t_data *all)
{
	int		i;
	t_token	*temp;
	int		to_expand;

	i = -1;
	temp = NULL;
	all->mode= H_DOC;
	while (temp != all->tokens->next)
	{
		to_expand = 0;
		if (i++ == -1)
			temp = all->tokens->next;
		if (temp->type == HERE_DOC)
		{
			if (ft_strchr(temp->token, '"') || ft_strchr(temp->token, '\''))
				delete_quotes(temp->token);
			else
				to_expand = 1;
			if (write_heredoc(all, temp, to_expand))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

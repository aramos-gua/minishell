/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/09/25 16:05:23 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	heredoc_error(t_token *tkn_ptr, int n, int *l_nbr)
{
	char	*num;

	if (g_signal == SA_RESTART)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		num = ft_itoa(*l_nbr);
		ft_putstr_fd(num, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(tkn_ptr->token, 2);
		ft_putendl_fd("')", 2);
		free(num);
		*l_nbr += n - 1;
	}
	else
		*l_nbr += n;
	return (1);
}

//-----------------------------------------------------------------------------
// writes to the heredoc
// l: line (each line written to the heredoc)
// n: number of lines written to the heredoc
static char	*write_heredoc(t_data *all, t_token *tkn_ptr, int to_exp, int *ln)
{
	char		*proc_nbr;
	char		*path;
	int			here_fd;
	char		*l;
	int			n;

	proc_nbr = ft_itoa(tkn_ptr->process_nbr);
	path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
	here_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	n = 0;
	while (++n)
	{
		(set_signals_heredoc(all), l = readline("> "));
		if ((!l || g_signal != SA_RESTART) && heredoc_error(tkn_ptr, n, ln))
			return (free(proc_nbr), free(path), close(here_fd), l);
		else if (!ft_strncmp(l, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1))
			break ;
		else if (!to_exp)
			ft_putendl_fd(l, here_fd);
		else if (to_exp)
		{
			(free(path), path = do_expansion(all, tkn_ptr, l));
			(ft_putendl_fd(path, here_fd));
		}
	}
	return (free(proc_nbr), free(path), close(here_fd), NULL);
}

//------------------------------------------------------------------------------
//opens heredocs and flags them for do_expansion
//deletes the quotes in the token that is the heredoc delimiter
//ln: line number
char	*heredoc(t_data *all)
{
	int			i;
	t_token		*temp;
	char		*input;
	static int	ln = 0;

	i = -1;
	temp = NULL;
	ln++;
	while (temp != all->tokens->next)
	{
		if (i++ == -1)
			temp = all->tokens->next;
		if (temp->type == HERE_DOC)
		{
			if (ft_strchr(temp->token, '"') || ft_strchr(temp->token, '\''))
				(delete_quotes(temp->token), temp->exp = 0);
			else
				temp->exp = 1;
			input = write_heredoc(all, temp, temp->exp, &ln);
			if (input)
				return (input);
		}
		temp = temp->next;
	}
	return (NULL);
}

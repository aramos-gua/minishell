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

//-----------------------------------------------------------------------------
//prints the heredoc error message when ^C or ^D are detected
static int	heredoc_error(t_data *all, t_token *tkn_ptr, int *l_nbr)
{
	char	*num;

	if (g_signal == SA_RESTART)
	{
		ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
		num = ft_itoa(*l_nbr);
		ft_putstr_fd(num, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(tkn_ptr->token, 2);
		ft_putendl_fd("')", 2);
		free(num);
	}
	else
		set_signals_heredoc(all);
	return (1);
}

static char	*read_input(void)
{
	char	*temp;
	char	*l;

	temp = NULL;
	l = NULL;
	ft_putstr_fd("> ", 1);
	temp = get_next_line(fileno(stdin));
	l = ft_strtrim(temp, "\n");
	return (free(temp), l);
}

//-----------------------------------------------------------------------------
// writes to the heredoc
// l: line (each line written to the heredoc)
// n: number of lines written to the heredoc
static int	write_heredoc(t_data *all, t_token *tkn_ptr, int to_exp, int *ln)
{
	char		*proc_nbr;
	char		*path;
	int			here_fd;
	char		*l;

	proc_nbr = ft_itoa(tkn_ptr->process_nbr);
	path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
	here_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	l = NULL;
	while (42)
	{
		(set_signals_heredoc(all), l = read_input());
		if ((!l || g_signal != SA_RESTART) && heredoc_error(all, tkn_ptr, ln))
			return (free(proc_nbr), free(path), close(here_fd), 1);
		else if (!ft_strncmp(l, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1))
			break ;
		else if (!to_exp)
			ft_putendl_fd(l, here_fd);
		else if (to_exp)
			(free(path), path = l, l = do_expansion(all, tkn_ptr, path),
				ft_putendl_fd(l, here_fd), path = NULL);
		(free(l), l = NULL);
	}
	return (free(l), free(proc_nbr), free(path), close(here_fd), 0);
}

//------------------------------------------------------------------------------
//opens heredocs and flags them for do_expansion
//deletes the quotes in the token that is the heredoc delimiter
//ln: line number
int	heredoc(t_data *all)
{
	int			i;
	t_token		*temp;
	static int	ln = 0;

	i = -1;
	temp = NULL;
	ln++;
	g_signal = SA_RESTART;
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
			if (write_heredoc(all, temp, temp->exp, &ln))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

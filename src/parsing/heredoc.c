/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:37:21 by mtice             #+#    #+#             */
/*   Updated: 2025/09/14 20:41:31 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	heredoc_error(t_data *all, t_token *tkn_ptr, int line_n)
{
	(void)all;
	static int		count = 0;
	char			*num;

	//printf("count: %d\n", count);
	if (g_signal == SA_RESTART)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		num = ft_itoa(count + 1);
		ft_putstr_fd(num, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(tkn_ptr->token, 2);
		ft_putendl_fd("')", 2);
	}
	count += (line_n - count);
	//printf("count: %d line_n: %d\n" , count, line_n);
}

static char	*write_heredoc(t_data *all, t_token *tkn_ptr, int to_expand)
{
	char		*proc_nbr;
	char		*path;
	int			here_fd;
	char		*line;
	static int	line_n = 0;

	proc_nbr = ft_itoa(tkn_ptr->process_nbr);
	path = ft_strjoin("/tmp/.heredoc_p", proc_nbr);
	here_fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (here_fd < 0)
	{
		perror(ft_strjoin("minishell: ", path));
		return (path);
	}
	while (42)
	{
		set_signals_heredoc();
		line = readline("> ");
		// if (g_signal != SA_RESTART)
		// 	break ; //TODO: free
		if (!line || g_signal != SA_RESTART) //TODO: if g_signal != SA_RESTART
		{
			if (g_signal != SA_RESTART)
				++line_n;
			heredoc_error(all, tkn_ptr, line_n);
			break;
		}
		if (g_signal != SA_RESTART)
			break ; //TODO: free
		else if (!ft_strncmp(line, tkn_ptr->token, ft_strlen(tkn_ptr->token) + 1))
			break;
		else if (!to_expand)
			ft_putendl_fd(line, here_fd);
		else if (to_expand)
		{
			char *expanded;
			expanded = do_expansion(all, line);
			ft_putendl_fd(expanded, here_fd);
			free(expanded);
		}
		line_n++;
	}
	(free(proc_nbr), free(path), close(here_fd));
	if (g_signal != SA_RESTART)
		return (line);
	return (NULL);
}

//------------------------------------------------------------------------------
//heredoc()
//TODO:notes
char *heredoc(t_data *all)
{
	int		i;
	t_token	*temp;
	char	*input;
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
			if (ft_strchr(temp->token, '"') || ft_strchr(temp->token, '\''))
				delete_quotes(temp->token);
			else
				to_expand = 1;
			input = write_heredoc(all, temp, to_expand);
			if (input)
				return (input);
		}
		temp = temp->next;
	}
	return (NULL);
}

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

typedef struct s_heredoc
{
	char	**delimiter;
	int		*fds;
	
}				t_heredoc;


static int	find_heredoc(t_token *tokens, t_heredoc *heredoc)
{
	t_token	*temp;
	int		j;
	int		len;

	temp = NULL;
	j = -1;
	len = 0;
	while (temp != tokens->next)
	{
		if (j++ == -1)
			temp = tokens->next;
		if (temp->type == HERE_DOC)
			len++;
		temp = temp->next;
	}
	heredoc->delimiter = malloc(sizeof(char *) * (len + 1));
	j = -1;
	temp = NULL;
	while (temp != tokens->next)
	{
		if (j++ == -1)
			temp = tokens->next;
		if (temp->type == HERE_DOC)
			heredoc->delimiter[j] = ft_strdup(temp->token);
		temp = temp->next;
	}
	heredoc->delimiter[j] = NULL;
	j = -1;
	printf("------------------DELIMITERS--------------\n");
	while (heredoc->delimiter[j++] != NULL)
		printf("delimiter[%d]:%s\n", j, heredoc->delimiter[j]);
	if (!heredoc->delimiter)
		return (1);
	return (0);
}

static int	create_tmp(t_heredoc *heredoc)
{
	int	j;
	char	*filename;

	j = 0;
	while (heredoc->delimiter[j] != NULL)
	{
		filename = ft_strjoin(".", heredoc->delimiter[j]);
		heredoc->fds[j] = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (heredoc->fds[j] < 0)
			return (perror("Could not create heredoc"), 1);
	}
	return (0);
}

//static int	fill_tmp()

//------------------------------------------------------------------------------
//find_heredoc() finds all the heredoc tokens, and fills the delimiter array, with the delimiter names
//create_tmp() creates all the temp files for each heredoc
//fill_tmp() populates each temp file with the lines read up to the delimiter
//heredoc_expansion() checks each delimiter for expansion, and checks each line for expansion as well
int	heredoc(t_data *all)
{
	t_heredoc	*heredoc;

	heredoc = NULL;
	if (find_heredoc(all->tokens, heredoc))
		return (1);
	else if (create_tmp(heredoc))
		return (1);
	// fill_tmp(heredoc);
	// heredoc_expansion(heredoc);
	return (0);
}

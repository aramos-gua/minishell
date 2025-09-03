/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:57:22 by mtice             #+#    #+#             */
/*   Updated: 2025/08/11 08:52:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//deals with redirection cases that we do not have to handle
//and incorrect redirections
// case 1: echo <>hello
// case 2: echo <<<hello
// case 3: echo ><hello
// etc
static int	deal_redirects(char *input, int *i)
{
	(*i)++;
	if (input[*i - 1] == '<')
	{
		if (input[*i] == '>' && input[*i + 1] != '\0')
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
		else if (input[*i] == '\0' || (input[*i] == '<' && input[*i + 1] == '\0')
			|| (input[*i] == '>' && input[*i + 1] == '\0'))
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `newline'", 2), 1);
		else if (input[*i] == '<' && input[*i + 1] == '<')
		{
			if (input[*i + 2] == '<' && input[*i + 3] == '<' && input[*i + 4] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<<<'", 2), 1);
			else if (input[*i + 2] == '<' && input[*i + 3] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<<'", 2), 1);
			else if (input[*i + 2] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `newline'", 2), 1);
		}
	}
	else if (input[*i - 1] == '>')
	{
		if (input[*i] == '<')
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
		else if (input[*i] == '\0' || (input[*i] == '>' && input[*i + 1] == '\0'))
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `newline'", 2), 1);
		else if (input[*i] == '>' && input[*i + 1] == '>')
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
//ideals with the case where the $ is incorrectly used e.g. $$HOME
static int	deal_expansion(char *input, int *i)
{
	int		j;

	j = 0;
	if (input[*i] == '$')
	{
		while (input[++(*i)] == '$')
			j++;
		(*i) -= (j + 1);
		if (j > 0)
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `$'", 2), 1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
//deals with multiple pipes case (order of cases matters)
//case1: pipes at the end of input, bash waits for you to finish your input
//case2: more than two pipes togeth ("|||") is a syntax error
static int	deal_multiple_pipes(char *input, int *i)
{
	int		j;

	j = 0;
	if (input[*i] == '|')
	{
		while ((input[*i] == '|' || ft_isspace(input[*i])) && input[*i] != '\0')
		{
			if (input[*i] == '|')
				j++;
			(*i)++;
		}
		if ((input[*i] == '\0' && j == 1) || j == 2)
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `|'", 2), 1);
		else if ((input[*i] == '\0' && j > 1) || j > 2)
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `||'", 2), 1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
//deals with unclosed quotes and pipes within quotes
//case 1: echo hi "|" world! this is one process only
//replaces a pipe within quotes by ascii 26
//during the tokenisation the pipe will be put back in the string
static int	deal_quotes(char *input, int *i)
{
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			(*i)++;
		}
		if (input[*i] == '\0')
			return (ft_putendl_fd(S_QUOTE, 2), 1);
	}
	else if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			(*i)++;
		}
		if (input[*i] == '\0')
			return (ft_putendl_fd(D_QUOTE, 2), 1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
//processes the raw input before it can be broken down into processes
//looks for syntax errors associated with quotes (single and double)
//pipes in quotes or multiple pipes
//expansion syntax errors
//and redirect syntax errors
int	input_check(char *input)
{
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if ((input[i] == '\'' || input[i] == '"') && deal_quotes(input, &i))
			return (1);
		else if (input[i] == '|' && deal_multiple_pipes(input, &i))
			return (1);
		else if (input[i] == '$' && deal_expansion(input, &i))
			return (1);
		else if ((input[i] == '<' || input[i] == '>')
			&& deal_redirects(input, &i))
			return (1);
		i++;
	}
	return (0);
}

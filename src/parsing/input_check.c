/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:57:22 by mtice             #+#    #+#             */
/*   Updated: 2025/08/09 20:50:13 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//--------------------------------------------------------------------------------------
//deals with redirection cases that we do not have to handle, and incorrect redirections
// case 1: echo <>hello
// case 2: echo <<<hello
// case 3: echo ><hello
// etc
static int	deal_redirects(char *input, int *i)
{
	if (input[*i] == '<')
	{
		(*i)++;
		if (input[*i] == '>' && input[*i + 1] != '\0')
			return (printf("bash: syntax error near unexpected token `>'\n"));
		else if (input[*i] == '\0' || (input[*i] == '<' && input[*i + 1] == '\0')
				|| (input[*i] == '>' && input[*i + 1] == '\0'))
			return (printf("bash: syntax error near unexpected token `newline'\n"));
		else if (input[*i] == '<' && input[*i + 1] == '<')
		{
			if (input[*i + 2] == '<')
				return (printf("bash: syntax error near unexpected token `<'\n"));
			return (printf("bash: syntax error near unexpected token `<<'\n"));
		}
	}
	else if (input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == '<')
			return (printf("bash: syntax error near unexpected token `<'\n"));
		else if (input[*i] == '\0' || (input[*i] == '>' && input[*i + 1] == '\0'))
			return (printf("bash: syntax error near unexpected token `newline'\n"));
		else if (input[*i] == '>' && input[*i + 1] == '>')
			return (printf("bash: syntax error near unexpected token `>'\n"));
	}
	return (0);
}

//----------------------------------------------------------------------------------------
//deals with the case where the $ is incorrectly used e.g. $$HOME
static int	deal_expansion(char *input, int *i)
{
	int		j;
	char	*syntax;

	j = 0;
	if (input[*i] == '$')
	{
		while (input[++(*i)] == '$')
			j++;
		if (j > 0)
		{
			syntax = malloc(sizeof(char) * (j + 1));
			if (!syntax)
				return (perror("Malloc error"), 1);
			syntax[j] = '\0';
			while (j-- > 0)
				syntax[j] = '$';
			printf("bash: syntax error near unexpected token `%s'\n", syntax);
			return (free(syntax), 1);
		}
	}
	return (0);
}

//-----------------------------------------------------------------------------------------
//deals with multiple pipes case (order of cases matters)
//case1: pipes at the end of input, bash waits for you to finish your input
//case2: two pipes together ("||") with tokens after cancels the effect of proceding commands
//case3: more than two pipes togeth ("|||") is a syntax error
static int	deal_multiple_pipes(char *input, int *i)
{
	int		j;
	char	*syntax;

	j = 0;
	if (input[*i] == '|')
	{
		while (input[(*i)++] == '|')
			j++;
		if (input[*i + 1] == '\0' && j <= 2)
			return (printf("UNIMPLEMENTED: wait for the rest of input\n"));
		else if (j == 2)
			return (printf("bash: syntax error near unexpected token `|'\n")); //TODO:bonus (||)
		//ft_bzero((input + *i - (j + 1)), ft_strlen(input + *i));
		else if (j > 2)
		{
			j -= 2;
			syntax = malloc(sizeof(char) * (j + 1));
			if (!syntax)
				return (perror("Malloc error"), 1);
			syntax[j] = '\0';
			while (j-- > 0)
				syntax[j] = '|';
			printf("bash: syntax error near unexpected token `%s'\n", syntax);
			return (free(syntax), 1);
		}
	}
	return (0);
}

//-----------------------------------------------------------------------------------------
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
			return (printf("bash: syntax error unclosed single quote\n"));
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
			return (printf("bash: syntax error unclosed double quote\n"));
	}
	return (0);
}

//---------------------------------------------------------------------------------------
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
		else if ((input[i] == '<' || input[i] == '>') && deal_redirects(input, &i))
			return (1);
		i++;
	}
	return (0);
}

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
//checks for syntax errors after the '<' operator
//after a redirection we can only have a word
//since we do not have to handle <> or <<< cases these can differ from bash
//case 1: cat < (NULL) or cat << (NULL) -> (unexpected newline)
//case 2: cat <> or cat <>> -> (unexpected '>' or unexpected '>>')
//case 3: cat <<> or cat <<>> -> (unexpected '>' or unexpected '>>')
static int	syntax_re_in(char *input, int *i)
{
	if (input[*i] == '<')
	{
		(*i)++;
		if (input[*i] == '\0' || (input[*i] == '<' && input[*i + 1] == '\0'))
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `newline'", 2), 1);
		else if (input[*i] == '>')
		{
			if (input[*i] == '>' && input[*i + 1] != '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
			else if (input[*i] == '>' && input[*i + 1] == '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>>'", 2), 1);
		}
		else if (input[*i] == '<')
		{
			if (input[*i + 1] == '>' && input[*i + 2] != '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
			else if (input[*i + 1] == '>' && input[*i + 2] == '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>>'", 2), 1);
			else if (input[*i + 1] == '<' && input[*i + 2] != '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
			else if (input[*i + 1] == '<' && input[*i + 2] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<<'", 2), 1);
		}
	}
	return (0);
}

//-----------------------------------------------------------------------------
//checks for syntax errors after the '>' operator
//case 1: cat > (NULL) or cat >> (NULL) -> (newline error)
//case 2: cat >< or cat ><< -> (unexpected '<' or unexpected '<<')
//case 3: cat >>< or cat >><< -> (unexpected '<' or unexpected '<<')
static int	syntax_re_out(char *input, int *i)
{
	if (input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == '\0' || (input[*i] == '>' && input[*i + 1] == '\0'))
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `newline'", 2), 1);
		else if (input[*i] == '<')
		{
			if (input[*i] == '<' && input[*i + 1] != '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
			else if (input[*i] == '<' && input[*i + 1] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<<'", 2), 1);
		}
		else if (input[*i] == '>')
		{
			if (input[*i + 1] == '<' && input[*i + 2] != '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<'", 2), 1);
			else if (input[*i + 1] == '<' && input[*i + 2] == '<')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `<<'", 2), 1);
			else if (input[*i + 1] == '>' && input[*i + 2] != '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
			else if (input[*i + 1] == '>' && input[*i + 2] == '>')
				return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>>'", 2), 1);
		}
	}
	return (0);
}

//-----------------------------------------------------------------------------
//deals with the case where the $ is incorrectly used e.g. $$HOME
static int	syntax_expansion(char *input, int *i)
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
//deals with incorrectly used pipes
//we do not have to handle the logical operator OR ('||'), it will be an error
//case 1: | echo hello -> pipe used at beginning of input
//case 2: echo hi ||| echo hello -> multiple pipes in a row
//case 3: echo hi | -> pipe used at the end of input
static int	syntax_multiple_pipes(char *input, int *i)
{
	int		j;
	int		w;
	int		r;

	j = 0;
	w = *i - 1;
	r = 0;
	if (input[*i] == '|')
	{
		while (w > 0 && (ft_isspace(input[w]) || input[w] == '<' || input[w] == '>'))
		{
			if (input[w] == '<' || input[w] == '>')
				r++;
			w--;
		}
		if (w == 0 || w == -1)
			j += 1;
		while ((input[*i] == '|' || ft_isspace(input[*i])) && input[*i] != '\0')
		{
			if (input[*i] == '|')
				j++;
			(*i)++;
		}
		(*i)--;
		if (input[*i + 1] == '\0' || j == 2 || r >= 1)
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `|'", 2), 1);
		else if (j > 2)
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `||'", 2), 1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
//deals with unclosed quotes and pipes within quotes
//case 1: echo "hi -> unclosed double quotes
//case 2: echo 'hi -> unclosed single quotes
//case 3: echo "hello | world" or echo 'hello | world' -> pipe is substituted
//with ascii 26 (SUB) and later added back during tokenisation
static int	syntax_quotes(char *input, int *i)
{
	//printf("char[%d]:%c\n", *i, input[*i]);
	(*i)++;
	if (input[*i - 1] == '\'')
	{
		while (input[*i] != '\'' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			(*i)++;
		}
		if (input[*i] == '\0')
			return (ft_putendl_fd(S_QUOTE, 2), 1);
	}
	else if (input[*i - 1] == '"')
	{
		while (input[*i] != '"' && input[*i] != '\0')
		{
			if (input[*i] == '|')
				input[*i] = 26;
			(*i)++;
		}
		if (input[*i] == '\0')
			return (ft_putendl_fd(D_QUOTE, 2), 1);
	}
	//(*i)++;
	return (0);
}

//-----------------------------------------------------------------------------
//processes the raw input before it can be broken down into processes
//looks for syntax errors: invalid quotes, pipes, expansions, redirections
int	input_check(char *input)
{
	int		i;
	char	prev_c;

	i = 0;
	prev_c = '\0';
	while (input[i] != '\0')
	{
		while (ft_isspace(input[i]))
			i++;
		if (prev_c == '<' && input[i] == '>')
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
		else if (prev_c == '>' && input[i] == '<')
			return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `>'", 2), 1);
		prev_c = input[i];
		if ((input[i] == '\'' || input[i] == '"') && syntax_quotes(input, &i))
			return (1);
		else if (input[i] == '|' && syntax_multiple_pipes(input, &i))
			return (1);
		else if (input[i] == '$' && syntax_expansion(input, &i))
			return (1);
		else if (input[i] == '<' && syntax_re_in(input, &i))
			return (1);
		else if (input[i] == '>' && syntax_re_out(input, &i))
			return (1);
		if (input[i] != '\0')
			i++;
	}
	return (0);
}

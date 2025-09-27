/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 11:38:47 by mtice             #+#    #+#             */
/*   Updated: 2025/09/27 11:40:37 by mtice            ###   ########.fr       */
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
int	syntax_re_in(char *input, int *i)
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
	return ((*i)--, 0);
}

//-----------------------------------------------------------------------------
//checks for syntax errors after the '>' operator
//case 1: cat > (NULL) or cat >> (NULL) -> (newline error)
//case 2: cat >< or cat ><< -> (unexpected '<' or unexpected '<<')
//case 3: cat >>< or cat >><< -> (unexpected '<' or unexpected '<<')
int	syntax_re_out(char *input, int *i)
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
	return ((*i)--, 0);
}

//-----------------------------------------------------------------------------
//deals with the case where the $ is incorrectly used e.g. $$HOME
int	syntax_expansion(char *input, int *i)
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
int	syntax_multiple_pipes(char *input, int *i)
{
	int		j;
	int		w;
	int		r;

	j = 0;
	w = *i - 1;
	r = 0;
	while (w > 0
		&& (ft_isspace(input[w]) || input[w] == '<' || input[w] == '>'))
	{
		if (input[w] == '<' || input[w] == '>')
			r++;
		w--;
	}
	while ((input[*i] == '|' || ft_isspace(input[*i])) && input[*i] != '\0')
	{
		if (input[(*i)++] == '|')
			j++;
	}
	if (input[*i] == '\0' || j == 2 || r >= 1 || (w <= 0 && j == 1))
		return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `|'", 2), 1);
	else if ((w <= 0 && j > 1) || j > 2)
		return (ft_putstr_fd(SYNTAX, 2), ft_putendl_fd(" `||'", 2), 1);
	return (--(*i), 0);
}

//-----------------------------------------------------------------------------
//deals with unclosed quotes and pipes within quotes
//case 1: echo "hi -> unclosed double quotes
//case 2: echo 'hi -> unclosed single quotes
//case 3: echo "hello | world" or echo 'hello | world' -> pipe is substituted
//with ascii 26 (SUB) and later added back during tokenisation
int	syntax_quotes(char *input, int *i)
{
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
	return (0);
}

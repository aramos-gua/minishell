/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:59:44 by mtice             #+#    #+#             */
/*   Updated: 2025/08/10 00:14:09 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	check_var(t_token *tokens, int position, int process_nbr, char *env_var)
{
	int		i;
	int		len;
	char	*new_var;

	i = 0;
	printf("ENV_VAR: %s\n", env_var);
	while (env_var[i] != ' ' && env_var[i] != '\0')
		i++;
	if (env_var[i] == '\0')
		return ;
	while (env_var[i] != '\0')
	{
		len = 0;
		while (ft_isspace(env_var[i]) && env_var[i] != '\0')
			i++;
		while (!ft_isspace(env_var[i]) && env_var[i] != '\0')
			i++, len++;
		new_var = find_token(env_var, i--, len);
		if (!new_var)
			break ;
		tokens = add_at_pos(tokens, new_var, process_nbr, ++position);
		printf("POSITION: %d\n", position);
		//free(new_var);
		i++;
	}
}

static	void	expand_var(char **c_envp, char **env_var, int to_expand)
{
	int	i;
	int	j;
	int	k;
	char *temp = NULL;

	if (!to_expand)
		return ;
	i = 0;
	j = 0;
	k = 0;
	temp = *env_var;
	*env_var = ft_strjoin(*env_var, "=");
	free(temp);
	temp = *env_var;
	while (c_envp[j] != NULL)
	{
		i = 0;
		while (c_envp[j][i] != '=')
			i++;
		if (!ft_strncmp(c_envp[j], *env_var, ++i))
		{
			k = 1;
			*env_var = &c_envp[j][i];
		}
		j++;
	}
	if (k == 0)
		*env_var = ft_strdup("");
	free(temp);
}

//----------------------------------------------------------------------------------
//expansion inside quotes, i.e. there is a $ inside ""
//e.g. "$'HOME"
//TODO: handle this case: export a="cho hello"
//e$a (should give echo: builtin, hello: argument)
//handle heredoc expansions

char	*expansion(t_data *all, char *token, int position, int process_nbr)
{
	int		i;
	int		len;
	int		to_expand;
	char	*prev_env_var;
	char	*env_var;

	i = 0;
	env_var = NULL;
	while (token[i] != '\0')
	{
		len = 0;
		to_expand = 0;
		prev_env_var = env_var;
		if (token[i] == '$' && token[i + 1] == '?')
		{
			printf("UNIMPLEMENTED: return exit code (expansion)\n");
			return (NULL);
		}
		else if (token[i] == '$' && token[i + 1] == '\'')
		{
			i += 2, len++;
			while (token[i] != '\'' && token[i] != '\0')
				i++, len++;
		}
		else if (token[i] == '$' && token[i + 1] == '"')
		{
			i += 2, len++;
			while (token[i] != '"' && token[i] != '$' && token[i] != '\0')
				i++, len++;
		}
		else if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
		{
			i++;
			while (ft_isalpha(token[i]) || token[i] == '_')
				i++, len++;
			to_expand = 1;
		}
		else if (token[i] == '$' && token[i + 1] == '\0')
			return (ft_strjoin(prev_env_var, "$"));
		else if (token[i] == '\'')
		{
			i++;
			while(token[i] != '\'' && token[i] != '\0')
				i++, len++;
		}
		else if (token[i] != '$')
		{
			while (token[i] != '$' && token[i] != '\0')
				i++, len++;
		}
		env_var = find_token(token, i--, len);
		expand_var(all->c_envp, &env_var, to_expand);
		env_var = ft_strjoin(prev_env_var, env_var);
		i++;
	}
	check_var(all->tokens, position, process_nbr, env_var);
	return (env_var);
}

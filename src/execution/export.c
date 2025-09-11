/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:25:02 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/26 23:02:23 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i + 1);
	return (-1);
}

int	exist_in_arr(char *str, char **array, bool flag)
{
	int	len;
	int	i;

  i = 0;
  if (flag == true)
    len = ft_strlen(str) - 1;
  else
    len = ft_strlen(str);
  while (array[i])
  {
    if (ft_strncmp(str, array[i], len) == 0)
      return (i);
    i++;
  }
	return (-1);
}

char *nullify(char *cmd)
{
  int   len;
  char  *cmd_cut;

  len = var_len(cmd);
  cmd_cut = ft_substr(cmd, 0, len);
  return (cmd_cut);
}

void fill_exp(t_data *all)
{
    int i;

    i = 0;

    while (all->c_envp[i])
      i++;
    all->c_exp = ft_calloc((i + 1), sizeof(char *));
    if (!all->c_exp)
    {
      dprintf(2, "not posibile to aloc for c_exp\n");
    }
    i = 0;
    while (all->c_envp[i])
    {
      all->c_exp[i] = ft_strdup(all->c_envp[i]);
      i++;
    }
    all->c_exp[i] = NULL;
}

char  **update_exp(t_data *all, char *new_element, t_token *arg_node)
{
  char  **array;
  int   i;
  int   len;

  len = ft_strlen(new_element);
  i = exist_in_arr(new_element, all->c_exp, true);
  if (i != -1 && new_element[len - 1] == '=')
  {
    free(all->c_exp[i]);
    all->c_exp[i] = malloc(ft_strlen(arg_node->token) * sizeof(char));
    all->c_exp[i] = arg_node->token;
    return (all->c_exp);
  }
  i = 0;
  while (all->c_exp[i])
    i++;
  array = malloc((i + 2) * sizeof(char *));
  if (!array)
    return (NULL);
  i = 0;
  while (all->c_exp[i])
  {
    array[i] = all->c_exp[i];
    i++;
  }
  array[i++] = ft_strdup(arg_node->token);
  array[i] = NULL;
  return (array);
}

char  **update_envp(t_data *all, char *new_element, t_token *arg_node)
{
  char  **array;
  int   i;

  i = exist_in_arr(new_element, all->c_envp, false);
  if (i != -1)
  {
    free(all->c_envp[i]);
    all->c_envp[i] = malloc(1 * sizeof(char *));
    all->c_envp[i] = arg_node->token;
    return (all->c_envp);
  }
  i = 0;
  while (all->c_envp[i])
    i++;
  array = malloc((i + 2) * sizeof(char *));
  if (!array)
    return (NULL);
  i = 0;
  while (all->c_envp[i])
  {
    array[i] = all->c_envp[i];
    i++;
  }
  array[i++] = ft_strdup(arg_node->token);
  array[i] = NULL;
  return (array);
}

void  ft_putexp(char *str)
{
  int   i;

  i = 0;
  while (str[i] && str[i] != '=')
  {
    write(1, &str[i], 1);
    i++;
  }
  write(1, &str[i++], 1);
  write(1, "\"", 2);
  while (str[i])
  {
    if (str[i] == '\"')
        i++;
    write(1, &str[i], 1);
    i++;
  }
  ft_putendl_fd("\"", 1);
}

int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
  t_token *arg;
  char    *cmd_cpy;
	int		  i;

  if (all->c_exp == NULL)
    fill_exp(all);
  if ((ft_lstsize(all->tokens, proc)) == 1)
  {
    i = 0;
    while (all->c_exp[i] && all->c_exp[i][0] != '\0')
    {
      ft_printf("declare -x ");
      if (ft_strchr(all->c_exp[i], '='))
        ft_putexp(all->c_exp[i]);
      else
        ft_printf("%s\n", all->c_exp[i]);
      i++;
    }
    return (1);
  }
  arg = cmd_node->next;
  while (arg->type == ARGUMENT && arg->process_nbr == proc)
  {
    if (arg->token && (!ft_isalpha(arg->token[0]) && arg->token[0] != '_'))
    {
      ft_dprintf(2, "bash: export: \'%s\': not a valid identifier\n", arg->token);
      arg = arg->next;
      continue ;
    }
    cmd_cpy = nullify(arg->token);
    if (cmd_cpy[ft_strlen(cmd_cpy) - 1] != '=')
    {
      all->c_exp = update_exp(all, cmd_cpy, arg);
    }
    else
    {
      all->c_envp = update_envp(all, cmd_cpy, arg);
      all->c_exp = update_exp(all, cmd_cpy, arg);
    }
    arg = arg->next;
  }
  return (1);
}

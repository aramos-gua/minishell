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

int	exist_in_arr(char *str, char **array)
{
	int	len;
	int	i;

  i = 0;
  dprintf(2, "exist_in_arr start\n");
  dprintf(2, "str:[%s]\n", str);
  dprintf(2, "array[0]:[%s]\n", array[0]);
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
  dprintf(1, "var_len of [%s] is [%d]\n", cmd, len);
  cmd_cut = ft_substr(cmd, 0, len);
  return (cmd_cut);
}

void fill_exp(t_data *all)
{
    int i;

    i = 0;

    dprintf(2, "fill_exp STARTING\n");
    while (all->c_envp[i])
      i++;
    all->c_exp = malloc((i + 1), sizeof(char *));
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

char  **update_exp(t_data *all, char *new_element, t_token *cmd_node)
{
  char  **array;
  int   i;

  i = exist_in_arr(new_element, all->c_exp);
  if (i != -1)
  {
    dprintf(2, "replacing [%d]\n", i);
    free(all->c_exp[i]);
    all->c_exp[i] = cmd_node->next->token;
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
  array[i++] = ft_strdup(cmd_node->next->token);
  array[i] = NULL;
  return (array);
}

char  **update_envp(t_data *all, char *new_element, t_token *cmd_node)
{
  char  **array;
  int   i;

  i = exist_in_arr(new_element, all->c_envp);
  if (i != -1)
  {
    dprintf(2, "replacing [%d]\n", i);
    free(all->c_envp[i]);
    all->c_envp[i] = cmd_node->next->token;
    return (all->c_envp);
  }
  i = 0;
  while (all->c_envp[i])
    i++;
  dprintf(2, "array len is [%d]\n", i);
  array = malloc((i + 2) * sizeof(char *));
  if (!array)
    return (NULL);
  i = 0;
  while (all->c_envp[i])
  {
    array[i] = all->c_envp[i];
    i++;
  }
  array[i++] = ft_strdup(cmd_node->next->token);
  array[i] = NULL;
  return (array);
}

int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
	char	**array;
  char  *cmd_cpy;
	int		i;

  if (all->c_exp == NULL)
    fill_exp(all);
  else
    dprintf(2, "no need to fill_exp\n");
  if ((ft_lstsize(all->tokens, proc)) == 1)
  {
    i = 0;
    while (all->c_exp[i])
    {
      ft_printf("%s\n", all->c_exp[i]);
      i++;
    }
    return (1);
  }
  cmd_cpy = nullify(cmd_node->next->token);
  if (cmd_cpy[ft_strlen(cmd_cpy) - 1] != '=')
  {
    dprintf(2,"array is c_exp\n");
    array = update_exp(all, cmd_cpy, cmd_node);
    free(all->c_exp);
    all->c_exp = array;
    return (1);
  }
  else
  {
    dprintf(2,"array is c_envp\n");
    array = update_envp(all, cmd_cpy, cmd_node);
    free(all->c_envp);
    all->c_envp = array;
    array = update_exp(all, cmd_cpy, cmd_node);
    free(all->c_exp);
    all->c_exp = array;
    return (1);
  }
}

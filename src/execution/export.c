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

int	ft_export(t_data *all, int proc, t_token *cmd_node)
{
	char	**array;
  char  *cmd_cpy;
	int		len;
	int		i;

  if (!all->c_exp || all->c_exp[0] == '\0')
  {
    int j;

    j = 0;
    while (all->c_envp[j])
      j++;
    all->c_exp = calloc((j + 1), sizeof(char *));
    j = 0;
    while (all->c_envp[j])
    {
      all->c_exp[j] = all->c_envp[j];
      j++;
    }
    all->c_exp[j] = NULL;
  }
  if (ft_lstsize(all->tokens, proc) == 1)
  {
    int	j;

    j = 0;
    dprintf(2, "filling exp\n");
    while (all->c_exp[j] != NULL)
      printf("%s\n", all->c_exp[j++]);
  }
  cmd_cpy = nullify(cmd_node->next->token);
  if (cmd_cpy[ft_strlen(cmd_cpy) - 1] != '=')
    array = all->c_exp;
	array = all->c_envp;
	dprintf(2, "[%d]\n", proc);
	len = 1;
	i = 0;
  if (exist_in_arr(cmd_cpy, array) != -1)
  {
    dprintf(2, "coincidence found\n");
    i = exist_in_arr(cmd_cpy, array);
    dprintf(2, "found here [%d]\n", i);
    array[i] = cmd_node->next->token;
    return (1);
  }
  while (array[len])
    len++;
  array = NULL;
  array = malloc ((len + 2) * sizeof(char *));
  if (!array)
    return (0);
  if (cmd_cpy[ft_strlen(cmd_cpy) - 1] != '=')
  {
    while (all->c_exp[i])
    {
      array[i] = all->c_exp[i];
      i++;
    }
    //array[i - 1] = cmd_node->next->token;
    array[i] = NULL;
    //free(all->c_exp);
    all->c_exp = array;
    return (1);
  }
  while (all->c_envp[i])
  {
    array[i] = all->c_envp[i];
    i++;
  }
	array[i++] = cmd_node->next->token;
	array[i] = NULL;
	free(all->c_envp);
	all->c_envp = array;
	return (1);
}

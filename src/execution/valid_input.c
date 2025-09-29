
#include "../../inc/minishell.h"

int	valid_exp_arg(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str[0] == '=' || str[0] == '-' || ft_isdigit(str[0]) || str[0] == '+' || str[0] == '?')
		return (1);
	while (str[i] && (ft_isalpha(str[0]) || str[0] == '_'))
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]) && str[i] != '=')
			ret = 1;
		i++;
	}
	return (ret);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:49:48 by aalami            #+#    #+#             */
/*   Updated: 2023/04/06 21:44:45 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//  size_t	ft_strlen(const char *s)
// {
// 	size_t	size;

// 	size = 0;
// 	while (s[size] != '\0')
// 	{
// 		size++;
// 	}
// 	return (size);
// }
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*ptr;
// 	size_t	i;
// 	size_t	j;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	ptr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s1[i] != '\0')
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		ptr[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }

t_lst *sort_env(char **env)
{
	int i;
	int j;
	char *tmp;
	t_lst *exp;
    
	i = 0;
    exp = creat_list();
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			// printf("%s\n",env[j]);
			if (strcmp(env[i],env[j]) < 0)
			{
				tmp = strdup(env[i]);
				free (env[i]);
				env[i] = strdup(env[j]);
				free (env[j]);
				env[j] = strdup(tmp);
				free (tmp);
			}
			j++;
		}
		i++;
	}
	push_list(exp, env);
    return (exp);
}
int	if_key_exist(char *key, t_lst *lst)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return(1);
		tmp = tmp->next;
	}
	return (0);
}
void	update_value(char **split, t_lst *lst, char *str)
{
	t_node	*tmp;

	tmp = lst->top;
	while (tmp)
	{
		if (!ft_strcmp(split[0],tmp->key))
			break;
		tmp = tmp->next;
	}
	if (str)
		tmp->value = strdup(get_value(str));
	else
		tmp->value = strdup("\0");
}
void	add_key_with_value(t_lst *lst, char *str)
{
	char	**split;
	t_node *new;

	split = ft_split(str, '=');
	if (if_key_exist(split[0], lst))
		update_value(split, lst, str);
	else
		new = ft_new_node(split[0],get_value(str));
	ft_lstadd_back(lst, new);
}
void	add_key_with_no_value(t_lst *lst, char *str)
{
	char	**split;
	t_node	*new;

	split = ft_split(str, '=');
	if (if_key_exist(split[0], lst))
		update_value(split, lst, NULL);
	else
		new = ft_new_node(split[0],"\0");
	ft_lstadd_back(lst, new);
}
void	add_key(t_lst *exp, char *str)
{
	t_node	*new;
	if (!if_key_exist(str, exp))
	{	
		new = ft_new_node(str, NULL);
		ft_lstadd_back(exp, new);
	}
}
void	if_valid_identifier(char **arg, t_lst *exp)
{
	int	i;
	int	j;
	int invalid;

	i = 0;
	while (arg[i])
	{
		j = 0;
		invalid = 0;
		while (arg[i][j])
		{
			while ((arg[i][j] && arg[i][j] >= 95 && arg[i][j] <= 122) || (arg[i][j] >= 65 && arg[i][j] <= 90))
				j++;
			if(arg[i][j] == '=' && j!=0)
			{
				if (arg[i][j + 1])
					add_key_with_value(exp, arg[i]);
					
				else
					add_key_with_no_value(exp, arg[i]);
				j += ft_strlen(arg[i] + j + 1);
			}
			
			else if(arg[i][j] == '\0')
			{
				add_key(exp, arg[i]);
				break;
			}
			else
				invalid ++;
			j++;
		}
		if (invalid != 0)
			printf("bash: export: '%s': not a valid identifier\n", arg[i]);
		i++;
	}
}


// void	export_variable(t_command *cmd)
// {
	
// }

void	ft_export(t_command *cmd, t_lst *lst)
{
	t_node	*tmp;
	if (cmd->argc)
		if_valid_identifier(cmd->args, lst);
   else
   {
   	tmp = lst->top;
		while (tmp)
		{
			if (tmp->value == NULL)
			{
				if (!lst->flag)
					printf ("declare -x %s\n",tmp->key);
			}
			else	
				printf ("declare -x %s=\"%s\"\n",tmp->key, tmp->value);
			tmp = tmp->next;
		}
   }
	// else
	// {
	// 	// export_variable(cmd);
		
	// }
		
}
// int	main(int argc, char **argv, char **env)
// {
// 	t_node *tmp;
// 	t_lst *lst;
// 	char **ret = get_export_env(env);
// 	lst = sort_env(ret);
//    tmp = lst->top;
// 	while (tmp)
// 	{
// 		printf ("%s\n",tmp->data);
// 		tmp = tmp->next;
// 	}
// }
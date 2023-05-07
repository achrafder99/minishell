/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:49:48 by aalami            #+#    #+#             */
/*   Updated: 2023/05/06 14:38:34 by adardour         ###   ########.fr       */
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
			if (ft_strcmp(env[i],env[j]) < 0)
			{
				tmp = ft_strdup(env[i]);
				free (env[i]);
				env[i] = ft_strdup(env[j]);
				free (env[j]);
				env[j] = ft_strdup(tmp);
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
void	update_value(char **split, t_lst *lst, char *str, int flag)
{
	t_node	*tmp;

	tmp = lst->top;
	if (flag)
		split[0] = ft_strtrim(split[0], "+");
	while (tmp)
	{
		if (!ft_strcmp(split[0],tmp->key))
			break ;
		tmp = tmp->next;
	}
	if (str && flag)
	{
		if (tmp->value)
			tmp->value = ft_strjoin(tmp->value, get_value(str));
		else
			tmp->value = ft_strjoin("", get_value(str));
	}
	else if (str && !flag)
		tmp->value = strdup(get_value(str));
	else
		tmp->value = strdup("\0");
}
void	add_key_with_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;
	int		flag;

	flag = 0;
	if (ft_strchr(split[0], '+'))
	{
		split[0] = ft_strtrim(split[0], "+");
		flag = 1;
	}
	if (if_key_exist(split[0], lst))
		update_value(split, lst, str, flag);
	else
	{
		new = ft_new_node(split[0],get_value(str));
		ft_lstadd_back(lst, new);
	}
}

void	add_key_with_no_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;
	int	flag;

	flag = 0;
	if (ft_strchr(split[0], '+'))
	{
		split[0] = ft_strtrim(split[0], "+");
		flag = 1;
	}
	if (if_key_exist(split[0], lst))
		update_value(split, lst, NULL, flag);
	else
		{
			new = ft_new_node(split[0],"\0");
			ft_lstadd_back(lst, new);
		}
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
void	append_value(t_lst *lst, char *str, char **split)
{
	t_node	*new;

	// split[0] = ft_strtrim(split[0], "+");
	if (if_key_exist(ft_strtrim(split[0], "+"), lst))
	{
		// if (split[1])
			update_value(split, lst, str, 1);
		// else
		// 	add_key(lst, str);
	}
	else
	{
		if (!split[1])
			add_key_with_no_value(lst, str, split);
		else
			add_key_with_value(lst, str, split);
	}
}
int	if_valid_identifier(char **arg, t_env *env)
{
	int	i;
	int	j;
	int invalid;
	char	**split;
	int	flag;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		j = 0;
		invalid = 0;
		split = ft_split(arg[i], '=');
		while (arg[i][j])
		{
			while ((arg[i][j] && arg[i][j] >= 95 && arg[i][j] <= 122) || (arg[i][j] >= 65 && arg[i][j] <= 90))
				j++;
			if(arg[i][j] == '=' && j!=0)
			{
				if (arg[i][j + 1])
				{
					add_key_with_value(env->exp, arg[i], split);
					add_key_with_value(env->env, arg[i], split);
				}
					
				else
				{
					add_key_with_no_value(env->exp, arg[i], split);
					add_key_with_no_value(env->env, arg[i], split);
				}
				break;
				// printf("%d\n", j);
			}
			else if (arg[i][j] == '+' && arg[i][j + 1] == '=' && j!=0)
			{
				append_value(env->exp, arg[i], split);
				append_value(env->env, arg[i], split);
				break;
			}
			
			else if(arg[i][j] == '\0')
			{
				add_key(env->exp, arg[i]);
				break;
			}
			else
			{
				invalid ++;
				flag = 1;
				break;
			}
			j++;
		}
		if (invalid != 0)
			printf("bash: export: '%s': not a valid identifier\n", arg[i]);
		i++;
	}
	if (flag)
		return (1);
	else
		return (0);
}


// void	export_variable(t_command *cmd)
// {
	
// }
void *sort_exp_list(t_lst *exp)
{
	t_node *tmp_a;
	t_node *tmp_b;
	char	*tmp_key;
	char	*tmp_value;
	
	tmp_a = exp->top;
	while (tmp_a)
	{
		tmp_b= exp->top;
		while (tmp_b)
		{
			// printf("%s\n",env[j]);
			if (ft_strcmp(tmp_a->key,tmp_b->key) < 0)
			{
				tmp_key = ft_strdup(tmp_a->key);
				tmp_value = ft_strdup(tmp_a->value);
				free (tmp_a->key);
				free (tmp_a->value);
				tmp_a->key = ft_strdup(tmp_b->key);
				tmp_a->value = ft_strdup(tmp_b->value);
				free (tmp_b->key);
				free (tmp_b->value);
				tmp_b->key = ft_strdup(tmp_key);
				tmp_b->value = ft_strdup(tmp_value);
				free (tmp_key);
				free (tmp_value);
			}
			tmp_b = tmp_b->next;
		}
		tmp_a = tmp_a->next;
	}
}
int	ft_export(t_command *cmd, t_env *env)
{
	t_node	*tmp;
	t_lst	*lst;

	lst = env->exp;
	if (cmd->argc)
		return (if_valid_identifier(cmd->args, env));
   else
   {
	sort_exp_list(lst);
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
		return 0;
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

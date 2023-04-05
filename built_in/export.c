/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:49:48 by aalami            #+#    #+#             */
/*   Updated: 2023/04/05 19:46:48 by aalami           ###   ########.fr       */
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
void	add_key_with_value(t_lst *lst, char *str)
{
	char	*ptr;
	t_node *new;

	ptr = ft_strjoin("declare -x ","\"");
	ptr = ft_strjoin(ptr, str);
	ptr = ft_strjoin(ptr, "\"");
	new = ft_new_node(ptr);
	ft_lstadd_back(lst, new);
}
void	if_valid_identifier(char **arg, t_lst *exp)
{
	int	i;
	int	j;
printf("RRR");
	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j] && arg[i][j] >= 95 && arg[i][j] <= 122)
				j++;
		if(arg[i][j] == '=' && j!=0)
		{
			if (arg[i][j + 1])
			{	add_key_with_value(exp, arg[i]);
				return;}
			// {
			// 	printf("this is value :%s\n", arg[i] + j + 1);
			// 	return;
			// }
		}
			
		else if(arg[i][j] == '\0')
			printf("key with no value\n");
		else
			printf("bash: export: '%s': not a valid identifier\n", arg[i]);
		}
		i++;
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
		printf ("%s\n",tmp->data);
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
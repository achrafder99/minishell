/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalami <aalami@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/04/10 01:42:32 by aalami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *display_name(void)
{
    char *username;
    char *full_username;
    char *temp;
    char *dd;

    username = ft_strjoin(getenv("USER"), "@:");
    temp = username;
    if (temp == NULL)
        write(2, "Could not get username", ft_strlen("Could not get username"));
    dd = ft_strjoin(temp, " > ");
	free(username);
    return (dd);
}

char *get_input(void)
{
    char *input;
    char *full_username;
    char *tt;

    input = NULL;
    full_username = display_name();
    tt = ft_strjoin(full_username, "");
    input = readline(tt);
	free(full_username);
	free(tt);
    return (input);
}

void    process_input(char *input, t_env *env)
{
    t_components	*head;
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
    if (input == NULL)
    {
        write(1, " ", 1);
        write(1, "exit\n", 5);
        exit(0);
    }
    else if (strlen(input) == 0)
        return;
    head = NULL;
    add_history(input);
    lexer(input, &head, info,env);
    printf("%d\n",info->status_code);
	free_node(head);
	head = NULL;
}

int main(int argc, char **argv, char **envp)
{
    char *input;
    t_env   *env;

    env->env = get_env(envp);
	env->exp = get_export_env(envp);
    while (1)
    {
        input = get_input();
        process_input(input,env);
        free(input);
        input = NULL;
    }
    return (0);
}

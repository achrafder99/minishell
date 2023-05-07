/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/05/06 15:02:13 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int    number(char *string)
{
    int i;
    int flag_space;
    int count;
	
    i = 0;
    count = 0;
    flag_space = 0;
    while (string[i] != '\0')
    {
        if(string[i] == '\'' || string[i] == '\"')
        {
            while (string[i] != '\0' && (string[i] != '\'' || string[i] != '\"'))
            {
                count++;
                i++;
            }
        }
        while (string[i] != '\0' && string[i] != ' ')
        {
            count++;
            i++;
			if (string[i] == ' ')
			{
				count++;
				flag_space = !flag_space;
				break;
			}
        }
        if(string[i] == ' ' && !flag_space)
		{
            flag_space = !flag_space;
            count += 1;
        }
        if(string[i] == '\0')
            break;
        i++;
    }
    return (count);
}

char *restring(char *input,int allocation)
{
	int i;
	int j;
	int flag_space;
	char *restring;
	i = 0;
	j = 0;
	flag_space = 0;
	restring = malloc(sizeof(char)* allocation + 1);
	while (input[i] != '\0')
	{
		if(input[i] == '\'' || input[i] == '\"')
        {
            while (input[i] != '\0' && (input[i] != '\'' || input[i] != '\"'))
            {
                restring[j++] = input[i];
                i++;
            }
        }
        while (input[i] != '\0' && input[i] != ' ')
        {
			restring[j++] = input[i];
            i++;
			if (input[i] == ' ')
			{
				flag_space = !flag_space;
				break;
			}
        }
        if(input[i] == ' ' && flag_space)
		{
            flag_space = !flag_space;
            restring[j++] = input[i];
        }
        if(input[i] == '\0')
            break;
        i++;
	}
	restring[j] = '\0';
	return (restring);
}

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
    // printf("%d\n",info->status_code);
	// free_node(head);
	head = NULL;
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    char	*clear_input;

    t_env   *env;

    env = creat_env();
    env->env = get_env(envp);
	env->exp = get_export_env(envp);
    env->env_arr = NULL;
    while (1)
    {
        input = get_input();
		clear_input = restring(input, number(input));
        process_input(clear_input,env);
        // free(input);
        // input = NULL;
    }
    return (0);
}

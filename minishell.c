/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:52:42 by adardour          #+#    #+#             */
/*   Updated: 2023/04/16 21:22:19 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	sigint_handler(int sig)
// {
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	fflush(stdout);
// }

char	*display_name(void)
{
	char	*username;
	char	*full_username;
	char	*temp;
	char	*dd;

	username = ft_strjoin(getenv("USER"), "@:");
	temp = username;
	if (temp == NULL)
		write(2, "Could not get username", ft_strlen("Could not get username"));
	dd = ft_strjoin(temp, " > ");
	free(username);
	return (dd);
}

char	*get_input(void)
{
	char	*input;
	char	*full_username;
	char	*tt;

	input = NULL;
	full_username = display_name();
	tt = ft_strjoin(full_username, "");
	input = readline(tt);
	free(full_username);
	free(tt);
	return (input);
}

void	process_input(char *input, char **env)
{
	t_components	*head;
	t_info			*info;

	info = malloc(sizeof(t_info));
	if (!info)
		exit(1);
	if (input == NULL)
	{
		write(1, "", 1);
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (strlen(input) == 0)
	{
		free(info);
		return ;
	}
	head = NULL;
	add_history(input);
	lexer(input, &head, info, env);
	printf("%d\n", info->status_code);
}

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

char *remove_extra_spaces(char *text)
{
	int	count;
	count = number(text);
	return (restring(text,count));
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char *clear_input;

	// rl_catch_signals = 0;
	// signal(SIGINT, sigint_handler);
	while (1)
	{
		input = get_input();
		clear_input = remove_extra_spaces(input);
		process_input(clear_input, env);
		input = NULL;
	}
	return (0);
}

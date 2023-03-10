/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:49 by adardour          #+#    #+#             */
/*   Updated: 2023/03/10 21:18:43 by adardour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_length(char **numbers)
{
	size_t	length;

	length = 0;
	while (numbers[length] != NULL)
		length++;
	return (length);
}

void	print_string(char **argument, int flag)
{
	int	i;
	int	j;

	i = 1;
	if (flag)
		i = 2;
	while (!ft_strcmp(argument[i], "-n"))
		i++;
	while (argument[i] != NULL)
	{
		j = 0;
		while (argument[i][j] != '\0')
		{
			if (argument[i][j] == '\'' || argument[i][j] == '\"')
				j++;
			write(STDOUT_FILENO, &argument[i][j], 1);
			if (argument[i][j] == '\0')
				break ;
			j++;
		}
		i++;
		if (argument[i] != NULL)
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}

int	get_argument(char *input)
{
	char	**commands;
	int		length;

	length = 0;
	commands = ft_split(input, 32);
	while (commands[length] != NULL)
		length++;
	return (length);
}

void	parse_built_in(char *cmd)
{
	char	**command_line;
	char	*pwd;
	int		how_many_argument;
	char	*print_error;
    t_env *env;

	command_line = ft_split(cmd, 32);
    if(!ft_strcmp(command_line[0],"exit"))
        exit(EXIT_SUCCESS);
	else if (!ft_strcmp(command_line[0], "echo"))
	{
		if (!ft_strcmp(command_line[1], "-n"))
			print_string(command_line, 1);
		else
			print_string(command_line, 0);
	}
	else if (!ft_strcmp(command_line[0], "pwd"))
	{
		pwd = malloc(MAX_PATH_LENGTH);
		how_many_argument = get_length(command_line);
		if (how_many_argument > 1)
		{
			print_error = "too many arguments\n";
            write(STDERR_FILENO, command_line[0], ft_strlen(command_line[0]));
            write(1," :",2);
			write(STDERR_FILENO, print_error, ft_strlen(print_error));
			return ;
		}
		if (getcwd(pwd, MAX_PATH_LENGTH) != NULL)
		{
			write(STDOUT_FILENO, pwd, ft_strlen(pwd));
			write(1, "\n", 1);
		}
		else
			perror("");
		free(pwd);
	}
    else if(!ft_strcmp(command_line[0], "cd")){
        if(!ft_strcmp(command_line[1], "~"))
            chdir("/");
        else if(!access(command_line[1],F_OK))
            chdir(command_line[1]);
        else{
            write(STDERR_FILENO,command_line[0],ft_strlen(command_line[0]));
            write(2,": ",2);
            write(2,"no such file or directory",ft_strlen("no such file or directory"));
            write(2," :",2);
            write(2,command_line[1],ft_strlen(command_line[1]));
            write(2,"\n",1);
        }
    }
}

int	main(int c, char **argv, char **env)
{
	char *user_name;
	user_name = ft_strjoin(getenv("USER"), " ~$> ");
	while (1)
	{
		char *input;
		input = readline(user_name);
		add_history(input);
		parse_built_in(input);
		free(input);
	}
}
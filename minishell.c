/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adardour <adardour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:13:49 by adardour          #+#    #+#             */
/*   Updated: 2023/03/11 17:54:18 by adardour         ###   ########.fr       */
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
	int		i;
	int		j;
	char **expend;
	char	*value;

	i = 1;
	if (flag)
		i = 2;
	if (strchr(argument[i], '$'))
	{
		expend = ft_split(argument[i], '$');
		int length;
		length = get_length(expend);
		if (length == 1)
		{
			value = getenv(expend[0]);
			write(1, value, ft_strlen(value));
			if (!flag)
				write(1, "\n", 1);
		}
		else
		{
			value = getenv(expend[length]);
			write(1, expend[0], ft_strlen(expend[0]));
			write(1, value, ft_strlen(value));
			if (!flag)
				write(1, "\n", 1);
		}
		return ;
	}
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

void	parse_built_in(char *cmd,char **env)
{
	char	**command_line;
	char	*pwd;
	int		how_many_argument;
	char	*print_error;
	char *home_dir;

	command_line = ft_split(cmd, 32);
	if (!ft_strcmp(command_line[0], "exit"))
		exit(EXIT_SUCCESS);
	else if (!ft_strcmp(command_line[0], "echo"))
	{
		if (command_line[1] == NULL)
		{
			write(1, "\n", 1);
			return ;
		}
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
			write(1, " :", 2);
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
	else if (!ft_strcmp(command_line[0], "cd"))
	{
		if (get_length(command_line) == 1)
		{
			home_dir = ft_strjoin("/home/", getenv("USER"));
			chdir(home_dir);
			return ;
		}
		else if (!ft_strcmp(command_line[1], "~"))
		{
			home_dir = ft_strjoin("/home/", getenv("USER"));
			chdir(home_dir);
			return ;
		}
		else if (!access(command_line[1], F_OK))
			chdir(command_line[1]);
		else
		{
			write(STDERR_FILENO, command_line[0], ft_strlen(command_line[0]));
			write(2, ": ", 2);
			write(2, "no such file or directory",
					ft_strlen("no such file or directory"));
			write(2, " :", 2);
			write(2, command_line[1], ft_strlen(command_line[1]));
			write(2, "\n", 1);
		}
	}
	else if(!ft_strcmp(command_line[0], "export"))
	{
		if(get_length(command_line) == 1)
			display_env(env);
	}
}

int	check_if_buillt_in(char *cmd)
{
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void not_built_in(char *cmd)
{
	int pid = fork();
	if (pid == 0) {
		char *args[] = { "/usr/bin/", "-c", cmd, NULL };
		char *env[] = { NULL };
		execve("/bin/sh", args, env);
		perror("execve");
		exit(EXIT_FAILURE);
	} 
	else if (pid < 0)
		perror("fork");
	else 
		wait(NULL);
}

char * trim(char *s) {
    int len = strlen(s);
    char *start = s;
    char *end = s + len - 1;
	char *result;

    while (isspace(*start)) {
        start++;
    }
    while (end > start && isspace(*end)) {
        end--;
    }
    *(end+1) = '\0';

    if (start != s) {
        memmove(s, start, (end - start) + 2);
    }
	return (strdup(s));
}

void start_redirections(char *cmd,char *tokens)
{
	char **files;
	char **commands;
	commands = ft_split(cmd,'>');
	files = ft_split(tokens,'>');

	int i;
	int fd;
	i = 0;
	char *token = strtok(tokens, ">");

    while (token != NULL) {
		fd = open(trim(token), O_RDWR | O_CREAT , 0777);
		if(fd == -1)
		{
			perror("");
			return;
		}
		dup2(fd, STDOUT_FILENO);
        token = strtok(NULL, ">");
		close(fd);
    }
}

int	main(int c, char **argv, char **env)
{
	char *user_name;
	user_name = ft_strjoin(getenv("USER"), " ~$> ");
	char *start;
	while (1)
	{
		char *input;
		char **commands;
		input = readline(user_name);
		commands = ft_split(input, ' ');
		if(ft_strchr(input,'>'))
		{
			start = ft_strchr(input,'>');
			start_redirections(input,start);
		}
		else if (check_if_buillt_in(commands[0]))
			parse_built_in(input,env);
		else
			not_built_in(input);
		free(input);
		add_history(input);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:45:34 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/23 16:04:00 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_value(char *key, t_data *data)
{
	t_envp_list	*list;

	if (strs_are_equal(key, "?"))
		return (ft_itoa(data->status));
	list = data->envp_list;
	while (list && !strs_are_equal(key, list->key))
		list = list->next;
	if (list)
		return (list->value);
	return ("");
}

static char	*get_key(char *str, int *i, int fd)
{
	char	*key;
	int		start;

	start = *i;
	*i += 1;
	if (in_charset(str[*i]) || str[*i] == '=')
	{
		ft_putstr_fd("$", fd);
		return (ft_strdup(""));
	}
	if (str[*i] == '?')
		*i += 1;
	else
		while ((ft_isalnum(str[*i]) && ft_isalpha(str[start + 1]))
			|| (ft_isdigit(str[*i]) && ft_isdigit(str[start + 1])))
			*i += 1;
	key = ft_substr(str, start + 1, *i - start - 1);
	if (!key)
		return (0);
	return (key);
}

static void	print_here_doc_input(t_data *data, char *input, int fd)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '$')
		{
			key = get_key(input, &i, fd);
			if (!key)
				return ((void) print_error("Malloc error"));
			value = get_value(key, data);
			if (!value)
				return (free(key), (void) print_error("Malloc error"));
			ft_putstr_fd(value, fd);
			if (strs_are_equal(key, "?"))
				free(value);
			if (key)
				free(key);
		}
		else
			ft_putchar_fd(input[i++], fd);
	}
}

int	here_doc(t_data *data, t_cmd *cmd, char *here_doc)
{
	char	*input;
	int		fd[2];

	(void) data;
	input = NULL;
	if (!here_doc || pipe(fd) < 0)
		return (-1);
	input = readline("> ");
	while (input && !strs_are_equal(input, here_doc))
	{
		print_here_doc_input(data, input, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(input);
		input = readline("> ");
	}
	free(input);
	close(fd[1]);
	cmd->fd_in = fd[0];
	return (1);
}

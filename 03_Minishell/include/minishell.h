/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angcampo <angcampo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:37:54 by angcampo          #+#    #+#             */
/*   Updated: 2024/08/23 17:09:32 by angcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "command.h"
# include "token.h"
# include "command.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/ioctl.h>

typedef struct s_data
{
	char				*built_in_cmd[8];
	int					status;
	int					exit;
	char				**envp;
	int					*pipe_fds;
	t_export_list		*export_list;
	t_envp_list			*envp_list;
	t_token_list		*token_list;
	t_cmd_list			*cmd_list;
	t_cmd				*current_cmd;
}						t_data;

extern int		g_pack;

void			parse_variables(char *line);
/*
-----------------------------
UTILS
-----------------------------
*/

/*
Prints "Error\n" then prints str with another \n if str isn't empty
@param str
@return 0
*/
int				print_error(const char *str);

/*
Returns an initialized t_data if everything went ok,
returns NULL if not.
@param envp
@return int
*/
t_data			*get_initialized_data(char **envp);

/*
Liberates all data from the struct
*/
void			free_data(t_data *data);

/*
Compares 2 strings
@return 1 if equal, 0 if not
*/
int				strs_are_equal(char *str1, char *str2);

/*
@brief Inits console
*/
void			console_initialization(t_data *data);

/*
Updates the data->envp from the data->envp_list
*/
int				update_envp(t_data *data);

//utils_export_list.c

void			print_export_list(t_data *data);

t_export_list	*get_export_list_node(char *str);

t_export_list	*add_export_sorted(t_export_list *current, t_export_list *new);

t_export_list	*get_export_list(char **envp);

void			free_export_list(t_export_list *current);

/*
-----------------------------
PARSE/TOKENS
-----------------------------
*/

//add_tokens_from_input.c

/*
It iterates through all the input string to add tokens
Returns 1 if ok
and returns 0 if not
@param data Fully initialized
@param input Any string
*/
int				add_tokens_from_input(t_data *data, char *input);

/*
-----------------------------
PARSE/LEXER
-----------------------------
*/

//validators_utils.c

/*
Given a token type, checks if it's a redirection or not
@return 1 if a redirection, 0 if not
*/
int				is_redir(int type);

/*
Gets the next or previous token that is not a white space
@param next 1 if next token, 0 if previous token
*/
t_token			*skip_spaces(t_token *token, int next);

//valid_token_list.c

/*
It iterates through all the token list to see if there are
any syntax errors.
@return 1 if syntax is ok, 0 if not
*/
int				valid_token_list(t_token_list *list);

/*
-----------------------------
PARSE/EXPANDER
-----------------------------
*/

/*
@param token with type ENV
@return value of the variable if it exists, empty string
if it doesn't
*/
char			*expanded_token(t_token *token, t_data *data);

/*
-----------------------------
PARSE/COMMANDS
-----------------------------
*/

//add_commands_from_input.c

/*
Adds tokens from input, returns 1 if ok
and returns 0 if not
@param data Fully initialized with tokens
*/
int				add_commands_from_input(t_data *data);

//get_arg.c

/*
Returns a word from a combination of tokens from the token list.
Used for get_args and get_redir_list.
@param token double pointer so pointer can be modified
@param data to expand the variables
*/
char			*get_arg(t_token **token, t_data *data);

//get_lists.c

/*
Fills the args + the redirection list
@param token double pointer so pointer can be modified
@param data to expand the variables
*/
void			get_lists(t_token **token, t_data *data, char **args,
					t_redir_list *redir_list);

/*
-----------------------------
PARSE/REDIRECTIONS
-----------------------------
*/

/*
Handles all redirections of the command list of data
@param data with a complete list of commands
@return 1 if ok, 0 if not
*/
int				handle_redirections(t_data *data);

/*
Handles the redirection
*/
int				handle_redir(t_data *data, t_cmd *cmd, t_redir *redir);

/*
Handles the heredoc
*/
int				here_doc(t_data *data, t_cmd *cmd, char *here_doc);

/*
-----------------------------
PIPEX
-----------------------------
*/
//pipex.c

/**
 @brief Executes all the commands in the linked list of commands.

 @details The function goes through the linked list of commands and executes
 each one of them in order. It sets the status of the data structure to the
 return value of the last command executed, and sets the exit value to 0, so
 that the shell does not exit after executing the commands.

 @param data The data structure containing the linked list of commands.

 @return EXIT_SUCCESS.
*/
int				ft_pipex(t_data *data);

/**
 @brief Executes a command in a child process.

 @param data The data structure containing all the data needed to execute a
 command.
 @param cmd_count The index of the command in the command list.
 @return The exit status of the command.
 */
int				ft_exec_cmd(t_data *data, int cmd_count);

/**
 This function is a wrapper for the fork system call. It creates a new process
 by duplicating the calling process. The new process, referred to as the child
 process, is an exact copy of the calling process. The parent process, referred
 to as the parent, and the child process continue to run concurrently.

 @param data The data structure containing all the necessary information for
 the child process.
 @param cmd_count The index of the current command being executed.

 @return The exit status of the child process.
 */
int				ft_fork(t_data *data, int cmd_count);

/**
 @brief Execute a command as a child process.

 This function forks, then in the child process:
 1. Get the absolute path of the command to be executed using the PATH
    environment variable.
 2. Redirect the standard input and output according to the redirection
    symbols found in the command.
 3. Execute the command with the execve system call.
 4. If the command cannot be executed, free the absolute path, set the exit
    status to EXIT_FAILURE, redirect the standard input and output back to
    their original values, and exit with the exit status.
 @param data The data structure containing the environment variables.
 @return The exit status of the command.
 */
int				ft_child_process(t_data *data);

//pipex_utils.c

/**
 @brief Redirige fd a std, y cierra fd original si es diferente a UNDEF_FD
 y diferente a std.

 @param fd Descriptor de fichero a redirigir.
 @param std Descriptor de fichero est ndar a redirigir (STDIN, STDOUT, STDERR).
 @param fd2 Descriptor de fichero que se va a redirigir.
 */
void			ft_redir_fd_std(int fd, int std, int fd2);

/**
 Executes a built-in command.

 @param data The data structure containing the command to be executed.
 @return The exit status of the executed command.
 */
int				ft_exec_builtin(t_data *data);

/**
 Resolves a command path to an absolute path.

 @param cmd The command to resolve the path for.
 @param envp An array of environment variables.
 @return The absolute path of the command, or a copy of the original path
  if it is already absolute.
 */
//char	*resolve_absolute_path(char *cmd, char **envp)

/*
-----------------------------
PATH_UTILS/PIPEX
-----------------------------
*/

/**
 Retrieves an array of strings representing the paths to executable directories.

 @param envp An array of environment variables.
 @return An array of strings representing the paths to executable directories.
 	Returns NULL if the environment variable is not found
	or if there is an error.
 */
char			**get_paths(char *envp[]);

/**
 Searches for an absolute or relative binary path.

 @param cmd The command to search for.
 @param envp An array of strings containing the environment variables.

 @return The absolute path of the binary if found, NULL otherwise.

 @throws None.
 */
char			*abs_bin_path(char *cmd, char **envp);

/**
 ft_valid_cmd - checks if a command can be executed by the user

 @cmd: the command to check

 Returns: the command if it can be executed, NULL otherwise

 Description: This function checks if a command can be executed by the user.
 It first checks if the file exists using the access() function with the
 F_OK flag. If it does, it then checks if the file is executable using the
 access() function with the X_OK flag. If the file is not executable, it
 prints an error message using perror() and returns the command. If the file
 is executable, it returns the command. If the file does not exist, it simply
 returns the command.
 */
char			*ft_valid_cmd(char *cmd);

/**
 Frees a matrix of strings, typically used to represent the environment
 variables, and sets the pointer to NULL.

 @param envp a matrix of strings
 */
void			ft_free_matrix(char **envp);

/*
-----------------------------
BUILD-INS
-----------------------------
*/

//cd.c
/**
 The cd function changes the current directory of the shell.

 @param data The shell data structure containing the environment variables.
 @return 0 if the directory was changed successfully.
 */
int				cd(t_data *data);

//echo.c
/**
 echo - prints the arguments to the standard output

 @param data t_data* pointer to the main struct

 @return int EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int				echo(t_data *data);

//env.c
/**
 ft_env - prints all environment variables

 @data: global data

 Return: void
 */
void			ft_env(t_data *data);

/**
 Executes the `env` command.

 @param data The t_data struct containing information about the program state.

 @return Returns 0 on success, 1 if the number of arguments is incorrect,
 or if the command is invalid.
 */
int				env(t_data *data);

//exit.c
/**
 ft_exit - exits the shell
 @data: structure containing all the information about the shell
 Return: EXIT_SUCCESS
 Description: sets data->exit to 1, prints "Bye\n" to stdout, and returns
 EXIT_SUCCESS
 */
int				ft_exit(t_data *data);

//export.c
/**
 Exports a variable to the environment.

 The variable is exported in the environment in the form
 "KEY=VALUE".

 @param data The data structure containing the information
             about the shell.

 @return 0 on success, 1 on failure.
 */
int				ft_export(t_data *data);

//pwd.c
/**
 ft_pwd: Returns the current working directory.

 @data: Global data structure.

 @return: 0 on success, 1 on failure.
 */
int				ft_pwd(t_data *data);

//unset.c
/**
 ft_unset: removes the given environment variables from the data struct.

 @data: the data struct containing the environment variables.

 Returns EXIT_SUCCESS.
 */
int				ft_unset(t_data *data);

/*
-----------------------------
SIGNALS
-----------------------------
*/
//signal.c
/**
 @brief Set up signal handlers for SIGINT, SIGTSTP, and SIGQUIT.

 SIGINT is handled by ctr_c, which prints a newline and redisplays the
 prompt. SIGTSTP and SIGQUIT are set to be ignored.

 This function is called during initialization to set up signal handling.
 */
void			ft_signals(void);

#endif

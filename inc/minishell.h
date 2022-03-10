/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esylva <esylva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:07:13 by crobot            #+#    #+#             */
/*   Updated: 2022/03/09 18:50:38 by esylva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* used libraries	*/

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

/*	colours	*/

# define BLACK		"\001\033[1;90m\002"
# define RED		"\001\033[1;91m\002"
# define GREEN		"\001\033[1;92m\002"
# define YELLOW		"\001\033[1;93m\002"
# define BLUE		"\001\033[1;94m\002"
# define PURPLE		"\001\033[1;95m\002"
# define WHITE		"\001\033[1;97m\002"
# define RESET		"\001\033[0m\002"

/*	error codes	*/

# define OK					0
# define ERROR				-1
# define ER_MALLOC			3
# define ER_FILE_OPEN		1
# define ER_SYNTAX			258
# define COMNOT				127
# define ER_PREPARSER		259
# define TRUE				-10
# define FALSE				-20
# define R_OUT				100
# define R_OUT_APPEND		101
# define R_IN				102
# define R_HEREDOC			103
# define R_FALSE			104

/*	error messages	*/

# define W_SYNTAX		"minishell: syntax error\n"

/*	data struct	*/

typedef struct s_cmd
{
	char			**arg;
	int				fd_in;
	int				fd_out;
	int				arg_num;
	int				*pipe_in;
	int				*pipe_out;
	int				redir_flag;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	char			*line;
	t_env			*env;
	char			**envar;
	int				pipe;
	int				ret_val;
	int				status;
	pid_t			*pid;
	t_cmd			*cmd;
	t_cmd			*first_cmd;
}	t_data;

typedef struct s_ts
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
}	t_ts;

/*		YOU'RE ENTERING THE EXE DIRECTORY FUNCTION LIST!	*/

/*		ft_exec_utils	*/
char	*ft_take_path(t_data *data);
char	*ft_check_dir(t_data *data, char **sp_path);

/*		ft_execute		*/
int		ft_exec_built_in(t_data *data);
void	ft_exec_bin(t_data *data);
void	ft_exec_pipe(t_data *data);
void	ft_execute(t_data *data);

/*		ft_pipe_work	*/
void	start_pipe(int *fd, t_data *data);
void	end_pipe(int *fd, t_data *data);
void	child_process(t_data *data, int **fd, int i);
void	ft_pipe_work(t_data *data);
void	ft_redir_pipe(t_data *data);

/*		ft_run_cd		*/
void	ft_run_cd(t_data *data);
void	ft_oldpwd(t_data *data, char *tmp_val);
void	ft_cd_home(t_data *data);
void	ft_cd_oldpwd(t_data *data);
void	ft_chk_arg(t_data *data, char *val);

/*		ft_run_echo		*/
void	ft_run_echo(t_data *cmd);
void	ft_write_echo(t_data *data);

/*		ft_run_env		*/
void	ft_run_env(t_data *cmd);
int		wr_fd(int fd, char *str, int len, t_data *data);
void	ft_env_error(t_data *data);

/*		ft_run_export	*/
void	ft_run_export(t_data *data);
void	ft_empty_export(t_data *data);
void	ft_run_export1(t_data *data, char *key, char *value);
void	ft_run_export2(t_data *data, char *key, char *value);
int		ft_do_export(t_data *data, char *key, char *value);

/*		ft_run_pwd		*/
void	ft_run_pwd(t_data *cmd);

/*		ft_run_unset	*/
void	ft_run_unset(t_data *data);

/*		ft_run_exit		*/
void	ft_run_exit(t_data *data);
void	ft_exit(t_data *data, int i);

/*		YOU'RE LEAVING THE EXE DIRECTORY FUNCTION LIST!	*/

/*		YOU'RE ENTERING THE PARS DIRECTORY FUNCTION LIST!	*/

/*		ft_dollar_handler	*/
char	*ft_digit_handler(char *line, int *i, int j);
char	*ft_query_handler(char *line, int *i, int status);
char	*ft_key_extractor(char *line, char **env, int len);
char	*ft_dollar_handler2(char *line, int *i, int j, char **env);
char	*ft_dollar_handler(char *line, int *i, char **env, int status);

/*		ft_parse_aid	*/
int		ft_is_empty(char c);
int		ft_special_symbol(char c, int i, int j);
int		ft_space_skipper(char *line, int *i);
char	*ft_no_key(t_ts ts, int *i, int j);

/*		ft_parser	*/
int		ft_symbol_handler(t_data *data, char **line, int *i, int *j);
int		ft_parser_util(t_data *data, char **line, int *i, int *j);
int		ft_get_com_args(t_data *data, char *line, int *i, int *j);
int		ft_pipe_exist(char *line, int *i, int *j);
int		ft_parser(t_data *data, char **line);

/*		ft_pipe_handler	*/
void	ft_pipe_handler(t_data *data, char *line, int *i, int *j);

/*		ft_preparser	*/
int		ft_scan_pipe(t_data *data, char *line, int start, int finish);
int		ft_check_pipe(t_data *data, char *line);
char	*ft_check_quotes(t_data *data, char *line);
char	*ft_check_redirect(t_data *data, char *line);
int		ft_preparser(t_data *data, char *line);

/*		ft_quotes_handler	*/
char	*ft_quote_skipper(char *str, int *i, int j);
char	*ft_quote_handler(char *line, int *i);
char	*ft_2quotes_handler(char *line, int *i, char **env, int status);

/*		ft_redirect_handler	*/
int		ft_check_redir_arg(char *arg);
int		ft_redir_opener(t_data *data, char *redir_arg, int empty_flag);
int		ft_redir_finder(int *redir_flag, char *line, int *i);
char	*ft_redir_symbol(t_data *data, char *line, int *i);
void	ft_redir_handler(t_data *data, char **line, int *i, int *j);

/*		ft_redirect_handler2 */
int		ft_redirect_out(t_data *data, char *file_name);
int		ft_redirect_out_append(t_data *data, char *file_name);
int		ft_redirect_in(t_data *data, char *file_name);

/*		ft_redirect_handler3 */
int		ft_rewrite_strnstr(char *stop_word, char *text);
void	ft_put_in_fd(int fd, char *stop_word);
int		ft_heredoc(t_data *data, char *stop_word);

/*		YOU'RE ENTERING THE UTILZ DIRECTORY FUNCTION LIST!	*/

/*		ft_env_I	*/
char	*find_value(t_data *data, char *key);
t_env	*find_env(t_data *data, char *key);
int		ft_split_env(char *param, char **key, char **value);
int		ft_split_env_m(char *param, char **key, char **value);

/*		ft_env_II	*/
int		ft_update_env(t_data *data);
int		ft_cycle(t_env *tmp, char **arr, int i, t_data *data);
int		ft_size_of_env(t_env *env);
char	*ft_new_str_env(t_env *env);
char	**ft_new_envar(char **arr, t_data *data);

/*		ft_init	*/
void	ft_init_pid(t_data *data);
t_cmd	*ft_cmd_init(void);
t_env	*ft_init_env(t_data *data, char **env);
int		**ft_init_fd(int **fd, int count_pipe);
void	ft_init(t_data *data, char **env);

/*		ft_list	*/
t_env	*ft_lstnew(t_data *data);
void	ft_lstadd_back(t_env *new, t_data *data, char *key, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst);
void	ft_lstclear(t_env **lst);

/*		ft_pid	*/
void	signal_handler(int sig);
void	child_signal_handler(int signo);
void	ft_add_pid(pid_t *pid, pid_t pid_value);
void	ft_wait_pid(t_data *data);

/*		ft_put_prompt	*/
char	*ft_get_dir(t_data *data);
char	**ft_log_env(int ac, char **argv, char **env);
char	*ft_get_env(char *prm, char **env);
char	*ft_put_prompt(t_data *data);

/*		ft_free	*/
char	**free_2d_arr(char **p);
void	ft_free_at_exit(t_data *data);
void	ft_free_key_value(char **key, char **value);
char	*free_ts(t_ts ts);

/*		ft_utilz_I	*/
int		ft_iskey(char *key, t_data *data);
size_t	len_2d_arr(char **arr);
char	**ft_arr_plus(char **arr, char *str);
int		ft_isall_digits(char *str);
long	ft_atol(char *str);

/*		ft_utilz_II	*/
t_ts	ft_write_ts(char *line, int *i, int j);
void	ft_3sfd(char *s1, char *s2, char *s3, int fd);
int		**malloc_2d_int(size_t size);
void	ft_cd_error(t_data *data);
int		cd_utils(t_data *data);

/*		YOU'RE LEAVING THE UTILZ DIRECTORY FUNCTION LIST!	*/

/*		MINISHELL	*/
void	ft_error(t_data *data, int err_num);
void	minishell(t_data *data);
int		main(int ac, char **av, char **env);

#endif

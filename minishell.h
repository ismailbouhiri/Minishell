/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouhiri <ibouhiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:32:40 by ibouhiri          #+#    #+#             */
/*   Updated: 2020/12/13 14:31:04 by ibouhiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include "Utils/get_next_line.h"

# define COMMAND 1
# define STRING	2
# define PIPE 3
# define REDIRECTION_RIGHT 4
# define REDIRECTION_LEFT 5
# define DOUBLE_REDICTION 6
# define POINT_VIRGULE 7
# define FILE 9

typedef struct	s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}				t_nod;

typedef struct	s_cmd
{
	char			*cmd;
	int				what;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_srt
{
	char			*key;
	char			*value;
	struct s_srt	*next;
}				t_sorted;

struct			s_var
{
	int			double_quote;
	int			single_quote;
	int			cmd;
	int			skip_slash;
	int			pipe;
	int			point_virgule;
	int			rediction_left;
	int			rediction_right;
	int			doulbe_rediction;
	int			double_slash;
	int			i;
	int			directions;
	int			command;
	char		*path;
	t_cmd		*tmp;
	int			save;
}				t_var;

struct			s_p
{
	int			count_pipes;
	int			reti;
	int			**fd;
	int			ispipeinfront;
	int			ispipebehind;
	int			ispvbehind;
	pid_t		pid;
	int			waits;
	int			k;
	int			i;
	int			u;
}				t_pipe;

struct			s_m
{
	char		*line;
	char		*backup;
	int			ret;
}				t_main;

t_nod			*g_new;
t_nod			*g_head;
t_cmd			*g_hcmd;
t_cmd			*g_hnew;
t_sorted		*g_shead;

int				g_in;
int				g_out;
int				g_isin;
int				g_isout;
int				g_canidup;

int				g_erreur;
int				g_command;
int				g_saveout;
int				g_savein;
int				g_ifin;
int				g_stillexec;
int				g_ctrl_c;
int				g_issort;
int				g_count;
int				g_count2;
size_t			g_linelen;
int				g_s;

int				g_j;
int				ft_count(unsigned int n);
int				count_char(char *chars, char c);
int				count_word(char const *s, char c);
char			**ft_free(char *str, int i, char **ptr);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*conv(char *ptr, unsigned int s, int i, int c);
int				ft_isalnum(int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *s1);
void			ft_collecte_env(char **env);
void			ft_lstadd_back(t_nod **head, t_nod *new);
t_nod			*ft_lstnew(char *key, char *value);
void			ft_print_nod(void);
void			ft_add_env(char *line);
void			ft_delete_nod(char *line);
char			*ft_find_value_env(char *key);
t_cmd			*ft_lstnew_cmd(char *str, int what);
void			ft_lstadd_back_cmd(t_cmd **head, t_cmd *new);
void			parser(char *line);
int				check(char *tab);
void			ft_step1(char *line);
void			ft_condition(char *tmp, int i);
void			ft_tableau(char *tab, char *tmp, int *i);
void			ft_link(char *ptr);
void			ft_step2(t_cmd	*tmp);
void			ft_dollar(char *tab, t_cmd *tmp);
void			free_lst(void);
int				simple_cout(t_cmd *tmp, char *tab, int *i);
int				double_cout(t_cmd *tmp, char *tab, int *i);
int				replace_dollar(char *cmd, char *tab, int *i);
int				ft_countinue(char *cmd, int *i);
char			*trim_space(char *cmd);
void			free_nod(void);
void			err_dec(void);
void			ft_rename_file(void);
void			rm_empty_nod(void);
void			err_dir(void);
void			ft_corrector(void);
void			ft_inis(void);
int				ft_ret(char *tab, int *i);
int				ft_normi(char *tab, char *tmp, int *i);
void			ft_fixdirections(t_cmd *cmd, t_cmd *firstredir);
void			ft_cmdorg(void);
void			ft_addstr(t_cmd *firstcmd, t_cmd *firstredir);
void			ft_swapcmd(t_cmd *cmd, t_cmd *firstcmd, t_cmd *firstredir);
void			ft_command_var(t_cmd *findcmd, t_cmd **firstcmd,
				t_cmd **firstredir);
void			ft_norm(t_cmd *firstcmd, t_cmd *firstredir,
				t_cmd *cmd, t_cmd *copycmd);
int				ft_strcmp(char *s1, char *s2);

int				ft_check_key(char *ptr);
void			add_back(t_sorted *ptr);
void			free_shead();
void			dup_it(void);
void			ft_norminetteexit(void);
void			override_line(char **env);

void			println(int key);
void			send_to_entry(char **env);
void			prompt(char **env);
int				ft_check_equal_2(char *str);

void			echo(t_cmd *tmp);
void			help_echo(t_cmd *tmp);
void			help_echo2(t_cmd *tmp);
int				ft_lstsize(t_cmd *lst);

int				count_cmd();
int				check_pipe(int start);
int				beforepipe(int max);
int				ft_lstcountpipe(int k);
void			help_lstcountpipe(t_cmd **lst, int k);

int				help_sort_shead(t_sorted	*tmp, t_sorted	*n, int acce);
void			export(t_cmd *tmp);
void			fill(char *key, char *value);
void			sort_shead();
void			copy_list();

int				entry(char **env);
int				pipes(char **env);
void			pipes_2(void);
int				pipes_3(char **env);
int				pipes_4(char **env);

void			pipes_5(void);
void			allocate_pipe(int k);
int				checkpv(int max);
void			free_old();
void			ft_strcpy_dollar(char *dst, char *src);

void			swap_data(struct s_srt *a, struct s_srt *b);
void			ft_print_shead(void);
int				ft_check_equal(char *str);
void			launch_it(char *path, t_cmd *cmd, char **env);
void			launch_it2(char *path, char **args, char **env);

int				execute(char **env, int start);
int				execute_2(t_cmd *tmp);
int				execute_commands(t_cmd *tmp, char **env);
void			execute_unset(t_cmd *tmp);
int				execute_pwd(void);

int				execute_cd(t_cmd *tmp);
void			direct(t_cmd *tmp);
void			direct_r_a(t_cmd *tmp);
int				direct_r_a_2(t_cmd *p, int fd);
int				direct_r_a_3(t_cmd *p, int fd);

int				direct_l(t_cmd *p);
int				direct_l_2(t_cmd *p);
int				count_r_a(t_cmd *tmp);
int				count_l(t_cmd *tmp);
int				path_exist(void);

void			search_it(t_cmd *cmd, char **env);
void			search_it2(char *path, t_cmd *cmd, int fd, char **env);
void			search_it3(char **env, t_cmd *cmd, int fd, char *path);
int				search_it4(char **v_path, t_cmd *cmd, int fd, char **env);
void			free_vpath(char **v_path);

void			exit_entry(t_cmd *tmp);
int				is_digit(char *str);
int				ft_atoi(char *str);
void			num_required_exit(t_cmd *tmp);
void			simple_exit(void);

void			envy(t_cmd *tmp);
void			dup_it_pipe(void);
int				execute_commands2(t_cmd *tmp, char **env);

#endif

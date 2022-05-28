/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfriesen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 18:43:49 by jfriesen          #+#    #+#             */
/*   Updated: 2019/03/19 18:43:52 by jfriesen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# define SPACES " \t"

# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "op.h"

int g_nline;

typedef struct			s_token
{
	char				*content;
	int					type;
	struct s_token		*next;
	int					bytes;
}						t_token;

typedef struct			s_operation
{
	struct s_token		*tokens;
	int					bytes;
	int					strnum;
	struct s_operation	*next;
	char				bin[21];
}						t_operation;

typedef struct			s_info
{
	char				*name;
	char				*comment;
	char				*filname;
	t_operation			*operations;
}						t_info;
void					write_name(t_info *info, int i, char *del, char	*del2);
int						go_to_16(char *str, int c1, int i, int size);
int						codinstr(t_operation *oper,
						t_info *info, int num);
int						go_to_16(char *str, int c1, int i, int size);
void					err(t_info *info, int i, char *c, int line);
void					error_exit(char *string, int nline,
						char **line, t_info **info);
int						find_marker(t_info *info, char *cont,
						t_token *tok, int line);
int						is_label(char *s);
int						is_spaces(char c);
t_token					*create_token(char *s);
t_token					*token_push_back(t_token *new, t_token **first);
void					operation_push_back(t_operation *new,
						t_operation **first);
t_operation				*create_operation(t_token *tokens);
char					**ft_strsplit_symbols(char *str, char *c);
t_info					*lexical_analyzer(int fd);
void					clean_array(char ***a);
int						ft_strchr_index(char *s, char c);
char					*clean_string(char **string);
void					delete_first_word(char **string);
void					delete_spaces_from_start(char **string);
int						ft_count_chr(char *string, char c);
int						starts_with(char *string, char *start);
int						full_of_spaces(char *string);
int						starts_with_command(char *string);
int						starts_with_label(char *string);
int						starts_with_end_spaces(char *string,
						char *start);
int						put_space_before_direct_char(char **line);
int						convert_string_to_operation(char **line,
						t_info *info);
void					parse_name_and_comment(char **line,
						t_info **info, int fd);
int						command_type(char *s);
int						check_syntax(t_operation *op);
void					assign_type(t_operation *op);
int						is_num(char *string);
t_info					*info_create(void);
void					free_info(t_info *info);
void					put_byte_code_into_newfile(char *new_filename,
						t_info *info);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouhsis <hbouhsis@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:01:25 by zmeribaa          #+#    #+#             */
/*   Updated: 2022/05/30 22:17:44 by hbouhsis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_lexer
{
	char			c;
	unsigned int	i;
	char			*contents;
}	t_lexer;

typedef enum e_type
{
	T_WORD,
	T_RDRIN,
	T_RDROUT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
}	t_type;

typedef struct s_token
{
	int		type;
	char	*value;
}		t_token;

typedef struct s_redirection
{
	int						type;
	char					*file;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_parse
{
	char			*cmd;
	char			**args;
	int				argsc;
	t_redirection	*redirection;
	struct s_parse	*next;
}				t_parse;

t_token			*init_tok(int token, char *value);
t_lexer			*init_lexer(char *contents);
void			lexer_advance(t_lexer *lexer);
void			lexer_skip_whitespace(t_lexer *lexer);
t_token			*lex_next_tok(t_lexer *lexer);
t_token			*lexer_collect_string(t_lexer *lexer, char c);
char			*lex_crr_str(t_lexer *lexer);
t_token			*lex_av_tok(t_lexer *lexer, t_token *token);
t_token			*lexer_collect_word(t_lexer *lexer);
char			*join_string(t_lexer *lexer, char c);
char			*join_word(t_lexer *lexer);
char			*after_quotes(t_lexer *lexer, char *val);
char			*expandinword(t_lexer *lexer);
char			*expandinquotes(t_lexer *lexer);
void			lexer_retreat(t_lexer *lexer);
char			*my_getenv(char *env);
char			*expandcheck(t_lexer *lexer, char *s);
void			add_redirecion(t_redirection *head, char *val, t_type type);
t_redirection	*init_redirection(char *val, t_type type);
t_parse			*init_commands(void);
t_parse			*add_command(void);
void			factory(t_token **token, t_parse *command, int i);
void			create_command(t_token **token);
t_token			**realloc_token(t_token **curr, t_token *token);
void			parse(void);
t_token			*err_quotes(char *val);
char			*join_string(t_lexer *lexer, char c);
char			*join_word(t_lexer *lexer);
char			*after_quotes(t_lexer *lexer, char *val);
char			*expandinword(t_lexer *lexer);
char			*expandinquotes(t_lexer *lexer);
void			lexer_retreat(t_lexer *lexer);
char			*my_getenv(char *env);
char			*expandcheck(t_lexer *lexer, char *s);
void			add_redirecion(t_redirection *head, char *val, t_type type);
t_redirection	*init_redirection(char *val, t_type type);
t_parse			*init_commands(void);
t_parse			*add_command(void);
void			factory(t_token **token, t_parse *command, int i);
void			create_command(t_token **token);
t_token			**realloc_token(t_token **curr, t_token *token);
t_token			*err_quotes(char *val);
t_token			*free_retnull(char *val);
void			free_command(void);
void			free_redirections(t_redirection *rdr);
void			free_all(void);
char			*expand_exit(t_lexer *lexer);
#endif

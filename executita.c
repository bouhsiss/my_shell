/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:15 by hbouhsis          #+#    #+#             */
/*   Updated: 2022/05/22 21:27:30 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define INPUT_REDIRECTION 1
# define OUTPUT_REDIRECTION 2
# define APPEND_REDIRECTION 4

# include <stdbool.h>
# include <errno.h>

/* 
 * duplication of file descriptors
 * @param fd -> filedes
 * @param desired_fileno -> filedes2
 * 
 * man dup2 for more information
 */
static void	__duplicate_file_descriptors(int *fd, int desired_fileno) {
	if (*fd > 2) {
		dup2(*fd, desired_fileno);
		close(*fd);
	}
}

/*
 * duplication of the last input and last output
 @ param cmd_list -> main structure
 @ param fdin -> input filedes
 @ paran fdout -> output filedes
 */
static void	__dup_last_in_last_out(t_parse *cmd_list, int *fdin, int *fdout) {
	bool flagged_input = false;
	bool flagged_output = false;
	t_redirection *redir_copy = cmd_list->redirection;
	while (redir_copy != NULL) {
		if (redir_copy->type == INPUT_REDIRECTION) {
			flagged_input = true;
		} if (redir_copy->type == OUTPUT_REDIRECTION || redir_copy->type == APPEND_REDIRECTION) {
			flagged_output = true;
		}
		redir_copy = redir_copy->next;
	}
	if (flagged_input) {
		__duplicate_file_descriptors(fdin, STDIN_FILENO);
	} if (flagged_output) {
		__duplicate_file_descriptors(fdout, STDOUT_FILENO);
	}
}



/* 
 * redirection implementation
 * @param cmd_list ==> main structure
 * 
 * bash has a weird behaviour kind of thing regarding redirections
 * (n - 1) get ignored in some way
 * the appropirate file descriptors do get opened but none of them
 * gets the duplicated file descriptor
 * the (n) redirection, is the one where we duplicate the appropriate fd
 */
static void	__implement_redirections(t_parse *cmd_list) {
	int fdin = STDIN_FILENO;
	int fdout = STDOUT_FILENO;
	/* 
	 * loop through every redirection and open the appropriate file descriptors
	 * NB: make sure you close fdout or fdin if their values differ from originial
	 * that means the same thing as for pipes that the loop's already got executed before.
	 * (man 2 open) returns -1 on failure, and sets errno to indicate the error.
	 */
	t_redirection *redirection_copy = cmd_list->redirection;
	while (redirection_copy != NULL) {
		if (redirection_copy->type == INPUT_REDIRECTION) {
			if (fdin != STDIN_FILENO) {
				close(fdin);
			}
			fdin = open(redirection_copy->file, O_RDONLY, 0644);
		} else if (redirection_copy->type == OUTPUT_REDIRECTION || redirection_copy->type == APPEND_REDIRECTION) {
			if (fdout != STDOUT_FILENO) {
				close(fdout);
			} if (redirection_copy->type == OUTPUT_REDIRECTION) {
				fdout = open(redirection_copy->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			} else if (redirection_copy->type == APPEND_REDIRECTION)
				fdout = open(redirection_copy->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		} if (fdin == -1 || fdout == -1) {
			exit(69);
		}
		redirection_copy = redirection_copy->next;
	}
	
	/* 
	 * we only duplicate the last fdin and the last fdout
	 * NB: last fdin && last fdout appropriately
	 * ==> not the last filedes on a pipeline
	 */
	__dup_last_in_last_out(cmd_list, &fdin, &fdout);
}





/* 
 * execution function
 * @param env => environment variables
 */
void	execute(char **env) {
	(void)env;

	/* 
	 * process_id
	 */
	pid_t pid;
	
	/* 
	 * we create pipe fds holders
	 * we create a temporary variable in that will play as a middleman
	 */
	int pipe_fds[2];
	int in = STDIN_FILENO;

	/* 
	 * we start by initalizing our main structure
	 */
	t_parse *cmd_list;
	cmd_list = mini.command;


	/*
	 * spawn multiple processes
	 */
	while (cmd_list->next != NULL) {
		
		/*
		 * once this loop enters, this means we have a pipeline to execute ;
		 * we start by initialisation of our pipe_fds using pipe()
		 */
		pipe(pipe_fds);
		
		/*
		 * spawn a process on each iteration of the loop until pipeline
		 * is on it's last -1 element
		 */
		pid = fork();
		if (pid == 0) {
			/*
			 * we know that we will be writing on reading and writing ends of pipe
			 * NB: we check for [ in, pipe_fds[0], pipe_fds[1] ] as they're not in their awaited values
			 * ==> it means this piece of code's already got executed before
			 * 
			 * - we first check that our variable in is not 0 ;
			 * - we then check for writing end of pipe
			 * ==> we dup the appropriate file descriptors to them
			 * - we then make sure that we closed the reading end of pipe
			 * ==> we'll be executing a command on the duplicated file descriptor
			 */
			if (in != STDIN_FILENO) {
				dup2(in, STDIN_FILENO);
				close(in);
			} if (pipe_fds[STDOUT_FILENO] != STDOUT_FILENO) {
				dup2(pipe_fds[STDOUT_FILENO], STDOUT_FILENO);
				close(pipe_fds[1]);
			} if (pipe_fds[STDIN_FILENO] > 2) {
				close(pipe_fds[STDIN_FILENO]);
			}


			/*
			 * redirections
			 */
			if (cmd_list->redirection != NULL) {
				__implement_redirections(cmd_list);
			}

			/* 
			 * we executed the desired command
			 * in case of errors we should return the appropriate exit code
			 * else child will return and data flow proceeds
			 */
			if (cmd_list->cmd != NULL) {
				if (execvp(cmd_list->args[0], cmd_list->args) == -1) {
					/* 
					 * exit with the appropriate exit_code
					 *
					 * you can use errno to know what kind of error was returned
					 * and set the returned exit code to the appropriate one.
					 * 
					 * e.g:
					 * ==> errno 13 EACCES Permission denied.
					 * An attempt was made to access a file in a way forbidden
					 * by its file access permissions.
					 */
					if (errno == 13)
						exit(126);
					exit(69420);
				}
			}
			/* 
			 * this exit is used in case we have a nulled command
			 * which will cause the child to hang if we don't exit manually
			 *
			 * exit with the appropriate exit_code
			 */
			exit(69);
		}


		/* 
		 * we make sure we close the file descriptors that we duplicated in the child
		 * we make sure we close writing end of pipe
		 * we make sure we close in)
		 */
		if (pipe_fds[STDOUT_FILENO] > 2) {
			close(pipe_fds[STDOUT_FILENO]);
		} if (in != STDIN_FILENO) {
			close(in);
		}

		/* 
		 * in takes the reading end of pipe now to get it ready
		 * for either the next command or last command
		 */
		in = pipe_fds[STDIN_FILENO];
		cmd_list = cmd_list->next;
	}


	/*
	 * spawn one process
	 * this piece of code handles either last pipeline command or a simple command
	 * in other words if the checks we'll have on the child get executed
	 * ==> it means it's the last command on a pipeline
	 * if they get ignored it means It's a simple command by base
	 */
	
	pid = fork();
	if (pid == 0) {
		
		/* 
		 * if in has a different value than what we first initialized it with
		 * It means it's the last command on a pipeline we proceed to dup2 on the stdin
		 * and we make sure we close writing end of pipe or it will leak as it's useless now.
		 */
		if (in != STDIN_FILENO) {
			dup2(in, STDIN_FILENO);
			close(in);
		} if (pipe_fds[1] > 2) {
			close(pipe_fds[1]);
		}

		/*
		 * redirections
		 */
		if (cmd_list->redirection != NULL) {
			__implement_redirections(cmd_list);
		}
	
		/* 
		 * we executed the desired command
		 * in case of errors we should return the appropriate exit code
		 * else child will return and data flow proceeds
		 */
		if (cmd_list->cmd != NULL) {
			if (execvp(cmd_list->args[0], cmd_list->args) == -1) {
				/* 
				 * exit with the appropriate exit_code
				 *
				 * you can use errno to know what kind of error was returned
				 * and set the returned exit code to the appropriate one.
				 * 
				 * e.g:
				 * ==> errno 13 EACCES Permission denied.
				 * An attempt was made to access a file in a way forbidden
             	 * by its file access permissions.
				 */
				if (errno == 13)
					exit(126);
				exit(EXIT_FAILURE);
			}
		}
		/* 
		 * this exit is used in case we have a nulled command
		 * which will cause the child to hang if we don't exit manually
		 *
		 * exit with the appropriate exit_code
		 */
		exit(EXIT_FAILURE);

	}

	/*
	 * close the last duplicated file descriptors
	 * ==> prevents fd leaks
	 */ 	
	if (in != STDIN_FILENO) {
		close(in);
	}
	
	
	/* 
	 * we use a garbaged variable called 'stat_loc'
	 * It will catch the exit status returned by child
	 * and save it on stat_loc
	 * WEXITSTATUS(status)
	 * ==> if WIFEXITED(status) is true, evaluates to the low-oder 8 bits of the argument
	 * passed to exit by the child
	 * NB: the usage of (wait, wait3m wait4) is equally if options set well
	 * read the man for differences (man 2 wait)
	 * 
	 * having the exit_code as a singleton variable (global var)
	 * is okey since It'll make implementation of other functionalities
	 * very easy
	 */
	int exit_code;
	int stat_loc;
	while (waitpid(-1, &stat_loc, 0) > 0) {
		if (WIFEXITED(stat_loc)) {
			exit_code = WEXITSTATUS(stat_loc);
		}
	}
	printf("\n-------------\nparent returned -> exit_code = %d\n-------------\n", exit_code);
}


# Minishell !
personal implementation of a simple shell .

## what does the project does ?

Your shell should :

_ Display a **prompt** when waition for a new command.<br/>
_ Have a working **history**.<br/>
_ Search and launch the right executable (based on **PATH** variable or using a relative or an absoluet path).<br/>
_ Not interpret unclosed quotes or special characters which are not required by the subject such as '\' or ';' .<br/>
_ Handle ' (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.<br/>
_ Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).<br/>
_ Implement redirections ( < _ > _ >> _ <<) .<br/>
_ Implement infinite **pipes**.<br/>
_ Handle **environment variables** which should expand to their values by using " $ ".<br/>
_ Handle **$?** which should expand to the exit status value.<br/>
_ Handle ctrl-C, ctrl-D and ctrl-\ .<br/>
_ Implement thet following builtins :<br/>
	&nbsp;- **echo** with option -n <br/>
	&nbsp;- **cd** with only a relative or absolute path <br/>
	&nbsp;- **pwd** with no options <br/>
	&nbsp;- **export** with no options <br/>
	&nbsp;- **unset** with no options <br/>
	&nbsp;- **env** with no options or arguments <br/>
	&nbsp;- **exit** with no options <br/>
## why the project is useful
	_ the aim of this project if to gain experience with some advanced programming techniques like process creationand control, file descriptors, signals and pipes.
## Usage 
	_ clone the repo, execute <sub>make</sub> command and then execute <sub>./Minishell</sub> and it will display a prompt. 
	then you can have fun with it.
## Who contributes to the project
	- the Parsing part was done by :
	@zmeribaa
	https://github.com/zmeribaa
	- the Execution part was done by @me.
# Ressources
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
	https://www.rozmichelle.com/pipes-forks-dups/
	https://pubs.opengroup.org/onlinepubs/7908799/xcu/chap2.html


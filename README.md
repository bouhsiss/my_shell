
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
	&emsp;- **echo** with option -n <br/>
	&emsp;- **cd** with only a relative or absolute path <br/>
	&emsp;- **pwd** with no options <br/>
	&emsp;- **export** with no options <br/>
	&emsp;- **unset** with no options <br/>
	&emsp;- **env** with no options or arguments <br/>
	&emsp;- **exit** with no options <br/>
## why the project is useful ?
_ the aim of this project if to gain experience with some advanced programming techniques like process creationand control, file descriptors, signals and pipes.
## Usage.
_ clone the repo, execute ```make``` command and then execute ```./Minishell``` and it will display a prompt. 
then you can have fun with it.
## Who contributes to the project ?
- the Parsing part was done by :
	@zmeribaa</br>
	https://github.com/zmeribaa
- the Execution part was done by @me.
# Ressources.
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf </br>
https://www.rozmichelle.com/pipes-forks-dups/ </br>
https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e </br>
https://www.geeksforgeeks.org/making-linux-shell-c/ </br>
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Simple-Commands </br>
https://mywiki.wooledge.org/BashParser </br>
http://aosabook.org/en/bash.html </br>
https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html </br>
https://brennan.io/2015/01/16/write-a-shell-in-c/ </br>
https://hackernoon.com/lets-build-a-linux-shell-part-i-bz3n3vg1 </br>
https://chrismartine-e.medium.com/creating-your-own-linux-shell-1cbaaae2c41c </br>
https://www.quora.com/How-do-I-create-my-own-shell-in-Linux </br>
https://www.codementor.io/@sandesh87/how-and-why-i-built-a-mini-linux-shell-using-c-1dqk5olxgw </br>
https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html </br>
https://pubs.opengroup.org/onlinepubs/7908799/xcu/chap2.html </br>
https://blog.scottlowe.org/2015/01/27/using-fork-branch-git-workflow/ </br>
https://github.com/moisam/lets-build-a-linux-shell </br>
https://putaindecode.io/articles/maitriser-les-redirections-shell/ </br>



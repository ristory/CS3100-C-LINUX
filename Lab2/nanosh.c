/* 
 CS 3100 Lab 2 - by Hoang Cao
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void cmdExit(int argc, char **argv) {
	if(argc == 1){
	exit(0);
}
	errno = EINVAL;
	perror("exit command failed ");
	return;
}

void cmdPWD(int argc, char **argv) {
        char* cwd;
	char buff[PATH_MAX +1];
	cwd = getcwd(buff, PATH_MAX +1);
	if(argc == 1){
      	printf("%s\n",cwd);
	return;
}
	
        errno = EINVAL;
        perror("exit command failed ");
        return;
}
void cmdCD(int argc, char **argv) {
        if(argc == 1)
{
        chdir(getenv("HOME"));
	return;
}
	if(argc == 2)
{
	chdir(argv[1]);
	errno = ENOENT;
        perror("exit command failed ");
        return;
	
}
	else
	{
	errno = EINVAL;
        perror("exit command failed ");
        return;
	}
}

void cmdFunction(int argc, char **argv) {
	pid_t cpid;
	cpid = fork(); 
        if(cpid == 0)
{

	execvp(argv[0],argv);	
	 errno = EINVAL;
        perror("exit command failed ");
        return;

}
	if(cpid == -1)
{
        errno = EINVAL;
        perror("exit command failed ");
        return;
}
	else{
	int status;
	pid_t value = waitpid(cpid, &status, 0);
if(value > 0)
{
if(WIFEXITED(status))
printf("%d\n",WEXITSTATUS(status));
else
printf("%d\n",status);
}
else if(value==0)
printf("Process is running\n");
  errno = EINVAL;
        perror("exit command failed ");

}
	

}



// getParameters returns the argc, the number of words found in cmd
//  while populating argv with pointers to each word
int getParameters(char *cmd, char **argv) {
	char *token;
	int argc = 0;
	token = strtok(cmd, " \t\n");
	while (token != NULL) {
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " \t\n");
	}
	argv[argc] = NULL;		// set last + 1 argument to NULL
	return argc;
}

int main(int argc, char **argv) {

	char cmd[1024];
	char *rc;
	int myArgc = 0;
	char *myArgv[1000];

	while (1) {
		printf("nanosh: ");
		fflush(stdout);
		rc = fgets(cmd, sizeof(cmd), stdin);
		if (rc == NULL) {
			exit(0);
		}
		myArgc = getParameters(cmd, myArgv);

		// if no words typed: restart loop
		if (myArgc == 0) {			
			continue;
		}

		// if the first word is "exit", terminate the program
		if (strcmp(myArgv[0], "exit") == 0) {
			cmdExit(myArgc, myArgv);
			continue;
		}
		if (strcmp(myArgv[0], "pwd") == 0) {
                        cmdPWD(myArgc, myArgv);
                        continue;
                }
		  if (strcmp(myArgv[0], "cd") == 0) {
                        cmdCD(myArgc, myArgv);
                        continue;
                }
		
		  if(strcmp(myArgv[0], "exit")!=0 || strcmp(myArgv[0], "pwd")!=0 || strcmp(myArgv[0], "cd")!=0 || strcmp(myArgv[0], "chdir")!=0)
		 {
                        cmdFunction(myArgc, myArgv);
                        continue;
                }
 

		// add if statements here for the other internal commands
		//   and a default action that calls a function to fork()
		//   and exec() while the parent issues waitpid()
	}

	return 0;
} 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int execute_command(int input_fd, int output_fd, char *command, char *arg)
{
    pid_t pid = fork();
    
    if (pid == 0) {
        if (input_fd != -1) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        
        if (output_fd != -1) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        
        if (command != NULL) {
            if (arg != NULL)
                execlp(command, command, arg, NULL);
            else
                execlp(command, command, NULL);
            perror("execlp");
            exit(1);
        }
        exit(1);
    }
	waitpid(pid, NULL, 0);
    if (input_fd != -1)
        close(input_fd);
    if (output_fd != -1)
        close(output_fd);
        
    return pid;
}


int main()
{
	int pipe1[2];
	int pipe2[2];

	pipe(pipe1);
	pipe(pipe2);
    pid_t pid1 = execute_command(-1, pipe1[1], "ls", "-la");
    pid_t pid2 = execute_command(pipe1[0], pipe2[1], "grep", "test");
    pid_t pid3 = execute_command(pipe2[0], -1, "wc", "-l");
    
    // Wait for all at the end
    // waitpid(pid1, NULL, 0);
    // waitpid(pid2, NULL, 0);
    // waitpid(pid3, NULL, 0);
	// {
	// 	close(fd2[1]);
	// 	dup2(fd2[0], STDOUT_FILENO);
	// 	close(fd2[0]);
	// 	execlp("ls", "ls", NULL);
	// }
	// waitpid(pid, NULL, 0);
	// close(fd2[1]);
	// dup2(fd2[0], STDIN_FILENO);
	// close(fd2[0]);
	
	return 0;
}
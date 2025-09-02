#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define READ_END 0
#define WRITE_END 1

char *ls[] = {
	"/usr/bin/ls", NULL
};

char *grep[] = {
	"/usr/bin/grep", "a", NULL
};

char *wc[] = {
	"/usr/bin/wc", "-l", NULL
};

char **g_commands[] = {
	ls,
	grep,
	wc,
	NULL,
};

void execute_pipe_pair(char ***commands)
{
	int pipe_fds[2];
	int first_fork_pid;
	int second_fork_pid;

	if (commands[1])
	pipe(pipe_fds);
	first_fork_pid = fork();
	if (first_fork_pid == 0)
	{
		// First child, do (for example) ls
		dup2(pipe_fds[WRITE_END], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		execvp(commands[0][0], commands[0]);
	}
	else
	{
		// Parent
		second_fork_pid = fork();
		if (second_fork_pid == 0)
		{
			// Second child, go (for example) grep a | wc -l
			dup2(pipe_fds[READ_END], STDIN_FILENO);
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			char ***smaller_pipeline = &commands[1];
			if (smaller_pipeline[1])
				execute_pipe_pair(smaller_pipeline);
			else
				execvp(smaller_pipeline[0][0], smaller_pipeline[0]);
		}
		else
		{
			// Parent, wait for both children to finish
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			waitpid(-1, NULL, 0);
			waitpid(-1, NULL, 0);
		}
	}
}

int main(void)
{
	execute_pipe_pair(g_commands);
	return (0);
}

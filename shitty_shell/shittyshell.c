

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    char *line = NULL;
    size_t bufsize = 0;
    pid_t pid, wpid;
    int status;

    while (1) {
        // 1. Print a prompt
        printf("$ ");

        // 2. Read a line of input
        if (getline(&line, &bufsize, stdin) == -1) {
            perror("getline");
            break;
        }

        // 3. Trim the newline character
        line[strcspn(line, "\n")] = '\0';

        // 4. Fork a new process
        pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) { // Child process
            // 5. Create argument vector
            char *argz[2];
            argz[0] = line;
            argz[1] = NULL;

            // 6. Execute the command
            if (execvp(line, argz) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE); // Exit the child process on error
            }
        } else { // Parent process
            // Wait for the child process to complete
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

        // 7. Free the memory for line and reset buffer
        free(line);
        line = NULL;
        bufsize = 0;
    }

    return 0;
}

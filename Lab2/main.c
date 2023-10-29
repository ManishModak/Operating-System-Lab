#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    // Create an array of strings to store the command-line arguments
    char* data[argc - 1];

    for (int j = 1; j < argc; j++) {
        data[j - 1] = argv[j];
    }

    // Sorting the arguments (bubble sort)
    for (int i = 1; i < argc - 2; i++) {
        for (int j = 1; j < argc - i - 2; j++) {
            if (atoi(data[j]) > atoi(data[j + 1])) {
                char* temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execv(data[0], data);
        perror("Exec failed");
        exit(1);
    } else {
        // Parent process
        int status;
        wait(&status);
    }

    return 0;
}


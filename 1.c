#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Дочірній процес PID: %d запущено\n", getpid());
        sleep(5); 
        printf("Дочірній процес завершено\n");
        exit(0);
    } else {
        printf("Батьківський процес PID: %d, чекає на завершення дочірнього PID: %d...\n", getpid(), pid);
        int status;
        while (1) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == 0) {
                printf("Дочірній процес ще працює...\n");
                sleep(1); 
            } else if (result == pid) {
                printf("Дочірній процес завершився з кодом %d\n", WEXITSTATUS(status));
                break;
            } else {
                perror("waitpid");
                break;
            }
        }
    }
    return 0;
}
//gcc -Wall 1.c -o 1
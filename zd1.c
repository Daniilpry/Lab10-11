#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Дочірній процес (PID: %d) стартував\n", getpid());
        sleep(5);
        printf("Дочірній процес (PID: %d) завершується\n", getpid());
        exit(0);
    } else {
        int status;
        printf("Батьківський процес (PID: %d) продовжує роботу\n", getpid());

        while (1) {
            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == 0) {
                printf("Очікування... Дочірній ще працює\n");
                sleep(1);
            } else if (result == pid) {
                printf("Дочірній процес завершено. Код завершення: %d\n", WEXITSTATUS(status));
                break;
            } else {
                perror("waitpid error");
                break;
            }
        }
    }

    return 0;
}

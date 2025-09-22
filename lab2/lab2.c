#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 1024

int main() {
  char program[MAX_INPUT];

  // printf("Enter programs to run.\n");

  while (1) {

    printf("Enter programs to run.\n");
    printf("> ");
    fflush(stdout);

    if (fgets(program, sizeof(program), stdin) == NULL) {
      break;
    }

    program[strcspn(program, "\n")] = 0;

    if (program[0] == '\0') {
      continue;
    }

    pid_t pid = fork();

    if (pid < 0) {
      perror("fork failed");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {
      execl(program, program, (char *)NULL);

      fprintf(stderr, "Exec failure\n");
      exit(EXIT_FAILURE);
    } else {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}

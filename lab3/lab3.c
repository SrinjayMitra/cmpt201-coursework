#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void free_history(char **history, int count) {
  for (int i = 0; i < count; ++i) {
    free(history[i]);
  }
}

void print_history(char **history, int count) {
  for (int i = 0; i < count; ++i) {
    printf("%s", history[i]);
  }
}

int main() {
  char *history[HISTORY_SIZE] = {NULL};
  int history_count = 0;
  int history_start = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while (1) {
    printf("Enter input: ");
    fflush(stdout);
    read = getline(&line, &len, stdin);
    if (read == -1) {
      // EOF (Ctrl+D), break loop
      break;
    }

    // Remove any existing newline at end
    if (read > 0 && line[read - 1] != '\0' && line[read - 1] == '\n') {
      line[read - 1] = '\0';
      --read;
    }

    // Check for "print" command
    if (strcmp(line, "print") == 0) {
      // Add "print" to history
      char *copy = malloc(strlen("print\n") + 1);
      if (copy != NULL)
        strcpy(copy, "print\n");
      // strdup("print\n");
      if (history_count < HISTORY_SIZE) {
        history[history_count++] = copy;
      } else {
        free(history[history_start]);
        history[history_start] = copy;
        history_start = (history_start + 1) % HISTORY_SIZE;
      }
      // Print history (in order)
      for (int i = 0; i < history_count; ++i) {
        int idx = (history_start + i) % HISTORY_SIZE;
        printf("%s", history[idx]);
      }
      printf("\n");
      continue;
    }

    char *copy = malloc(read + 2);
    strcpy(copy, line);
    strcat(copy, "\n");

    if (history_count < HISTORY_SIZE) {
      history[history_count++] = copy;
    } else {
      free(history[history_start]);
      history[history_start] = copy;
      history_start = (history_start + 1) % HISTORY_SIZE;
    }
  }

  free(line);

  for (int i = 0; i < history_count; ++i) {
    int idx = (history_start + i) % HISTORY_SIZE;
    free(history[idx]);
  }
  return 0;
}

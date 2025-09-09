#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
  char buffer[32];
  char *b = buffer;
  size_t bufsize = 32;
  size_t characters;
  char *token;
  printf("entr your number\n");
  characters = getline(&b, &bufsize, stdin);
  printf("%zu", characters);
  printf("%s", buffer);
  while ((token = strtok_r(b, " ", &b)))
    printf("%s\n", token);
  return 0;
}

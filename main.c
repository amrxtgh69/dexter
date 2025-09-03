#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1024
int main() {
  char input[MAX_INPUT];
  char *args[MAX_ARGS]
  while (1) {
    printf("smolshell> ");
    fflush(stdout);

    if (fgets(input, MAX_INPUT, stdin) == NULL) {
      printf("\n");
      break;
    }
    input[strcspn(input, "\n")] = 0;
    
    if (strcmp(input, "exit") == 0) {
      break;
    }
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL && i < MAX_ARGS -1) {
      args[i++] = token;
      token = strtok(NULL, " ");
    }

  }
  printf("Exiting the shell...\n");
  return 0;
}

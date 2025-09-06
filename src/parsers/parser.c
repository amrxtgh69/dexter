#include <string.h>
#include "parser.h"

int parse_input(char *input, char *args[]) {
  int argc = 0;
  //tokenize the input
  char *token = strtok(input, " ");
  while (token != NULL && argc < MAX_ARGS - 1) {
    args[argc++] = token;
    token = strtok(NULL, " ");
    }
  args[argc] = NULL;
  return argc;
}

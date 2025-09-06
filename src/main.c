#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#include "prompt_handler.h"
#include "parser.h"
#include "command_handler.h"
#include "commands.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

int main() {
  char input[MAX_INPUT_SIZE];
  char *args[MAX_ARGS];
  int argc;

  while (1) {
    print_prompt();
    if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
      printf("\n");
      break;
    }
    input[strcspn(input, "\n")] = 0;
    if (strcmp(input, "exit") == 0) {
      break;
    }
    argc = parse_input(input, args);
    execute_command(argc, args);
  }
  printf("Exiting the shell..\n");
}



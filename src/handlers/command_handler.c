#include <stdio.h>
#include <string.h>
#include "command_handler.h"
#include "commands.h"

void execute_command(int argc, char *args[]){
  if (argc == 0) {
    return;
  }
  if (strcmp(args[0], "ls") == 0){
    built_ls(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "cd") == 0) {
    builtin_cd(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "cat") == 0) {
    builtin_cat(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "clear") == 0) {
    builtin_clear();
  }
  else if (strcmp(args[0], "pwd") == 0) {
    builtin_pwd();
  }
  else if (strcmp(args[0], "mkdir") == 0) {
    builtin_mkdir(argc > 1 ? args[1] : NULL);
  }
  else if (strcmp(args[0], "touch") == 0) {
    if (argc > 1) {
      builtin_touch(argc, args);
    } else {
      fprintf(stderr, "touch: missing file operand\n");
    }
  }
  else {
    fprintf(stderr, "Command not found: %s\n", args[0]);
  }
}



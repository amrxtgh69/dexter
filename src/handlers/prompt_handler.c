#include <stdio.h>
#include <unistd.h>
#include "prompt_handler.h"

void print_prompt() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("dexter:%s> ", cwd);
  } else {
    printf("dexter> ");
  }
  fflush(stdout);
}

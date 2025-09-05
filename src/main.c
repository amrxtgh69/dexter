#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void built_ls(char *path) {
  DIR *dir;
  struct dirent *entry;
  if (path == NULL) path = ".";
  dir = opendir(path);
  if (dir == NULL) {
    perror("ls");
    return;
  }
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      printf("%s  ", entry->d_name);
    }
 }
  printf("\n");
  closedir(dir);
}

void builtin_cd(char *path) {
  if (path == NULL) {
    path = getenv("HOME");
  }
  if (chdir(path) != 0) {
    perror("cd");
  }
}

void parse_and_execute(char *input) {
  char *args[MAX_ARGS];
  int argc = 0;
  //tokenize the input
  char *token = strtok(input, " ");
  while (token != NULL && argc < MAX_ARGS - 1) {
    args[argc++] = token;
    token = strtok(NULL, " ");
    }
  args[argc] = NULL;
  if (argc == 0) {
    return;
  }
    //command execution
  if (strcmp(args[0], "ls") == 0) {
    if (argc > 1) {
      built_ls(args[1]);
    } else built_ls(NULL);
  }
  else if (strcmp(args[0], "cd")) {
    if (argc > 1) builtin_cd(args[1]);
    else builtin_cd(NULL);
  }
}

int main() {
  char input[MAX_INPUT_SIZE];
  while (1) {
    printf("dexter> ");
    fflush(stdout);
    if (fgets(input, MAX_INPUT_SIZE,  stdin) == NULL) {
      printf("\n");
      break;
    }
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "exit") == 0) {
      break;
    }
    parse_and_execute(input);
  }
  printf("Exiting the shell\n");
}


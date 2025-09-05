#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>


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
    //if no path then go to home
    path = getenv("HOME");
    if (path == NULL) {
      fprintf(stderr, "cd:Home environment variable not set\n");
      return;
    }
  }
  if (strcmp(path, ".") == 0) {
    return;
  }

  if (chdir(path) != 0) {
    perror("cd");
  }
}

void builtin_pwd() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  }else {
    perror("pwd");
  }
}

void builtin_clear() {
  //ANSI escape code to clear the screen
  printf("\033[H\033[J");
  fflush(stdout);
}

void builtin_cat(char *filename) {
  if (filename == NULL) {
    fprintf(stderr, "cat: missing file operand\n");
    return;
  }
  FILE *file = fopen(filename, "r"); 
    if (file == NULL) {
      perror("cat");
      return; 
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
      putchar(ch);
    }
  fclose(file);
}

void builtin_mkdir(char *dirname) {
  if (dirname == NULL) {
    fprintf(stderr, "mkdir: missing directory name\n");
    return;
  }
  if (mkdir(dirname, 0755) != 0) {
    perror("mkdir");
  }
}

void builtin_touch(int argc, char *args[]) {
  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(args[i], "a");
    if (file == NULL) {
      perror("touch");
    } else fclose(file);
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
  else if (strcmp(args[0], "cd") == 0) {
    if (argc > 1) builtin_cd(args[1]);
    else builtin_cd(NULL);
  }
  else if (strcmp(args[0], "pwd") == 0) {
    builtin_pwd();
  }
  else if (strcmp(args[0], "clear") == 0) {
    builtin_clear();
  }
  else if (strcmp(args[0], "cat") == 0) {
    if (argc > 1) {
      builtin_cat(args[1]);
    }
    else builtin_cat(NULL);
  }
  else if (strcmp(args[0], "mkdir") == 0) {
    if (argc > 1) builtin_mkdir(args[1]);
    else builtin_mkdir(NULL);
  }
  else if (strcmp(args[0], "touch") == 0) {
    if (argc > 1) builtin_touch(argc, args);
    else fprintf(stderr, "touch: missing file operation\n");
  }
}

int main() {
  char input[MAX_INPUT_SIZE];
  char cwd[1024];
  while (1) {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      printf("dexter:%s>", cwd);
      fflush(stdout);
    } else printf("dexter> ");
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


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "commands.h"

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

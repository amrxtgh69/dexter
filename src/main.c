#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1024

int main() {
  char input[MAX_INPUT];
  while (1) {
    printf("dexter>  ");
    fflush(stdout);
    if (fgets(input, MAX_INPUT,  stdin) == NULL) {
      printf("\n");
      break;
    }
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "exit") == 0) {
      break;
    }
    printf("you typed %s\n", input);
  }
  printf("Exiting the shell\n");
}

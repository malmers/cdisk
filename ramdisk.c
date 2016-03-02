#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define GIGABYTE 2097152
#define PATH_SIZE 100

int main(int argc, char *argv[]) {
  char path[PATH_SIZE];
  char ram[80];
  int size, pid;
  int fd[2];

  if(argc < 2) {
    fprintf(stderr, "Too few arguments\n");
  	return 1;
  }

  size = strtol(argv[1], NULL, 10);
  sprintf(ram, "ram://%d", size*GIGABYTE);

  if(pipe(fd) == -1) {
    perror("pipe");
  exit(EXIT_FAILURE);
  }

  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Fork failed");
  } else if(pid == 0) {
    close(fd[0]);
    printf("%s", ram);
    dup2(fd[1], fileno(stdout));
    execlp("hdiutil", "hdiutil", "attach", "-nomount", ram, NULL);
    exit(1);
  } else {
    close(fd[1]);
    wait(NULL);

    FILE *stream;

    stream = fdopen(fd[0], "r");
    fread(path, 1, PATH_SIZE, stream);
    fclose (stream);

    printf("Path: \"%s\"\n", path);
  }

  return 0;
}

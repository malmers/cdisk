#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define GIGABYTE 2097152
#define PATH_SIZE 100

void usage() {
  fprintf(stderr, "usage: ramdisk size\n");
}

char *trimwhitespace(char *str) {
  // http://stackoverflow.com/questions/122616/
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int main(int argc, char *argv[]) {
  char path[PATH_SIZE];
  char ram[80];
  int size, pid;
  int fd[2];

  if(argc < 2) {
    usage();
    exit(EXIT_FAILURE);
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
    exit(EXIT_FAILURE);
  } else if(pid == 0) {
    close(fd[0]);
    dup2(fd[1], fileno(stdout));
    execlp("hdiutil", "hdiutil", "attach", "-nomount", ram, NULL);
    exit(EXIT_FAILURE);
  } else {
    close(fd[1]);
    wait(NULL);

    FILE *stream;

    stream = fdopen(fd[0], "r");
    fread(path, PATH_SIZE, 1, stream);
    fclose (stream);
    trimwhitespace(path);
  }

  execlp("diskutil", "diskutil", "erasevolume", "HFS+", "RAM Disk", path, NULL);
  return EXIT_FAILURE;
}

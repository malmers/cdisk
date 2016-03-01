#include <stdio.h>
#include <stdlib.h>

#define GIGABYTE 2097152

int main(int argc, char *argv[]) {
  int size;
  printf("Size of gig: %d\n", GIGABYTE);

  if(argc < 2) {
    fprintf(stderr, "Too few arguments\n");
  	return 1;
  }

  size = strtol(argv[1], NULL, 10);
  printf("Size: %d\n", size);

  return 0;
}


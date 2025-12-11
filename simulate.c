#include "buffer_struct.h"
#include <stdio.h>
#include <stdlib.h>
#
int main(int argc, char *argv[]) {
  if (argc < 2)
    return EXIT_FAILURE;
  ReadWriteBuff RWB;
  if (RW_init(&RWB, argv[1], 2048) != 0) {
    printf("Failed to initialize buffer\n");
    return EXIT_FAILURE;
  }
  printf("Generation 0: %s\n", RWB.read_buf);
  RW_append(&RWB, "ab");
  RW_swap(&RWB);
  printf("Generation 1: %s\n", RWB.read_buf);
  return EXIT_SUCCESS;
}

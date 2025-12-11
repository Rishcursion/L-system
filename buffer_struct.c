#include "buffer_struct.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RW_init(ReadWriteBuff *RWB, const char *axiom, size_t size) {
  RWB->read_buf = malloc(size);
  RWB->write_buf = malloc(size);
  RWB->total_capacity = size;
  RWB->write_idx = 0;
  if (!RWB->read_buf || !RWB->write_buf) {
    return 1;
  };
  strcpy(RWB->read_buf, axiom);
  RWB->write_buf[0] = '\0';
  return 0;
}

int RW_append(ReadWriteBuff *RWB, const char *src) {
  size_t len = strlen(src);
  if (RWB->write_idx + len > RWB->total_capacity) {
    return 2;
  };
  memcpy(&(RWB->write_buf[RWB->write_idx]), src, len);
  RWB->write_idx += len;
  RWB->write_buf[RWB->write_idx] = '\0';
  return 0;
}

int RW_swap(ReadWriteBuff *RWB) {
  if (RWB->write_idx == 0)
    return 1;
  char *temp = RWB->read_buf;
  RWB->read_buf = RWB->write_buf;
  RWB->write_buf = temp;

  RWB->write_idx = 0;
  RWB->write_buf[0] = '\0';
  return 0;
}

void RW_destroy(ReadWriteBuff *RWB) {
  free(RWB->read_buf);
  free(RWB->write_buf);
}

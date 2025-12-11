#ifndef BUFFER
#define BUFFER
#include <stddef.h>

typedef struct {
  char *read_buf;
  char *write_buf;
  size_t total_capacity;
  size_t write_idx; // For tracking write index of the write buffer.
} ReadWriteBuff;
//  Initializes Read and Write Buffers with pre-defined size.
int RW_init(ReadWriteBuff *RWB, const char *axiom, size_t size);
// Appends contents of the source string to the write buffer.
int RW_append(ReadWriteBuff *RWB, const char *src);
// Rotates read and write buffer contents.
int RW_swap(ReadWriteBuff *RWB);
// Destroys references of buffers for cleanup.
void RW_destroy(ReadWriteBuff *RWB);

#endif // !BUFFER

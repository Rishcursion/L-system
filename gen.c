#include "gen.h"
#include "buffer_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate(ReadWriteBuff *RWB, Grammar *Lsys) {
  /* 	Ok so now the buffer is initialzed with the axiom, the role of this
     function is now to use the CFG postulates and recursively substitute the
     initial value a.k.a the axiom.
  */
  for (int i = 0; RWB->read_buf[i] != '\0'; i++) {
    char symbol[2] = {RWB->read_buf[i], '\0'};
    char *rule = Lsys->postulates[(unsigned char)symbol[0]];
    if (rule == NULL) {
      RW_append(RWB, symbol);
    } else {
      RW_append(RWB, rule);
    }
  }
  RW_swap(RWB);
}

/* Initializes the context-free grammar for the L-system with a specified axiom
and associated postulates. Postulates are stored in an ASCII look-up table for
quick access. Ensure that the grammar is context-free, otherwise postulates will
be over-written.
*/
void G_init(Grammar *G, char **grammar, int rule_count) {
  G->axiom = grammar[0];
  memset(G->postulates, 0, sizeof(G->postulates));
  for (int i = 1; i < rule_count; i += 2) {
    G->postulates[(unsigned char)grammar[i][0]] = grammar[i + 1];
  }
}

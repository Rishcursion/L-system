#ifndef gen
#include "buffer_struct.h"
#include <stddef.h>
/* axiom: F-F-F-F
postulate: F-> F-F+F+FF-F,
need a way to look up the char in the read buffer i.e. F and the associated rule
to be followed, can technically cheat as there is only one symbol in the axiom
F, and there are no postulates in  L-systems that substitute + or -.
But for extensibility, we shall use an ASCII look-up table using char indices as
look-up index.
*/

typedef struct {
  char *axiom;
  char *postulates[256];
} Grammar;

void G_init(Grammar *Lsys, char **postulates, int rule_count);
void generate(ReadWriteBuff *RWB, Grammar *Lsys);
void calculate(ReadWriteBuff *RWB);
void createSVG(char **directions);
#endif // !gen

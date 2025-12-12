#include "buffer_struct.h"
#include "gen.h"
#include "turtle.h"
#include <stdio.h>
#include <stdlib.h>

typedef int (*ActionFunc)(Turtle *T, Stack *S, float turn_angle,
                          float step_size);

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("Insufficient Number of Arguments... exiting");
    return EXIT_FAILURE;
  }
  // Struct Initialization for initial stack push
  Grammar G;
  ReadWriteBuff RWB;
  Turtle T;
  Stack S;

  // Extracting command line arguments
  int num_iters = atoi(argv[1]);
  float initial_angle = atof(argv[2]);

  // Initializing structs
  G_init(&G, &argv[3], argc - 4);
  RW_init(&RWB, G.axiom, 200 * 1024 * 1024);

  St_init(&T, 0, 0, -90);

  S_init(&S);
  ActionFunc Table[256];
  for (int i = 0; i < 256; i++) {
    Table[i] = &action_do_nothing;
  }
  Table['F'] = &action_measure;
  Table['G'] = &action_measure;
  Table['+'] = &action_turn_left;
  Table['-'] = &action_turn_right;
  Table['['] = &action_save_state;
  Table[']'] = &action_restore_state;

  for (int i = 0; i < num_iters; i++) {
    generate(&RWB, &G);
  }
  for (char *c = RWB.read_buf; *c != '\0'; c += 1) {
    Table[(int)c[0]](&T, &S, initial_angle, 20);
  }
  float padding = 20.0f;
  float width = (T.max_x - T.min_x) + (padding * 2);
  float height = (T.max_y - T.min_y) + (padding * 2);
  float view_x = T.min_x - padding;
  float view_y = T.min_y - padding;
  printf("<svg viewBox='%.2f %.2f %.2f %.2f' "
         "xmlns='http://www.w3.org/2000/svg'>\n",
         view_x, view_y, width, height);
  printf("<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='white'/>\n",
         view_x, view_y, width, height);
  St_init(&T, 0, 0, -90); // Reset Turtle (Position goes back to 0,0)
  S_init(&S);             // Reset Stack (Important!)

  // Point 'F' to the drawing function
  Table['F'] = &action_draw_line;
  Table['G'] = &action_draw_line;
  for (char *c = RWB.read_buf; *c != '\0'; c += 1) {
    Table[(unsigned char)c[0]](&T, &S, initial_angle, 20);
  }

  printf("</svg>\n");
}

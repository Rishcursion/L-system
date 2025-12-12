#ifndef turtle
#include "stddef.h"
#define STACKLENGTH 1024
typedef struct {
  float x;
  float y;
  float alpha;
  unsigned int color;
  float min_x, min_y;
  float max_x, max_y;
} Turtle;

typedef struct {
  Turtle stack[STACKLENGTH];
  int top;
  int capacity;
} Stack;

// Stack Functions
int S_push(Stack *stack, Turtle *turt);
Turtle S_pop(Stack *stack);
int S_init(Stack *stack);

// Calculation Functions
int St_init(Turtle *turt, float x, float y, float a);
int action_draw_line(Turtle *turt, Stack *stack, float turn_angle,
                     float step_size);
int action_turn_left(Turtle *turt, Stack *stack, float turn_angle,
                     float step_size);
int action_turn_right(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size);
int action_save_state(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size);
int action_restore_state(Turtle *turt, Stack *stack, float turn_angle,
                         float step_size);
int action_do_nothing(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size);
int action_measure(Turtle *turt, Stack *, float, float);
#endif // !turtle

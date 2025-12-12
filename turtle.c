#include "turtle.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// Stack Function Declarations
int S_init(Stack *stack) {
  stack->capacity = STACKLENGTH;
  stack->top = 0;
  return EXIT_SUCCESS;
}

int S_push(Stack *stack, Turtle *turt) {
  // Check for stack overflow (hehe :D)
  if (stack->top == stack->capacity) { // Can't accept any new states
    return EXIT_FAILURE;
  }
  stack->stack[stack->top] = *turt;
  stack->top += 1;
  return EXIT_SUCCESS;
}

Turtle S_pop(Stack *stack) {
  if (stack->top == 0) {
    Turtle default_turt = {0.0, 0.0, 90.0, 0x00FF00};
    return default_turt;
  }
  stack->top -= 1;
  return stack->stack[stack->top];
}

// Turtle Function Declarations
int St_init(Turtle *turt, float x, float y, float a) {
  turt->x = x;
  turt->y = y;
  turt->alpha = a;
  turt->color =
      rand() % (0xEEEEEE - 0x000000) + 0x000000; // Randomly chooses the color
  ;
  turt->min_x = 1000000.0f;
  turt->min_y = 1000000.0f;
  turt->max_x = -1000000.0f;
  turt->max_y = -1000000.0f;
  return EXIT_SUCCESS;
}

int action_measure(Turtle *turt, Stack *stack, float turn_angle,
                   float step_size) {
  // 1. Do the Move Math
  double rad = turt->alpha * (3.1415926 / 180.0);
  turt->x += step_size * cos(rad);
  turt->y += step_size * sin(rad);

  // 2. Update Bounds (Check against the new position)
  if (turt->x < turt->min_x)
    turt->min_x = turt->x;
  if (turt->x > turt->max_x)
    turt->max_x = turt->x;
  if (turt->y < turt->min_y)
    turt->min_y = turt->y;
  if (turt->y > turt->max_y)
    turt->max_y = turt->y;

  return EXIT_SUCCESS;
}

int action_draw_line(Turtle *turt, Stack *stack, float turn_angle,
                     float step_size) {
  float old_x = turt->x;
  float old_y = turt->y;
  double rad_cost = 3.1415926 / 180;
  turt->x += step_size * cos(turt->alpha * rad_cost);
  turt->y += step_size * sin(turt->alpha * rad_cost);
  printf("<line x1='%f' y1='%f' x2='%f' y2='%f' stroke='black'/>\n", old_x,
         old_y, turt->x, turt->y);
  return EXIT_SUCCESS;
}

int action_turn_left(Turtle *turt, Stack *stack, float turn_angle,
                     float step_size) {
  turt->alpha -= turn_angle;
  return EXIT_SUCCESS;
}
int action_turn_right(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size) {
  turt->alpha += turn_angle;
  return EXIT_SUCCESS;
}

int action_save_state(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size) {
  S_push(stack, turt);
  return EXIT_SUCCESS;
}
int action_restore_state(Turtle *turt, Stack *stack, float turn_angle,
                         float step_size) {
  // 1. Pop the old state
  Turtle saved_state = S_pop(stack);

  // 2. SAVE the current global knowledge (Bounds)
  // We want the 'widest' limits we have seen SO FAR, whether from
  // the current path OR the path we are about to restore.
  float current_min_x = turt->min_x;
  float current_max_x = turt->max_x;
  float current_min_y = turt->min_y;
  float current_max_y = turt->max_y;

  // 3. Overwrite the turtle (Teleport back to the fork)
  *turt = saved_state;

  // 4. RESTORE / MERGE the global knowledge
  // If the saved state had 'smaller' knowledge, we force it to expand
  // to remember what we just saw in the branch.
  if (current_min_x < turt->min_x)
    turt->min_x = current_min_x;
  if (current_max_x > turt->max_x)
    turt->max_x = current_max_x;
  if (current_min_y < turt->min_y)
    turt->min_y = current_min_y;
  if (current_max_y > turt->max_y)
    turt->max_y = current_max_y;

  return EXIT_SUCCESS;
}
int action_do_nothing(Turtle *turt, Stack *stack, float turn_angle,
                      float step_size) {
  return EXIT_SUCCESS;
}

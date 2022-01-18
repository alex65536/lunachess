#ifndef EVAL_H
#define EVAL_H

#include "board.h"
#include "defs.h"
#include "globals.h"

// temporarily here:
bool gives_check(int move);

// the main evaluation function:
int evaluate();

// SEE and helper functions:
// int see(int move);
// int estimated_move_value(int move);

#endif

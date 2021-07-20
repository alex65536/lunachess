/* ENGINE.H: contains the 'intelligent' part of the program, such as the board
 * evaluation function, the move scoring function, and the negamax search
 * algorithm for finding the best move.
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"
#include "globals.h"

/* ---------- the search functions ---------- */
// init_search(): to initialize search variables
void init_search();

// score_move(): the move scoring function
inline int score_move(int move);

// evaluate(): the board evaluation function
inline int evaluate();

// the search algorithm for finding the best move:
int negamax(int depth);
int negamax_helper(int depth, int alpha, int beta);
int quiescence(int depth, int alpha, int beta);

#endif

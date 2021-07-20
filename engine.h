/* ENGINE.H: contains the 'intelligent' part of the program, such as the board
 * evaluation function, the move ordering function, and the minimax search
 * algorithm for finding the best move.
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "board.h"

// evaluate(): the board evaluation function
static inline int evaluate();

// search: a class for searching a board
class search {
public:
  int nodes_evaluated;
  search(board* b);

  // the search algorithm for finding the best move:
  int negamax(int depth);
  inline int negamax_helper(int depth, int alpha, int beta);
  inline int quiescence(int depth, int alpha, int beta);

private:
  int best_move;
  int best_score;
  board* b;
};

#endif

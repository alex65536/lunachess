#include <assert.h>
#include <stdio.h>

#include "board.h"
#include "consts.h"
#include "defs.h"
#include "engine.h"
#include "timer.h"

void print_move(int m);
int perft(board* b, int depth);

void print_bitboard(U64 bb) {
    for (int i = 0; i < 64; i++) {
        printf("%c ", ((bb >> i) & 1) ? 'x' : '.');
        if (i % 8 == 7) printf("\n");
    }
}

int main(int argc, char** argv) {
  init_consts();

  char* FEN = "rnbqkbnr/pppp3p/6p1/3Npp1Q/4P3/8/PPPP1PPP/R1B1KBNR b KQkq - 1 4";
  board b(FEN);

  U64 pinned = b.pinned_pieces();
  print_bitboard(pinned);

  /* timer t;
  t.start();
  // printf("%d\n", perft(&b, 5));
  // printf("best eval found: %d\n", alphabeta_helper(&b, 5, -INF, INF, true));
  // move m = alphabeta(&b, 5);
  // print_move(m.move_code);
  t.stop();
  t.print_duration(); */

  return 0;
}

void print_move(int m) {
  int to = (m >> 26) & 0x3F;
  int from = (m >> 20) & 0x3F;

  char* move_str = new char[6];
  move_str[5] = '\0';
  move_str[4] = '\0'; // TODO: REMOVE THIS

  move_str[0] = ((from % 8) + 'a');
  move_str[1] = (8 - (from / 8) + '0');
  move_str[2] = ((to % 8) + 'a');
  move_str[3] = (8 - (to / 8) + '0');

  // TODO: promotion piece

  printf("%s\n", move_str);
}

int perft(board* b, int depth) {
  int num_moves;
  int* moves = b->get_moves(num_moves);
  if (depth == 1) {
    int n_copy = num_moves;
    for (int i = 0; i < n_copy; i++) {
      if (!b->make_move(moves[i])) num_moves--;
      b->undo_move();
    }
    return num_moves;
  }

  int sum = 0;
  for (int i = 0; i < num_moves; i++) {
    if (b->make_move(moves[i])) {
      sum += perft(b, depth - 1);
    }
    b->undo_move();
  }

  return sum;
}

#include "utils.h"

// avoid including the huge Windows.h header more than once:
#ifdef _WIN32
  #include <Windows.h>
#endif

// print a move given the move code. does NOT print a new line!
void print_move(int move) {
  int to = MOVE_TO(move);
  int from = MOVE_FROM(move);

  char* move_str = new char[6];

  move_str[0] = ((from % 8) + 'a');
  move_str[1] = (8 - (from / 8) + '0');
  move_str[2] = ((to % 8) + 'a');
  move_str[3] = (8 - (to / 8) + '0');
  move_str[4] = (MOVE_IS_PROMOTION(move)) ?
                  PIECE_CHARS[MOVE_PROMOTION_PIECE(move)] : '\0';
  move_str[5] = '\0';

  printf("%s", move_str);
}

// gets the time in milliseconds (as an int - we assume no one's
// going to run this for 50 days straight)
int get_time() {
  auto duration = high_resolution_clock::now().time_since_epoch();
  auto millis = duration_cast<milliseconds>(duration).count();
  return (int) millis;
}

// listen to GUI input while in search. OS-dependent:
// (code is from VICE engine by richard allbert)
bool input_waiting() {
  #ifndef _WIN32
    fd_set readfds;
    struct timeval tv;
    FD_ZERO(&readfds);
    FD_SET(fileno(stdin), &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(16, &readfds, 0, 0, &tv);
    return (FD_ISSET(fileno(stdin), &readfds));
  #else
    static int init = 0, pipe;
    static HANDLE inh;
    DWORD dw;
    if (!init) {
      init = 1;
      inh = GetStdHandle(STD_INPUT_HANDLE);
      pipe = !GetConsoleMode(inh, &dw);
      if (!pipe) {
        SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
        FlushConsoleInputBuffer(inh);
      }
    }

    if (pipe) {
      if (!PeekNamedPipe(inh, NULL, 0, NULL, &dw, NULL)) return 1;
      return dw;
    }
    else {
      GetNumberOfConsoleInputEvents(inh, &dw);
      return dw <= 1 ? 0 : dw;
    }
  #endif
}

// read GUI input:
// (code is from BBC engine)
void read_input() {
  int bytes;
  char input[256] = "";
  char* endc;

  if (input_waiting()) {
    stop_search = true;
    do {
      bytes = read(fileno(stdin), input, 256);
    } while (bytes < 0);

    endc = strchr(input, '\n');
    if (endc) *endc = 0;

    if (strlen(input) > 0) {
      if (!strncmp(input, "quit", 4) || !strncmp(input, "stop", 4)) {
        quit_flag = true;
      }
    }
  }
}

// make sure we didn't get any stop or quit command, and that we still have time:
void communicate() {
  if (time_set && (get_time() > stop_time)) stop_search = true;
  read_input();
}

long perft(int depth, bool root) {
  int moves[MAX_POSITION_MOVES];
  int num_moves = b.get_moves(moves);
  if (depth == 1) return num_moves;

  long sum = 0;
  for (int i = 0; i < num_moves; i++) {
    b.make_move(moves[i]);
    if (root) {
      long branch = perft(depth - 1, false);
      print_move(moves[i]);
      printf(": %llu\n", branch);
      sum += branch;
    }
    else sum += perft(depth - 1, false);
    b.undo_move();
  }

  return sum;
}

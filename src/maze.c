#include "s21_maze.h"

int main(void) {
  srand(time(NULL));
  state_machine();
  return 0;
}

void state_machine() {
  initscr();
  Labirint_t laba;
  Tesei_t tesei;
  StateMachine state = START;
  bool go = true;
  int input;

  char k;
  int b_limit, d_limit;
  cave_t cave;

  while (go) {
    switch (state) {
      case START:
        printw(" 1) Labirint\n 2) Cave\n");
        scanw("%d", &input);
        if (input == 1) state = LABA;
        if (input == 2) state = CAVE;
        clear();
        break;
      case LABA:
        printw(" 1) Generate\n 2) Parse\n");
        scanw("%d", &input);
        if (input == 1) state = GENERATE_LABA;
        if (input == 2) state = PARSE_LABA;
        clear();
        break;
      case CAVE:
        int delay_timer = 1;
        printw("Enter b_limit\n");
        scanw("%d", &b_limit);
        printw("Enter d_limit\n");
        scanw("%d", &d_limit);
        printw("Enter delay (default 1)\n");
        scanw("%d", &delay_timer);
        clear();
        cave.b_limit = b_limit;
        cave.d_limit = d_limit;
        int err_cave = file_parser(&cave);
        noecho();
        curs_set(0);
        if (!err_cave) {
          generate_cave(&cave);
          halfdelay(delay_timer);
          while (k != 'q') {
            k = getch();
            print_cave(cave);
            if (k == 'f') {
              generate_cave(&cave);
            }
            if (k == 'a')
              while (1) {
                k = getch();
                generate_cave(&cave);
                print_cave(cave);
                if (k == 'q') break;
              }
            mvprintw(0, 0, "Press f to manual generate cave");
            mvprintw(1, 0, "Press a to auto generate cave");
            mvprintw(2, 0, "Press q to exit");
          }
        }
        clear();
        state = EXIT_CAVE;
        break;
      case PARSE_LABA:
        int err = 0;
        char* path = (char*)calloc(256, sizeof(char));
        printw("input path: ");
        scanw("%s", path);
        err = parse_Labirint(&laba, path);
        free(path);
        printw("%d", err);
        if (err == 0) {
          curs_set(0);
          print_labirint(&laba);
          curs_set(1);
          state = RANDOM_ROOM;
          clear();
        } else {
          state = EXIT;
          clear();
        }
        break;
      case GENERATE_LABA:
        int rows, cols;
        printw("input rows(min 1, max 50): ");
        scanw("%d", &rows);
        clear();
        printw("input cols(min 1, max 50): ");
        scanw("%d", &cols);
        clear();
        if (rows > 50) rows = 50;
        if (cols > 50) cols = 50;
        if (rows < 1) rows = 1;
        if (cols < 1) cols = 1;
        create_Labirint(&laba, rows, cols);
        zero_Labirint(&laba);
        generate_Labirint(&laba);
        curs_set(0);
        print_labirint(&laba);
        export_labirint(&laba);
        curs_set(1);
        state = RANDOM_ROOM;
        clear();
        break;
      case RANDOM_ROOM:
        print_labirint(&laba);

        mvprintw(0, laba.cols * 2 + 2, " 1) Random rooms");
        mvprintw(2, laba.cols * 2 + 2, " 2) Set room\n");

        mvscanw(5, laba.cols * 2 + 2, "%d", &input);
        clear();
        print_labirint(&laba);

        if (input == 1) init_random_room(&laba, &tesei);
        if (input == 2) {
          int sroom, lroom;
          mvprintw(0, laba.cols * 2 + 2,
                   "Start room (0 - %d): ", laba.count_room);
          mvscanw(5, laba.cols * 2 + 2, "%d", &sroom);
          if (sroom <= 0)
            sroom = 0;
          else if (sroom >= 100)
            sroom = 100;
          clear();
          print_labirint(&laba);
          mvprintw(0, laba.cols * 2 + 2,
                   "End room (0 - %d): ", laba.count_room);
          mvscanw(5, laba.cols * 2 + 2, "%d", &lroom);
          if (lroom <= 0)
            lroom = 0;
          else if (lroom >= 100)
            lroom = 99;
          get_room(&tesei, sroom, lroom);
          clear();
          print_labirint(&laba);
        }
        mvprintw(0, laba.cols * 2 + 2, "1) AI ");
        mvprintw(3, laba.cols * 2 + 2, "2) Line");
        mvscanw(5, laba.cols * 2 + 2, "%d", &input);
        if (input == 1) state = AI;
        if (input == 2) state = LINE;
        clear();
        break;
      case AI:
        int count = 0;
        print_labirint(&laba);
        mvprintw(3, laba.cols * 2 + 2, "How Tesei go? (default 100)");
        if (mvscanw(5, laba.cols * 2 + 2, "%d", &count) == 0 || count < 1)
          count = 100;
        clear();
        halfdelay(1);
        curs_set(0);
        tesei_adventure(&laba, &tesei, count);
        cbreak();
        getch();
        curs_set(1);
        state = EXIT;
        break;
      case LINE:
        lane_adventure(&laba, &tesei);
        curs_set(0);
        print_labirint(&laba);
        print_tesei(&tesei, 1);
        mvprintw(0, laba.cols * 2 + 2, "Press any key to exit");
        getch();
        curs_set(1);
        state = EXIT;
        break;
      case EXIT:
        if (!err) {
          free_Labirint(&laba);
          free_tesei(&tesei);
        }
        go = false;
        break;
      case EXIT_CAVE:
        clear_matrix(&cave);
        go = false;
        break;
      default:
        break;
    }
  }
  endwin();
}
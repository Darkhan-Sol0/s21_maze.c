#include "s21_maze.h"

void print_labirint(Labirint_t* laba) {
  int k = 0;
  clear();
  for (int i = 0; i < laba->rows; i++) {
    for (int j = 0; j < laba->cols; j++) {
      if (laba->labirint[i][j].wall_v != 0 &&
          laba->labirint[i][j].wall_h == 0) {
        mvaddch(i * 2, j * 2 + 1, ACS_VLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_VLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_VLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_LLCORNER);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_LTEE);
      }

      if (laba->labirint[i][j].wall_h != 0 &&
          laba->labirint[i][j].wall_v == 0) {
        mvaddch(i * 2 + 1, j * 2, ACS_HLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_HLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_URCORNER);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_HLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_TTEE);
      }

      if (laba->labirint[i][j].wall_h != 0 &&
          laba->labirint[i][j].wall_v != 0) {
        mvaddch(i * 2, j * 2 + 1, ACS_VLINE);
        mvaddch(i * 2 + 1, j * 2, ACS_HLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_LRCORNER);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h == 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_RTEE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v == 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_BTEE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_PLUS);
      }

      if (laba->labirint[i][j].wall_h == 0 &&
          laba->labirint[i][j].wall_v == 0) {
        // if (i + 1 < laba->rows && j + 1 < laba->cols &&
        // laba->labirint[i+1][j].wall_v != 0 && laba->labirint[i][j+1].wall_h
        // == 0)
        //   mvaddch(i * 2 + 1, j * 2 + 1, ACS_VLINE);
        // if (i + 1 < laba->rows && j + 1 < laba->cols &&
        // laba->labirint[i+1][j].wall_v == 0 && laba->labirint[i][j+1].wall_h
        // != 0)
        //   mvaddch(i * 2 + 1, j * 2 + 1, ACS_HLINE);
        if (i + 1 < laba->rows && j + 1 < laba->cols &&
            laba->labirint[i + 1][j].wall_v != 0 &&
            laba->labirint[i][j + 1].wall_h != 0)
          mvaddch(i * 2 + 1, j * 2 + 1, ACS_ULCORNER);
      }

      // mvprintw(i * 2, j * 2, "%d",laba->labirint[i][j].visit);
      // mvprintw(i * 2, j * 2 + laba->rows * 2 + 1, "%d",
      // laba->labirint[i][j].wall_h);

      // if (laba->krot.x_pos == j && laba->krot.y_pos == i && check_map(laba))
      // mvprintw(i * 2, j * 2, "%c", 'K');
      k++;
    }
    k = 0;
  }
  refresh();
}

Check_ways_t check_line_ways(Tesei_t* tesei, int y, int x) {
  Check_ways_t result;
  result.up_way = 0;
  result.right_way = 0;
  result.down_way = 0;
  result.left_way = 0;

  if (y - 1 >= 0) {
    if (tesei->map[y - 1][x].wall_h == 0) {
      result.up_way = 1;
    }
  }
  if (x + 1 < tesei->map_cols) {
    if (tesei->map[y][x].wall_v == 0) {
      result.right_way = 1;
    }
  }
  if (y + 1 < tesei->map_rows) {
    if (tesei->map[y][x].wall_h == 0) {
      result.down_way = 1;
    }
  }
  if (x - 1 >= 0) {
    if (tesei->map[y][x - 1].wall_v == 0) {
      result.left_way = 1;
    }
  }
  return result;
}

void print_tesei(Tesei_t* tesei, int line) {
  Check_ways_t room;
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
  for (int i = 0; i < tesei->map_rows; i++)
    for (int j = 0; j < tesei->map_cols; j++) {
      if (have_in_way(tesei, tesei->map[i][j].numder)) {
        room = check_line_ways(tesei, i, j);
        attron(COLOR_PAIR(1));
        mvaddch(i * 2, j * 2, ACS_BULLET);

        if (room.up_way == 1 && room.down_way == 1 && room.right_way == 0 &&
            room.left_way == 0)
          mvaddch(i * 2, j * 2, ACS_VLINE);
        else if (room.up_way == 0 && room.down_way == 0 &&
                 room.right_way == 1 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_HLINE);
        else if (room.up_way == 1 && room.down_way == 0 &&
                 room.right_way == 1 && room.left_way == 0)
          mvaddch(i * 2, j * 2, ACS_LLCORNER);
        else if (room.up_way == 1 && room.down_way == 0 &&
                 room.right_way == 0 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_LRCORNER);
        else if (room.up_way == 0 && room.down_way == 1 &&
                 room.right_way == 1 && room.left_way == 0)
          mvaddch(i * 2, j * 2, ACS_ULCORNER);
        else if (room.up_way == 0 && room.down_way == 1 &&
                 room.right_way == 0 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_URCORNER);

        else if (room.up_way == 1 && room.down_way == 1 &&
                 room.right_way == 1 && room.left_way == 0)
          mvaddch(i * 2, j * 2, ACS_LTEE);
        else if (room.up_way == 1 && room.down_way == 1 &&
                 room.right_way == 0 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_RTEE);

        else if (room.up_way == 1 && room.down_way == 0 &&
                 room.right_way == 1 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_BTEE);
        else if (room.up_way == 0 && room.down_way == 1 &&
                 room.right_way == 1 && room.left_way == 1)
          mvaddch(i * 2, j * 2, ACS_TTEE);

        attroff(COLOR_PAIR(1));
      }
      if (tesei->map[i][j].numder == tesei->last_room) {
        attron(COLOR_PAIR(2));
        mvaddch(i * 2, j * 2, ' ');
        attroff(COLOR_PAIR(2));
      }
      if (tesei->map[i][j].numder == tesei->start_room) {
        attron(COLOR_PAIR(3));
        mvaddch(i * 2, j * 2, ' ');
        attroff(COLOR_PAIR(3));
      }
      if (line == 0 && tesei->x_pos == j && tesei->y_pos == i)
        mvprintw(i * 2, j * 2, "%c", 'T');
    }
  // Check_ways_t way = check_ways(tesei);
  // mvprintw(5, tesei->map_cols * 2 + 2, "U:%d R:%d D:%d L:%d CW:%d -- %d",
  // way.up_way, way.right_way, way.down_way, way.left_way,
  // tesei->map[tesei->y_pos][tesei->x_pos].crossway, tesei->way.steps);

  // Room_pos_t rom = room_pos(tesei,
  // tesei->map[tesei->y_pos][tesei->x_pos].numder); mvprintw(7, tesei->map_cols
  // * 2 + 2, "%d %d %d", tesei->map[tesei->y_pos][tesei->x_pos].numder,
  // rom.y_pos, rom.x_pos);

  refresh();
}
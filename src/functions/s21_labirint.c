#include "s21_maze.h"

int parse_Labirint(Labirint_t* laba, char* path) {
  int code = 0;
  FILE* file = fopen(path, "r");
  if (file == NULL) {
    mvprintw(0, laba->cols, "Cannot open file or read! Press any key to exit");
    code = 1;
    getch();
  } else {
    fscanf(file, "%d %d", &laba->rows, &laba->cols);

    create_Labirint(laba, laba->rows, laba->cols);
    zero_Labirint(laba);

    for (int i = 0; i < laba->rows; i++)
      for (int j = 0; j < laba->cols; j++) {
        fscanf(file, "%d", &laba->labirint[i][j].wall_v);
      }

    for (int i = 0; i < laba->rows; i++)
      for (int j = 0; j < laba->cols; j++) {
        fscanf(file, "%d", &laba->labirint[i][j].wall_h);
      }
    fclose(file);
  }
  return code;
}

void export_labirint(Labirint_t* laba) {
  FILE* file = fopen("generate_maze.txt", "w");
  fprintf(file, "%d %d\n", laba->rows, laba->cols);
  fprintf(file, "\n");
  for (int i = 0; i < laba->rows; i++) {
    for (int j = 0; j < laba->cols; j++)
      fprintf(file, "%d ", laba->labirint[i][j].wall_v);
    fprintf(file, "\n");
  }
  fprintf(file, "\n");
  for (int i = 0; i < laba->rows; i++) {
    for (int j = 0; j < laba->cols; j++)
      fprintf(file, "%d ", laba->labirint[i][j].wall_h);
    fprintf(file, "\n");
  }
  fclose(file);
}

void create_Labirint(Labirint_t* laba, int rows, int cols) {
  laba->rows = rows;
  laba->cols = cols;
  laba->labirint = (Room_t**)calloc(laba->rows, sizeof(Room_t*));
  for (int i = 0; i < laba->rows; i++)
    laba->labirint[i] = (Room_t*)calloc(laba->cols, sizeof(Room_t));
}

void free_Labirint(Labirint_t* laba) {
  for (int i = 0; i < laba->rows; i++) free(laba->labirint[i]);
  free(laba->labirint);
  laba->rows = 0;
  laba->cols = 0;
}

void zero_Labirint(Labirint_t* laba) {
  int num = 0;
  for (int i = 0; i < laba->rows; i++)
    for (int j = 0; j < laba->cols; j++) {
      laba->labirint[i][j].wall_v = 1;
      laba->labirint[i][j].wall_h = 1;
      laba->labirint[i][j].numder = num;
      laba->labirint[i][j].visit = 1;
      num++;
    }
  laba->count_room = num;
}

void generate_Labirint(Labirint_t* laba) {
  start_spawn(laba);
  while (true) {
    move_krot(laba);
    int rooms = check_map(laba);
    if (rooms <= 0) break;
  }
}

int check_map(Labirint_t* laba) {
  int result = 0;
  for (int i = 0; i < laba->rows; i++)
    for (int j = 0; j < laba->cols; j++) {
      if (laba->labirint[i][j].visit != 0) {
        result += 1;
      }
    }
  return result;
}

void spawn_on_room(Labirint_t* laba) {
  int index = rand() % laba->count_room;
  for (int i = 0; i < laba->rows; i++)
    for (int j = 0; j < laba->cols; j++) {
      if (laba->labirint[i][j].numder == index &&
          laba->labirint[i][j].visit == 0) {
        laba->krot.x_pos = j;
        laba->krot.y_pos = i;
        Check_neighbor_t check = check_neighbor(laba);
        int vis =
            check.down_vis + check.left_vis + check.right_vis + check.up_vis;
        if (vis > 0) {
          i = laba->rows;
          break;
        } else {
          index++;
        }
      }
    }
  index = 0;
}

void start_spawn(Labirint_t* laba) {
  int index = rand() % laba->count_room;
  for (int i = 0; i < laba->rows; i++)
    for (int j = 0; j < laba->cols; j++) {
      if (laba->labirint[i][j].numder == index &&
          laba->labirint[i][j].visit == 1) {
        laba->krot.x_pos = j;
        laba->krot.y_pos = i;
        i = laba->rows;
        change_visits(laba);
        break;
      }
    }
}

Check_neighbor_t check_neighbor(Labirint_t* laba) {
  Check_neighbor_t result;
  result.right_vis = 0;
  result.left_vis = 0;
  result.down_vis = 0;
  result.up_vis = 0;

  if (laba->krot.x_pos + 1 < laba->cols &&
      laba->labirint[laba->krot.y_pos][laba->krot.x_pos + 1].visit == 1)
    result.right_vis = 1;
  if (laba->krot.x_pos - 1 >= 0 &&
      laba->labirint[laba->krot.y_pos][laba->krot.x_pos - 1].visit == 1)
    result.left_vis = 1;
  if (laba->krot.y_pos + 1 < laba->rows &&
      laba->labirint[laba->krot.y_pos + 1][laba->krot.x_pos].visit == 1)
    result.down_vis = 1;
  if (laba->krot.y_pos - 1 >= 0 &&
      laba->labirint[laba->krot.y_pos - 1][laba->krot.x_pos].visit == 1)
    result.up_vis = 1;
  return result;
}

void change_visits(Labirint_t* laba) {
  laba->labirint[laba->krot.y_pos][laba->krot.x_pos].visit = 0;
}

void move_krot(Labirint_t* laba) {
  Check_neighbor_t check = check_neighbor(laba);
  if (check.down_vis != 0 || check.left_vis != 0 || check.right_vis != 0 ||
      check.up_vis != 0) {
    rand_move_krot(laba);
  } else {
    spawn_on_room(laba);
  }
  change_visits(laba);
}

void rand_move_krot(Labirint_t* laba) {
  Check_neighbor_t vis = check_neighbor(laba);

  int mass_all = (vis.up_vis + vis.right_vis + vis.down_vis + vis.left_vis) > 0
                     ? vis.up_vis + vis.right_vis + vis.down_vis + vis.left_vis
                     : 1;
  int mass_UP = vis.up_vis * 100 / mass_all;
  int mass_right = (vis.right_vis * 100 / mass_all) + mass_UP;
  int mass_down = (vis.down_vis * 100 / mass_all) + mass_right;
  int mass_left = (vis.left_vis * 100 / mass_all) + mass_down;
  int velocity = rand() % 100;

  if (velocity >= 0 && velocity < mass_UP) {
    laba->labirint[laba->krot.y_pos - 1][laba->krot.x_pos].wall_h = 0;
    move_up_krot(laba);
  } else if (velocity < mass_right) {
    laba->labirint[laba->krot.y_pos][laba->krot.x_pos].wall_v = 0;
    move_right_krot(laba);
  } else if (velocity < mass_down) {
    laba->labirint[laba->krot.y_pos][laba->krot.x_pos].wall_h = 0;
    move_down_krot(laba);
  } else if (velocity < mass_left) {
    laba->labirint[laba->krot.y_pos][laba->krot.x_pos - 1].wall_v = 0;
    move_left_krot(laba);
  }
}

void move_left_krot(Labirint_t* laba) { laba->krot.x_pos -= 1; }
void move_right_krot(Labirint_t* laba) { laba->krot.x_pos += 1; }
void move_up_krot(Labirint_t* laba) { laba->krot.y_pos -= 1; }
void move_down_krot(Labirint_t* laba) { laba->krot.y_pos += 1; }
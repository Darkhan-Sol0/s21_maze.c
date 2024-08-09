#include "s21_maze.h"

void tesei_adventure(Labirint_t* laba, Tesei_t* tesei, int count) {
  init_room_map(laba, tesei, count);
  spawn_tesei(tesei);
  print_labirint(laba);
  print_tesei(tesei, 0);
  while (tesei->counter >= 0) {
    if (getch() == 'q') break;
    change_visits_tesei(tesei);
    move_tesei(tesei);
    add_way_map(tesei);
    print_labirint(laba);
    print_tesei(tesei, 0);
    mvprintw(0, laba->cols * 2 + 2, "Press q to stop ai");

    if (check_finish(tesei) != 0) {
      tesei->winer = 1;
      set_finish_way(tesei);
      export_tesei(tesei);
      if (tesei->counter >= 0) spawn_tesei(tesei);
    }
  }
  print_labirint(laba);
  print_tesei(tesei, 0);
  mvprintw(0, laba->cols * 2 + 2, "Press any key to exit");
  mvprintw(10, tesei->map_cols * 2 + 2, "Tesei complate laba, press q to ext");
}

void lane_adventure(Labirint_t* laba, Tesei_t* tesei) {
  init_room_map(laba, tesei, 1);
  spawn_tesei(tesei);
  while (true) {
    change_visits_tesei(tesei);
    move_tesei(tesei);
    add_way_map(tesei);
    if (check_finish(tesei) != 0) {
      tesei->winer = 1;
      export_tesei(tesei);
      break;
    }
  }
}

void init_room_map(Labirint_t* laba, Tesei_t* tesei, int count) {
  tesei->number = 0;
  tesei->map_rows = laba->rows;
  tesei->map_cols = laba->cols;
  tesei->counter = count;
  init_way_map(tesei);
  tesei->map = (Room_t**)calloc(tesei->map_rows, sizeof(Room_t*));
  for (int i = 0; i < tesei->map_rows; i++)
    tesei->map[i] = (Room_t*)calloc(tesei->map_cols, sizeof(Room_t));

  for (int i = 0; i < tesei->map_rows; i++)
    for (int j = 0; j < tesei->map_cols; j++) {
      tesei->map[i][j].numder = laba->labirint[i][j].numder;
      tesei->map[i][j].wall_h = laba->labirint[i][j].wall_h;
      tesei->map[i][j].wall_v = laba->labirint[i][j].wall_v;
      tesei->map[i][j].visit = 1;
      tesei->map[i][j].mass = 5;
      tesei->map[i][j].crossway = 0;
    }
}

void init_random_room(Labirint_t* laba, Tesei_t* tesei) {
  do {
    tesei->start_room = rand() % laba->count_room;
    tesei->last_room = rand() % laba->count_room;
  } while (tesei->start_room == tesei->last_room);
}

void init_way_map(Tesei_t* tesei) {
  tesei->way.rooms = (int*)malloc(sizeof(int));
  tesei->way.steps = 0;
}

void get_room(Tesei_t* tesei, int start_room, int exit_room) {
  tesei->start_room = start_room;
  tesei->last_room = exit_room;
}

void free_tesei(Tesei_t* tesei) {
  for (int i = 0; i < tesei->map_rows; i++) free(tesei->map[i]);
  free(tesei->map);
}
void free_ways(Tesei_t* tesei) { free(tesei->way.rooms); }

void spawn_tesei(Tesei_t* tesei) {
  refresh_map(tesei);
  free_ways(tesei);
  init_way_map(tesei);
  tesei->winer = 0;
  tesei->counter--;
  for (int i = 0; i < tesei->map_rows; i++)
    for (int j = 0; j < tesei->map_cols; j++)
      if (tesei->map[i][j].numder == tesei->start_room) {
        tesei->x_pos = j;
        tesei->y_pos = i;
        i = tesei->map_rows;
        break;
      }
  tesei->number++;
  add_way_map(tesei);
}

Check_ways_t check_ways(Tesei_t* tesei) {
  Check_ways_t result;
  result.up_way = 0;
  result.right_way = 0;
  result.down_way = 0;
  result.left_way = 0;
  int crossway = 0;

  if (tesei->y_pos - 1 >= 0) {
    if (tesei->map[tesei->y_pos - 1][tesei->x_pos].visit != 0 &&
        tesei->map[tesei->y_pos - 1][tesei->x_pos].wall_h == 0) {
      result.up_way = tesei->map[tesei->y_pos - 1][tesei->x_pos].mass;
      if (result.up_way > 0) crossway += 1;
    }
  }
  if (tesei->x_pos + 1 < tesei->map_cols) {
    if (tesei->map[tesei->y_pos][tesei->x_pos + 1].visit != 0 &&
        tesei->map[tesei->y_pos][tesei->x_pos].wall_v == 0) {
      result.right_way = tesei->map[tesei->y_pos][tesei->x_pos + 1].mass;
      if (result.right_way > 0) crossway += 1;
    }
  }
  if (tesei->y_pos + 1 < tesei->map_rows) {
    if (tesei->map[tesei->y_pos + 1][tesei->x_pos].visit != 0 &&
        tesei->map[tesei->y_pos][tesei->x_pos].wall_h == 0) {
      result.down_way = tesei->map[tesei->y_pos + 1][tesei->x_pos].mass;
      if (result.down_way > 0) crossway += 1;
    }
  }
  if (tesei->x_pos - 1 >= 0) {
    if (tesei->map[tesei->y_pos][tesei->x_pos - 1].visit != 0 &&
        tesei->map[tesei->y_pos][tesei->x_pos - 1].wall_v == 0) {
      result.left_way = tesei->map[tesei->y_pos][tesei->x_pos - 1].mass;
      if (result.left_way > 0) crossway += 1;
    }
  }
  if (crossway > 1)
    tesei->map[tesei->y_pos][tesei->x_pos].crossway = 1;
  else
    tesei->map[tesei->y_pos][tesei->x_pos].crossway = 0;
  return result;
}

void move_tesei(Tesei_t* tesei) {
  Check_ways_t way = check_ways(tesei);

  int mass_all = (way.up_way + way.right_way + way.down_way + way.left_way) > 0
                     ? way.up_way + way.right_way + way.down_way + way.left_way
                     : 1;
  int mass_UP = way.up_way * 100 / mass_all;
  int mass_right = (way.right_way * 100 / mass_all) + mass_UP;
  int mass_down = (way.down_way * 100 / mass_all) + mass_right;
  int mass_left = (way.left_way * 100 / mass_all) + mass_down;
  int velocity = rand() % 100;

  if (velocity >= 0 && velocity < mass_UP)
    move_up_tesei(tesei);
  else if (velocity < mass_right)
    move_right_tesei(tesei);
  else if (velocity < mass_down)
    move_down_tesei(tesei);
  else if (velocity < mass_left)
    move_left_tesei(tesei);
  else {
    set_deadlock(tesei);
    export_tesei(tesei);
    spawn_tesei(tesei);
    return;
  }
}

void move_up_tesei(Tesei_t* tesei) { tesei->y_pos -= 1; }

void move_down_tesei(Tesei_t* tesei) { tesei->y_pos += 1; }

void move_right_tesei(Tesei_t* tesei) { tesei->x_pos += 1; }

void move_left_tesei(Tesei_t* tesei) { tesei->x_pos -= 1; }

void change_visits_tesei(Tesei_t* tesei) {
  tesei->map[tesei->y_pos][tesei->x_pos].visit = 0;
}

Room_pos_t room_pos(Tesei_t* tesei, int number) {
  Room_pos_t result;
  result.x_pos = -1;
  result.y_pos = -1;
  for (int i = 0; i < tesei->map_rows; i++) {
    for (int j = 0; j < tesei->map_cols; j++) {
      if (tesei->map[i][j].numder == number) {
        result.x_pos = j;
        result.y_pos = i;
        break;
      }
    }
    if (result.x_pos >= 0 && result.y_pos >= 0) break;
  }
  return result;
}

void set_deadlock(Tesei_t* tesei) {
  for (int k = tesei->way.steps - 1; k > 0; k--) {
    Room_pos_t room = room_pos(tesei, tesei->way.rooms[k]);
    if (tesei->map[room.y_pos][room.x_pos].crossway == 0)
      tesei->map[room.y_pos][room.x_pos].mass = 0;
    else if (tesei->map[room.y_pos][room.x_pos].crossway != 0)
      break;
  }
}

void set_finish_way(Tesei_t* tesei) {
  for (int k = tesei->way.steps - 1; k > 0; k--) {
    Room_pos_t room = room_pos(tesei, tesei->way.rooms[k]);
    tesei->map[room.y_pos][room.x_pos].mass = 9;
  }
}

void refresh_map(Tesei_t* tesei) {
  for (int i = 0; i < tesei->map_rows; i++)
    for (int j = 0; j < tesei->map_cols; j++) tesei->map[i][j].visit = 1;
}

int check_finish(Tesei_t* tesei) {
  int result = 0;
  if (tesei->map[tesei->y_pos][tesei->x_pos].numder == tesei->last_room)
    result = 1;
  return result;
}

void add_way_map(Tesei_t* tesei) {
  tesei->way.steps++;
  int* new_way =
      (int*)realloc(tesei->way.rooms, (tesei->way.steps) * sizeof(int));

  tesei->way.rooms = new_way;
  tesei->way.rooms[tesei->way.steps - 1] =
      tesei->map[tesei->y_pos][tesei->x_pos].numder;
}

void export_tesei(Tesei_t* tesei) {
  FILE* file = fopen("TESEI_AI.txt", "a+");

  fprintf(file,
          "Tesei-%d | wining - %d | steps - %d | start - %d | exit - %d\n",
          tesei->number, tesei->winer, tesei->way.steps, tesei->start_room,
          tesei->last_room);
  fprintf(file, "Way: \n");
  for (int i = 0; i < tesei->way.steps; i++)
    fprintf(file, "%d - %d | ", i, tesei->way.rooms[i]);

  fprintf(file, "\n \n");
  fclose(file);
}

int have_in_way(Tesei_t* tesei, int number) {
  int result = 0;
  for (int i = 0; i < tesei->way.steps; i++)
    if (number == tesei->way.rooms[i]) {
      result = 1;
      break;
    }
  return result;
}

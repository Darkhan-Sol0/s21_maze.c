#ifndef S21_OBJECTS_H
#define S21_OBJECTS_H

#include "s21_cave.h"
#include "s21_maze.h"

typedef struct {
  int** matrix;
  int rows;
  int cols;
  int b_limit;
  int d_limit;
} cave_t;

typedef struct {
  int x_pos;
  int y_pos;
} Room_pos_t;

typedef struct {
  int* rooms;
  int steps;
} Way_map_t;

typedef struct {
  int up_way;
  int right_way;
  int down_way;
  int left_way;
} Check_ways_t;

typedef enum {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
} list_way_t;

typedef struct {
  int up_vis;
  int right_vis;
  int down_vis;
  int left_vis;
} Check_neighbor_t;

typedef struct {
  int numder;
  int wall_v;
  int wall_h;
  int visit;
  int crossway;
  int mass;
} Room_t;

typedef struct {
  int x_pos;
  int y_pos;
} Krot_t;

typedef struct {
  int number;
  int map_rows;
  int map_cols;
  int x_pos;
  int y_pos;
  Room_t** map;
  Way_map_t way;
  int start_room;
  int last_room;
  int winer;
  int counter;
} Tesei_t;

typedef struct {
  int rows;
  int cols;
  Room_t** labirint;
  Krot_t krot;
  int count_room;
} Labirint_t;

typedef enum {
  START,
  CAVE,
  LABA,
  PARSE_LABA,
  GENERATE_LABA,
  AI,
  LINE,
  RANDOM_ROOM,
  EXIT,
  EXIT_CAVE,
} StateMachine;

#endif

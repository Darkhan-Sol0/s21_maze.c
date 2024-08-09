#include "s21_maze.h"

void create_matrix(cave_t *cave) {
  cave->matrix = (int **)malloc(cave->rows * sizeof(int *));
  for (int i = 0; i < cave->rows; i++)
    cave->matrix[i] = (int *)malloc(cave->cols * sizeof(int));
}

void clear_matrix(cave_t *cave) {
  for (int i = 0; i < cave->rows; i++) free(cave->matrix[i]);
  free(cave->matrix);
}

void fill_matrix(cave_t *cave) {
  for (int i = 0; i < cave->rows; i++)
    for (int j = 0; j < cave->cols; j++) cave->matrix[i][j] = 1;
}

void print_cave(cave_t cave) {
  for (int i = 0; i < cave.rows; i++) {
    int x = 0;
    for (int j = 0; j < cave.cols; j++) {
      if (cave.matrix[i][j] == 1) {
        mvaddch(i + 3, j + x + 3, ACS_CKBOARD | A_REVERSE);
        mvaddch(i + 3, j + x + 4, ACS_CKBOARD | A_REVERSE);
      } else {
        mvaddch(i + 3, j + x + 3, 'x');
        mvaddch(i + 3, j + x + 4, 'x');
      }
      x++;
    }
  }
}

void copy_cave(cave_t cave, cave_t *cpy_cave) {
  cpy_cave->rows = cave.rows;
  cpy_cave->cols = cave.cols;
  cpy_cave->b_limit = cave.b_limit;
  cpy_cave->d_limit = cave.d_limit;
  create_matrix(cpy_cave);
  for (int i = 0; i < cave.rows; i++)
    for (int j = 0; j < cave.cols; j++)
      cpy_cave->matrix[i][j] = cave.matrix[i][j];
}

int count_neighbour(cave_t cave, int a, int b) {
  int count = 0;
  int x = a + 1;
  int y = b + 1;
  for (int i = a - 1; i <= x; i++)
    for (int j = b - 1; j <= y; j++) {
      if (cave.matrix[i][j] != 0) count++;
    }
  return count;
}

void generate_cave(cave_t *cave) {
  int n = 0;
  cave_t temp_cave;
  copy_cave(*cave, &temp_cave);
  for (int i = 1; i < cave->rows - 1; i++)
    for (int j = 1; j < cave->cols - 1; j++) {
      n = count_neighbour(*cave, i, j);
      if (cave->matrix[i][j] == 1) {
        if (n - 1 < cave->d_limit) temp_cave.matrix[i][j] = 0;
      } else if (n > cave->b_limit)
        temp_cave.matrix[i][j] = 1;
    }
  copy_cave(temp_cave, cave);
  clear_matrix(&temp_cave);
}
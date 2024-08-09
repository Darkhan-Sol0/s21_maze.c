#include "s21_maze.h"

int file_parser(cave_t *cave) {
  int code = 0;
  FILE *fp;
  int buffer, rows, cols;
  fp = fopen("cave", "r+");
  if (fp == NULL) {
    mvprintw(0, cave->cols, "Cannot open file or read! Press any key to exit"); code = 1; getch();
  } else {
  fscanf(fp, "%d", &rows);
  fscanf(fp, "%d", &cols);
  cave->rows = rows + 2;
  cave->cols = cols + 2;
  create_matrix(cave);
  fill_matrix(cave);
  for (int i = 1; i < cave->rows - 1; i++)
    for (int j = 1; j < cave->cols - 1; j++) {
      fscanf(fp, "%d", &buffer);
      cave->matrix[i][j] = buffer;
    }
  fclose(fp);
  }
  return code;
}

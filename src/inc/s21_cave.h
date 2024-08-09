#ifndef S21_CAVE_H
#define S21_CAVE_H

#include "s21_maze.h"
#include "s21_objects.h"

void create_matrix(cave_t* cave);
void clear_matrix(cave_t* cave);
void fill_matrix(cave_t* cave);
void random_matrix(cave_t* cave);
void print_matrix(cave_t cave);

void print_cave(cave_t cave);
void copy_cave(cave_t cave, cave_t* copy_cave);
int file_parser(cave_t* cave);
void generate_cave(cave_t* cave);
int count_neighbour(cave_t cave, int i, int j);

#endif

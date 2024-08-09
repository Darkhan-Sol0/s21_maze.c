#ifndef S21_MAZE_H
#define S21_MAZE_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_cave.h"
#include "s21_objects.h"

//-------Labirint--------
void create_Labirint(Labirint_t* laba, int rows, int cols);
void free_Labirint(Labirint_t* laba);
void zero_Labirint(Labirint_t* laba);
//-------Generator-------
void generate_Labirint(Labirint_t* laba);
int check_map(Labirint_t* laba);
void spawn_on_room(Labirint_t* laba);
//-------Movement--------
int check_visits(Labirint_t* laba);
void change_visits(Labirint_t* laba);
void move_krot(Labirint_t* laba);
void move_left_krot(Labirint_t* laba);
void move_right_krot(Labirint_t* laba);
void move_up_krot(Labirint_t* laba);
void move_down_krot(Labirint_t* laba);
void rand_move_krot(Labirint_t* laba);
Check_neighbor_t check_neighbor(Labirint_t* laba);
void start_spawn(Labirint_t* laba);

//-----print------
void print_labirint(Labirint_t* laba);

int parse_Labirint(Labirint_t* laba, char* path);
void export_labirint(Labirint_t* laba);

//------Tesei-------
void tesei_adventure(Labirint_t* laba, Tesei_t* tesei, int count);
void init_room_map(Labirint_t* laba, Tesei_t* tesei, int count);
void init_way_map(Tesei_t* tesei);
void init_random_room(Labirint_t* laba, Tesei_t* tesei);
void free_tesei(Tesei_t* tesei);
void free_ways(Tesei_t* tesei);
void spawn_tesei(Tesei_t* tesei);
void move_tesei(Tesei_t* tesei);
void move_up_tesei(Tesei_t* tesei);
void move_down_tesei(Tesei_t* tesei);
void move_right_tesei(Tesei_t* tesei);
void move_left_tesei(Tesei_t* tesei);
Check_ways_t check_ways(Tesei_t* tesei);
void change_visits_tesei(Tesei_t* tesei);
void print_tesei(Tesei_t* tesei, int line);
void set_deadlock(Tesei_t* tesei);
void refresh_map(Tesei_t* tesei);
int check_finish(Tesei_t* tesei);
void get_room(Tesei_t* tesei, int start_room, int exit_room);
void set_finish_way(Tesei_t* tesei);
void add_way_map(Tesei_t* tesei);
Room_pos_t room_pos(Tesei_t* tesei, int number);
void export_tesei(Tesei_t* tesei);

int have_in_way(Tesei_t* tesei, int number);

void lane_adventure(Labirint_t* laba, Tesei_t* tesei);

Check_ways_t check_line_ways(Tesei_t* tesei, int y, int x);

void state_machine();

#endif

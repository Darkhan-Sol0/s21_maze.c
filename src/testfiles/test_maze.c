#include "test_main.h"

START_TEST(test_cave) {
  cave_t cave;
  file_parser(&cave);
  cave.b_limit = 1;
  generate_cave(&cave);
  print_cave(cave);
}
END_TEST

START_TEST(test_generate_maze) {
  Labirint_t laba;
  Tesei_t tesei;
  create_Labirint(&laba, 20, 20);
  zero_Labirint(&laba);
  generate_Labirint(&laba);
  export_labirint(&laba);
  init_random_room(&laba, &tesei);
  tesei_adventure(&laba, &tesei, 100);
  free_Labirint(&laba);
  free_tesei(&tesei);
}
END_TEST

START_TEST(test_parce_maze) {
  Labirint_t laba;
  Tesei_t tesei;
  parse_Labirint(&laba, "20.maze");
  get_room(&tesei, 5, 50);
  lane_adventure(&laba, &tesei);
  free_Labirint(&laba);
  free_tesei(&tesei);
}
END_TEST

START_TEST(test_parce_broke_maze) {
  Labirint_t laba;
  halfdelay(1);
  create_Labirint(&laba, 10, 10);
  zero_Labirint(&laba);
  parse_Labirint(&laba, "jhadgs");
  free_Labirint(&laba);
  halfdelay(0);
}
END_TEST

Suite *test_maze(void) {
  Suite *s = suite_create("s21_maze");
  TCase *tc = tcase_create("maze_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_cave);
  tcase_add_test(tc, test_generate_maze);
  tcase_add_test(tc, test_parce_maze);
  tcase_add_test(tc, test_parce_broke_maze);
  // tcase_add_test(tc, tetris_6);
  // tcase_add_test(tc, tetris_7);
  // tcase_add_test(tc, tetris_8);
  // tcase_add_test(tc, tetris_9);
  // tcase_add_test(tc, tetris_10);
  // tcase_add_test(tc, tetris_11);
  return s;
}

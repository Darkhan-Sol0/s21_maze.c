#include "test_main.h"

int main(void) {
  int failed = 0;
  Suite *maze_test[] = {test_maze(), NULL};

  for (int i = 0; maze_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(maze_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);
  return failed;
}

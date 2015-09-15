/*
**
*/
#include <pebble.h>
#include "common.h"

/*
** Forward Declarations
*/

    static void init(void);
    static void deinit(void);
    int main(void);

/*
** OWN storage
*/

    Window *root = 0;

static void init(void) {

    root = window_create();
    window_stack_push(root, true);

    game_start();

} /* init */

static void deinit(void) {

    window_stack_pop_all(true);
    window_destroy(root);
} /* deinit */

int main(void) {

  init();
  app_event_loop();
  deinit();
} /* main */

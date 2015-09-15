#include <pebble.h>
#include "common.h"
#define TEAM_A 0
#define TEAM_B 1
#define TEAM_MAX 2

typedef struct _game {
    char *name;
    int stop_clock;
    int pmax;
    int period[];
} GAME;

/*
** Forward declarations
*/

    void game_start(void);
    void game_adjust_score(int team, int adjustment);
    static void game_load(Window *window);
    static void game_appear(Window *window);
    static void game_unload(Window *window);
    static void game_disappear(Window *window);

/*
** OWN storage
*/

//    static int period = 0;
    static Window *root = 0;
    static TextLayer *name[TEAM_MAX], *score[TEAM_MAX];

void game_start(void) {

    // create a context here containing pointers to team and code
    // as in "sporting code", as well as the window, etc.

    root = window_create();
    window_set_window_handlers(root, (WindowHandlers) {
                                .load = game_load,
                                .appear = game_appear,
                                .disappear = game_disappear,
                                .unload = game_unload
                              });
    window_stack_push(root, true);
} /* game_start */


void game_adjust_score(int team,
                       int adjustment) {

    // adjust textlayer

} /* game_adjust_score */

static void game_load(Window *window) {

    name[TEAM_A] = text_layer_create(GRect(5, 10, 120                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               , 20));
    text_layer_set_text_alignment(name[TEAM_A], GTextAlignmentCenter);
    text_layer_set_overflow_mode(name[TEAM_A],
                                      GTextOverflowModeTrailingEllipsis);
    text_layer_set_text(name[TEAM_A], "Swan Comets");
    layer_add_child(window_get_root_layer(window),
                    text_layer_get_layer(name[TEAM_A]));

    // setup the team names

    // setup scoreboxes at 00

    // setup 'vs'

    scorebar_init(window);
} /* game_load */

static void game_appear(Window *window) {
    // if stop_clock
        // restart the clock...
} /* game_appear */

static void game_unload(Window *window) {
    scorebar_deinit();

    // tidy up?
} /* game_unload */

static void game_disappear(Window *window) {
    // if stop_clock
        // pause_timer
} /* game_disappear */

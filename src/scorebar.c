// This should be attached to the game Window.
// game will need a couple routines that can be called to
// adjust the score, say:
//
//    game_adjust_score(int team, int adjustment);
//
// This routine will handle updating the text boxes, what the adjustment
// really means...in AFL 1-click = point, 2-click = goal
//                in Basketball 1-click = 1 point, etc.
//
// The game module should hold all the real details, including what the
// adjustment really means.  scorebar just handles gathering the details.
#include <pebble.h>
#include "common.h"
#define CLICK_TIMEOUT 0
#define MIN_CLICKS 1
#define MAX_CLICKS 3

/*
** Forward declarations
*/

    void scorebar_init(Window *parent);
    void scorebar_deinit(void);
    static void click_handler(ClickRecognizerRef recognizer, void *context);
    static void set_scorebar_plus(void);
    static void set_scorebar_minus(void);
    static void click_config_provider(void *context);

/*
** OWN storage
*/

    static ActionBarLayer *scorebar = 0;
    static int score[2];
    static int multiplier;
    static GBitmap *elipsis, *plus = 0, *minus = 0;

void scorebar_init(Window *parent) {

    if (scorebar != 0) return;

    score[0] = score[1] = 0;
    multiplier = 1;

    elipsis = gbitmap_create_with_resource(RESOURCE_ID_ELIPSIS);
    minus = gbitmap_create_with_resource(RESOURCE_ID_MINUS);
    plus = gbitmap_create_with_resource(RESOURCE_ID_PLUS);

    scorebar = action_bar_layer_create();

    action_bar_layer_set_click_config_provider(scorebar,
                                               click_config_provider);

    set_scorebar_plus();
    action_bar_layer_set_icon_animated(scorebar, BUTTON_ID_SELECT,
                                       elipsis, true);

    action_bar_layer_add_to_window(scorebar, parent);
} /* scorebar_init */

void scorebar_deinit(void) {

    if (scorebar == 0) return;

    action_bar_layer_remove_from_window(scorebar);
    action_bar_layer_destroy(scorebar);

    gbitmap_destroy(elipsis);
    gbitmap_destroy(minus);
    gbitmap_destroy(plus);

    scorebar = 0;
} /* scorebar_deinit */

static void click_handler(ClickRecognizerRef recognizer,
                          void *context) {
    ButtonId id;
    uint8_t count;

    id = click_recognizer_get_button_id(recognizer);
    count = click_number_of_clicks_counted(recognizer);

    switch (id) {
    case BUTTON_ID_SELECT:
        switch (count) {
        case 1:
            if (multiplier < 0) {
                set_scorebar_plus();
            } else {
                set_scorebar_minus();
            }
            multiplier *= -1;
            break;
        }
        break;

    default:
        switch (id) {
            case BUTTON_ID_UP:
            score[0] += (count * multiplier);
            break;

        case BUTTON_ID_DOWN:
            score[1] += (count * multiplier);
            break;

        default:
            break;
        }

        if (multiplier < 0) {
            set_scorebar_plus();
        }
        break;
    }
} /* click_handler */

static void set_scorebar_minus(void) {
    action_bar_layer_set_background_color(scorebar, GColorRed);
    action_bar_layer_set_icon_animated(scorebar, BUTTON_ID_UP, minus, true);
    action_bar_layer_set_icon_animated(scorebar, BUTTON_ID_DOWN, minus, true);
} /* set_scorebar_minus */

static void set_scorebar_plus(void) {
    action_bar_layer_set_background_color(scorebar, GColorGreen);
    action_bar_layer_set_icon_animated(scorebar, BUTTON_ID_UP, plus, true);
    action_bar_layer_set_icon_animated(scorebar, BUTTON_ID_DOWN, plus, true);
} /* set_scorebar_plus */

static void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, click_handler);
    window_multi_click_subscribe(BUTTON_ID_UP, MIN_CLICKS-1, MAX_CLICKS,
                                 CLICK_TIMEOUT, true, click_handler);

    window_single_click_subscribe(BUTTON_ID_SELECT, click_handler);
    window_multi_click_subscribe(BUTTON_ID_SELECT, MIN_CLICKS-1, MAX_CLICKS,
                                 CLICK_TIMEOUT, true, click_handler);

    window_single_click_subscribe(BUTTON_ID_DOWN, click_handler);
    window_multi_click_subscribe(BUTTON_ID_DOWN, MIN_CLICKS-1, MAX_CLICKS,
                                 CLICK_TIMEOUT, true, click_handler);
} /* click_config_provider */


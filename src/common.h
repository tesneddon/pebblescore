#ifndef common_h__
#define common_h__
#include <pebble.h>

#define TEAM_A 0
#define TEAM_B 1

/*
** game.c
*/

    void game_start(void);
    void game_adjust_score(int team, int adjustment);

/*
** scorebar.c
*/

    void scorebar_init(Window *parent);
    void scorebar_deinit(void);

#endif /* common_h__ */


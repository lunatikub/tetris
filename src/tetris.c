#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tetris.h"
#include "tetris_ai.h"
#include "tetris_wall.h"
#include "tetris_x.h"

static inline item_t tetris_item_rand(void)
{
    static item_t last_item = INIT_ITEM;
    item_t item = rand() % _Z + 1;

    while (item == last_item) {
        item = rand() % _Z + 1;
    }
    last_item = item;

    return item;
}

static inline void tetris_item_fill(item_t *item)
{
    uint8_t i = 0;

    for (i = 0; i < _ITEM; ++i) {
        item[i] = tetris_item_rand();
    }
}

static inline item_t tetris_item_next(item_t *item)
{
    uint8_t i = 0;
    item_t curr = item[0];

    for (i = 0; i < _ITEM - 1; ++i) {
        item[i] = item[i + 1];
    }
    item[i] = tetris_item_rand();

    return curr;
}

static inline int tetris_init(tetris_t *t)
{
    memset(t, 0, sizeof(tetris_t));

    srand(time(NULL));

    if (_X_ && tetris_x_init()) {
        return -1;
    }

    return 0;
}

static inline int tetris_clean(tetris_t *t)
{
    (void)t;

    if (_X_ && tetris_x_clean()) {
        return -1;
    }

    return 0;
}

int main(void)
{
    tetris_t t;

    item_t items[_ITEM] = { INIT_ITEM };
    item_t curr_item = INIT_ITEM;

    if (tetris_init(&t)) {
        return -1;
    }

    move_t mv = {
        .x = -1,
        .r = -1,
        .hold = 0,
    };

    tetris_item_fill(items);

    for (;;) {
        curr_item  = tetris_item_next(items);

        if (_X_) {
            tetris_x_main_dump(&t, curr_item, items);
        }

        if (tetris_ai(&t, curr_item, items, &mv)) {
            break; /* Game Over */
        }

        if (_X_ == 0 && (t.nr_items % 100 == 0)) {
            printf("%10u\r", t.nr_completed);
        }

        tetris_wall_update(&t);
    }

    if (_X_) {
        getchar();
    }

    if (tetris_clean(&t)) {
        return 1;
    }

    if (_X_ == 0) {
        printf("\n%u\n", t.nr_completed);
    }

    return 0;
}

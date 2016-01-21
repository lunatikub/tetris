#ifndef TETRIS_ABSTRACTION_H_
# define TETRIS_ABSTRACTION_H_

#include "tetris_emulation.h"
#include "tetris_x.h"

static inline int tetris_abstraction_init(void)
{
#ifdef EMULATION
    return tetris_emul_init();
#else
    return tetris_x_init();
#endif
}

static inline int tetris_abstraction_clean(void)
{
#ifdef EMULATION
    return tetris_emul_clean();
#else
    return tetris_x_clean();
#endif
}

static inline item_t tetris_abstraction_next_item_get(void)
{
#ifdef EMULATION
    return tetris_emul_next_item_get();
#else
    return tetris_x_next_item_get();
#endif
}

static inline void tetris_abstraction_dump(tetris_t *t,
                                           item_t    item,
                                           uint32_t  score)

{
#ifdef EMULATION
    return tetris_emul_dump(t, item, score);
#else
    (void)t;
    (void)item;
    (void)score;
#endif
}

#endif /* !TETRIS_ABSTRACTION_H_ */

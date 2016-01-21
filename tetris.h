#ifndef TETRIS_H_
# define TETRIS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define _W (10)
#define _H (20)

#define _GET(map,x,y) (map[((y) * _W) + (x)])

#define _SET(t,x,y,I)                                                   \
    ({                                                                  \
        if ((t)->map[((y) * _W) + (x)] != 0) {                          \
            fprintf(stderr, " override %s %u", __FUNCTION__, __LINE__); \
            fprintf(stderr, " x: %u y: %u ", x, y);                     \
            fprintf(stderr, " last: %u ", (t)->map[((y) * _W) + (x)]);  \
            getchar();                                                  \
            abort();                                                    \
        }                                                               \
        ((t)->map[((y) * _W) + (x)] = I);                               \
        ((t)->n[y]++);                                                  \
    })

#define _RESET(map,x,y) (map[((y) * _W) + (x)] = 0)

typedef struct {
    uint8_t  map[_W * _H];
    uint8_t  h[_W];
    uint8_t  hole[_W];
    uint8_t  n[_H];
    uint32_t nr;
} tetris_t;

#define TETRIS_ERR(msg)                                         \
    ({                                                          \
        fprintf(stderr, "Error:    %s\n", msg);                 \
        fprintf(stderr, "Line:     %u\n", __LINE__);            \
        fprintf(stderr, "Function: %s\n", __FUNCTION__);        \
        fprintf(stderr, "File:     %s\n", __FILE__);            \
        exit(1);                                                \
    })

#endif /* !TETRIS_H_ */

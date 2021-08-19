#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "kuf.h"

void gens(void)
{
    printf("random quad: %x\n", kuf_gen_quad());
    printf("random tile: %x\n", kuf_gen_tile());
    printf("random pair: %x\n", kuf_gen_pair());
}

void print_tile(uint8_t tile)
{
    printf("%s", tile ? "#" : " ");
}

void print_quad(uint8_t quad)
{
    printf("+--+\n");
    printf("|");
    print_tile(quad & 1);
    print_tile((quad & 2) >> 1);
    printf("|\n|");
    print_tile((quad & 4) >> 2);
    print_tile((quad & 8) >> 3);
    printf("|\n");
    printf("+--+\n");
}

void print_side(uint16_t side)
{
    print_tile(side & 1);
    print_tile(side & 2);
}

void print_square(uint16_t square)
{
    printf("+----+\n");
    printf("|");
    print_side(kuf_quad_side_get(square & 0xf, KUF_NORTH));
    print_side(kuf_quad_side_get((square >> 4) & 0xf, KUF_NORTH));
    printf("|\n");

    printf("|");
    print_side(kuf_quad_side_get(square & 0xf, KUF_SOUTH));
    print_side(kuf_quad_side_get((square >> 4) & 0xf, KUF_SOUTH));
    printf("|\n");

    printf("|");
    print_side(kuf_quad_side_get((square >> 8) & 0xf, KUF_NORTH));
    print_side(kuf_quad_side_get((square >> 12) & 0xf, KUF_NORTH));
    printf("|\n");

    printf("|");
    print_side(kuf_quad_side_get((square >> 8) & 0xf, KUF_SOUTH));
    print_side(kuf_quad_side_get((square >> 12) & 0xf, KUF_SOUTH));
    printf("|\n");

    printf("+----+\n");
}

void setting_stuff(void)
{
    printf("setting stuff\n");

    print_quad(kuf_quad_side_set(0, KUF_NORTH, 3));
    print_quad(kuf_quad_side_set(0, KUF_SOUTH, 3));
    print_quad(kuf_quad_side_set(0, KUF_EAST, 3));
    print_quad(kuf_quad_side_set(0, KUF_WEST, 3));
}

void getting_stuff(void)
{
    printf("getting stuff\n");
    print_quad(kuf_quad_side_get(9, KUF_NORTH));
    print_quad(kuf_quad_side_get(9, KUF_SOUTH));
    print_quad(kuf_quad_side_get(0xf, KUF_EAST));
    print_quad(kuf_quad_side_get(5, KUF_WEST));
}

void quad_getters(void)
{
    uint16_t s;

    s = 0xf | 0xd << 4 | 6 << 8 | 7 << 12;
    printf("quad getters\n");
    print_square(s);

    printf("Quads A,B,C,D:\n");

    print_quad(kuf_square_quad_get(s, KUF_QUAD_A));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_B));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_C));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_D));

    printf("Quads AB,CD,AC,BD:\n");

    print_quad(kuf_square_quad_get(s, KUF_QUAD_AB));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_CD));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_AC));
    print_quad(kuf_square_quad_get(s, KUF_QUAD_BD));

    printf("Quad ABCD:\n");
    print_quad(kuf_square_quad_get(s, KUF_QUAD_ABCD));
}

void quad_setters(void)
{
    printf("quad setters\n");
    printf("Quads A,B,C,D:\n");
    print_square(kuf_square_quad_set(0, KUF_QUAD_A, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_B, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_C, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_D, 0xf));

    printf("Quads AB,CD,AC,BD:\n");
    print_square(kuf_square_quad_set(0, KUF_QUAD_AB, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_CD, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_AC, 0xf));
    print_square(kuf_square_quad_set(0, KUF_QUAD_BD, 0xf));

    printf("Quad ABCD:\n");
    print_square(kuf_square_quad_set(0, KUF_QUAD_ABCD, 0xf));
}

void gen_squares(void)
{
    printf("gen square\n");
    kuf_print_square(kuf_gen_square());
    kuf_print_square(kuf_gen_square());
    kuf_print_square(kuf_gen_square());
    kuf_print_square(kuf_gen_square());
}

void gen_blocks(void)
{
    uint16_t w, x, y, z;
    printf("gen block\n");
    w = x = y = z = 0;
    kuf_gen_block(&w, &x, &y, &z);
    kuf_print_block(w, x, y, z);
    kuf_write_block_pbm("test.pbm", w, x, y, z);
}

void gen_patterns(void)
{
    uint16_t w, x, y, z;
    uint16_t sqr[24];
    int width;
    int i;

    width = 6;

    for (i = 0; i < 24; i++) sqr[i] = 0;

    printf("gen patterns\n");

    w = x = y = z = 0;
    w = KUF_HLINE_0;
    x = KUF_HLINE_1;
    y = KUF_HLINE_2;
    z = KUF_HLINE_3;
    kuf_set_block(width, sqr, 0, 0, w, x, y, z);
    kuf_print_block(w, x, y, z);
    w = x = y = z = 0;
    w = KUF_VLINE_0;
    x = KUF_VLINE_1;
    y = KUF_VLINE_2;
    z = KUF_VLINE_3;
    kuf_set_block(width, sqr, 2, 0, w, x, y, z);
    kuf_print_block(w, x, y, z);
    w = x = y = z = 0;
    w = KUF_HLINE_HALF_WEST_0 | KUF_HLINE_HALF_EAST_1;
    x = KUF_HLINE_HALF_EAST_0 | KUF_HLINE_HALF_WEST_1;
    y = KUF_HLINE_HALF_WEST_2 | KUF_HLINE_HALF_EAST_3;
    z = KUF_HLINE_HALF_EAST_2 | KUF_HLINE_HALF_WEST_3;
    kuf_set_block(width, sqr, 4, 0, w, x, y, z);
    kuf_print_block(w, x, y, z);
    w = x = y = z = 0;
    w = KUF_VLINE_HALF_NORTH_0 | KUF_VLINE_HALF_SOUTH_1;
    x = KUF_VLINE_HALF_SOUTH_0 | KUF_VLINE_HALF_NORTH_1;
    y = KUF_VLINE_HALF_NORTH_2 | KUF_VLINE_HALF_SOUTH_3;
    z = KUF_VLINE_HALF_SOUTH_2 | KUF_VLINE_HALF_NORTH_3;
    kuf_set_block(width, sqr, 0, 2, w, x, y, z);
    kuf_print_block(w, x, y, z);
    w = x = y = z = 0;
    w = KUF_HPARALLEL_0;
    x = KUF_HPARALLEL_1;
    y = KUF_VPARALLEL_0;
    z = KUF_VPARALLEL_1;
    kuf_set_block(width, sqr, 2, 2, w, x, y, z);
    kuf_print_block(w, x, y, z);
    w = x = y = z = 0;
    w = KUF_CORNER_NORTHWEST;
    x = KUF_CORNER_NORTHEAST;
    y = KUF_CORNER_SOUTHWEST;
    z = KUF_CORNER_SOUTHEAST;
    kuf_set_block(width, sqr, 4, 2, w, x, y, z);
    kuf_print_block(w, x, y, z);

    /* kuf_set_block(width, sqr, 0, 0, w, x, y, z); */
    /* kuf_set_block(width, sqr, 2, 0, w, x, y, z); */
    /* kuf_set_block(width, sqr, 4, 0, w, x, y, z); */

    kuf_write_pbm("pat.pbm", 6, 4, sqr);
}

void gen_correct(void)
{
    uint16_t sqr[36];
    uint16_t w, x, y, z;
    int i;
    int width, height;
    width = 6;
    height = 6;

    for (i = 0; i < 36; i++) sqr[i] = 0;


    w = x = y = z = 0;

    w = x = y = z = KUF_HPARALLEL_0;
    for (i = 0; i < 3; i++) {
        kuf_set_block(width, sqr, i*2, 0, w, x, y, z);
    }


    w = x = y = z = KUF_HPARALLEL_0 | KUF_VPARALLEL_0;

    kuf_print_square(w | KUF_HLINE_3);

    kuf_print_square(kuf_correct_square(w | KUF_HLINE_3));

    kuf_set_block(width, sqr, 0, 0, w, x, y, z);
    kuf_set_block(width, sqr, 4, 0, w, x, y, z);

    w = x = y = z = KUF_HPARALLEL_1;
    for (i = 0; i < 3; i++) {
        kuf_set_block(width, sqr, i*2, 4, w, x, y, z);
    }
    w = x = y = z = KUF_HPARALLEL_1 | KUF_VPARALLEL_0;
    kuf_set_block(width, sqr, 0, 4, w, x, y, z);
    kuf_set_block(width, sqr, 4, 4, w, x, y, z);

    w = x = y = z = KUF_VPARALLEL_0;
    kuf_set_block(width, sqr, 0, 2, w, x, y, z);
    kuf_set_block(width, sqr, 4, 2, w, x, y, z);

    w = x = y = z = 0x6666;
    kuf_set_block(width, sqr, 2, 2, w, x, y, z);

    kuf_correct(width, height, sqr, NULL);

    kuf_write_pbm("correct.pbm", width, height, sqr);
}

void gen_correct2(void)
{
    uint16_t sqr[36];
    uint16_t w, x, y, z;
    int i;
    int width, height;
    width = 6;
    height = 6;

    for (i = 0; i < 36; i++) sqr[i] = 0;


    w = x = y = z = 0;

    for (i = 0; i < 3; i++) {
        kuf_set_block(width, sqr, i*2, 0, w, x, y, z);
    }

    kuf_gen_block(&w, &x, &y, &z);
    kuf_set_block(width, sqr, 0, 0, w, x, y, z);

    kuf_gen_block(&w, &x, &y, &z);
    kuf_set_block(width, sqr, 4, 0, w, x, y, z);

    kuf_gen_block(&w, &x, &y, &z);
    kuf_set_block(width, sqr, 0, 4, w, x, y, z);

    kuf_gen_block(&w, &x, &y, &z);
    kuf_set_block(width, sqr, 4, 4, w, x, y, z);

    w = x = y = z = 0x6635;
    kuf_set_block(width, sqr, 2, 2, w, x, y, z);

    w = x = y = z = KUF_HPARALLEL_0;
    kuf_set_block(width, sqr, 0, 2, w, x, y, z);
    kuf_set_block(width, sqr, 2, 4, w, x, y, z);
    kuf_set_block(width, sqr, 2, 0, w, x, y, z);
    w = x = y = z = KUF_VPARALLEL_0;
    kuf_set_block(width, sqr, 4, 2, w, x, y, z);

    kuf_correct(width, height, sqr, NULL);

    printf("writing correct2.pbm\n");
    kuf_write_pbm("correct2.pbm", width, height, sqr);
}

void gen_bitmask(void)
{
    uint16_t sqr[48];
    int i;
    int w, h;
    int pat[4];
    uint8_t bm[6];
    int x, y;

    w = 8;
    h = 6;

    pat[0] = KUF_HPARALLEL_0;
    pat[1] = KUF_VPARALLEL_0;
    pat[2] = KUF_HPARALLEL_1;
    pat[3] = KUF_HPARALLEL_0 | KUF_VPARALLEL_0;

    for (i = 0; i < 48; i++) {
        sqr[i] = 0;
    }

    for (i = 0; i < 6; i++) bm[i] = 0xff;

    for (i = 0; i < w; i++) {
        kuf_set_square(w, sqr, i, 0, pat[i % 4]);
        kuf_set_square(w, sqr, i, h - 1, pat[i % 4]);
    }

    for (i = 0; i < h; i++) {
        kuf_set_square(w, sqr, 0, i, pat[i % 4]);
        kuf_set_square(w, sqr, w - 1, i, pat[i % 4]);
        /* kuf_set_square(w, sqr, w - 1, i, 0xFFFF); */
    }

    /* kuf_set_square(w, sqr, 1, 1, KUF_CORNER_NORTHWEST); */
    /* kuf_set_square(w, sqr, w-2, 1, KUF_CORNER_NORTHEAST); */
    /* kuf_set_square(w, sqr, 1, h-2, KUF_CORNER_SOUTHWEST); */
    /* kuf_set_square(w, sqr, w-2, h-2, KUF_CORNER_SOUTHEAST); */

    for (y = 1; y < h - 1; y++) {
        for (x = 1; x < w - 1; x++) {
            kuf_bitmask_set(bm, w, x, y, 0);
        }
    }


    /* test out little pockets of correction */

    kuf_set_square(w, sqr, 3, 3, 0xFFFF);
    kuf_bitmask_set(bm, w, 3, 3, 1);

    kuf_set_square(w, sqr, 5, 2, 0xFFFF);
    kuf_bitmask_set(bm, w, 5, 2, 1);

    printf("correcting and writing bitmask\n");
    kuf_correct(w, h, sqr, bm);

    kuf_write_pbm("bitmask.pbm", w, h, sqr);
}

/* try generating a big one ! */

void boxit(uint16_t *sqr, int w, int h, int off)
{
    int i;
    int startx, starty;
    int endx, endy;

    startx = off;
    endx = w - off - 1;

    starty = off;
    endy = h - off - 1;

    kuf_set_square(w, sqr, startx, starty, KUF_CORNER_NORTHWEST);
    kuf_set_square(w, sqr, endx, starty, KUF_CORNER_NORTHEAST);
    kuf_set_square(w, sqr, startx, endy, KUF_CORNER_SOUTHWEST);
    kuf_set_square(w, sqr, endx, endy, KUF_CORNER_SOUTHEAST);

    for (i = startx + 1; i < endx; i++) {
        kuf_set_square(w, sqr, i, starty, KUF_HPARALLEL_0);
        kuf_set_square(w, sqr, i, endy, KUF_HPARALLEL_1);
    }

    for (i = starty + 1; i < endy; i++) {
        kuf_set_square(w, sqr, startx, i, KUF_VPARALLEL_0);
        kuf_set_square(w, sqr, endx, i, KUF_VPARALLEL_1);
    }
}

void gen_big(void)
{
    uint16_t sqr[1024];
    int i;
    int w, h;
    int xp, yp;
    int pos;

    w = 32;
    h = 32;

    for (i = 0; i < 1024; i++) {
        if (i < 512) {
            if (i % 2) sqr[i] = KUF_HPARALLEL_0;
            else sqr[i] = KUF_CROSSHATCH_0;
        } else sqr[i] = KUF_DIAGONAL_0;
    }


    for (yp = h/2; yp < h; yp++) {
        for (xp = w/2; xp < w; xp++) {
            kuf_set_square(w, sqr, xp, yp, KUF_VPARALLEL_1);
        }
    }

    for (yp = 0; yp < (h/4); yp++) {
        for (xp = 0; xp < (w/4); xp++) {
            int run;

            if ((yp % 2) == 0) {
                run = (xp % 2) == 0;
            } else {
            }


            if (run) {
                uint16_t a, b, c, d;
                int k;

                for (k = 0; k < 3; k++) {
                    kuf_gen_block(&a, &b, &c, &d);
                    kuf_set_block(w, sqr, xp*4, yp*4 + 2*k, a, b, c, d);

                    kuf_gen_block(&a, &b, &c, &d);
                    kuf_set_block(w, sqr, xp*4 + 2, yp*4 + 2*k, a, b, c, d);

                    kuf_gen_block(&a, &b, &c, &d);
                    kuf_set_block(w, sqr, xp*4 + 4, yp*4 + 2*k, a, b, c, d);
                }
            }
        }
    }

    boxit(sqr, w, h, 1);
    boxit(sqr, w, h, 3);
    boxit(sqr, w, h, 5);

    printf("correcting and writing big\n");
    kuf_correct(w, h, sqr, NULL);

    kuf_write_pbm("big.pbm", w, h, sqr);
}

int main(int argc, char *argv[])
{
    size_t seed;

    /* seed = time(NULL); */
    /* seed = 1609883522; */
    /* seed = 1609884516; */
    /* seed = 1610033651; */
    seed = 1629077282;
    srand(seed);
    gens();

    printf("printing some stuff\n");
    print_tile(1);
    print_tile(0);
    printf("\n");
    print_tile(0);
    print_tile(1);
    printf("\n\n");

    print_quad(1);
    print_quad(2);
    print_quad(4);
    print_quad(8);

    setting_stuff();
    getting_stuff();

    quad_getters();
    quad_setters();

    gen_squares();

    gen_blocks();

    gen_patterns();

    gen_correct();
    gen_correct2();

    gen_bitmask();

    gen_big();

    printf("seed: %ld\n", seed);
    return 0;
}

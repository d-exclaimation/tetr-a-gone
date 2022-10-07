//
//  test.c
//  
//  Unit test program
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#include "unittest.h"
#include "vector2.h"

static Testcode_t vector2_eq_test(void)
{
    if (!vec2_eq(VEC2_EAST, VEC2_EAST))
        return FATAL;

    if (!vec2_eq(VEC2_ZERO, VEC2_ZERO))
        return FATAL;

    if (vec2_eq(VEC2_EAST, VEC2_WEST))
        return FATAL;

    if (vec2_eq(VEC2_NORTH, VEC2_SOUTH))
        return FATAL;

    if (vec2_eq(vec2(4, 7), vec2(7, 4)))
        return FATAL;

    return OK;
}

static Testcode_t vector2_add_test(void)
{
    Vector2_t vec;

    vec = vec2_add(VEC2_ZERO, VEC2_ZERO);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_add(VEC2_ZERO, vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_ZERO, vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_EAST, VEC2_SOUTH);
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_WEST, VEC2_NORTH);
    if (!vec2_eq(vec, vec2(-1, -1)))
        return FAIL;

    return OK;
}

static Testcode_t vector2_inv_test(void)
{
    Vector2_t vec;

    vec = vec2_inv(VEC2_ZERO);
    if (!vec2_eq(vec, vec2(MAX_X, MAX_Y)))
        return FAIL;

    vec = vec2_inv(vec2(MAX_X, MAX_Y));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_inv(vec2(2, 2));
    if (!vec2_eq(vec, vec2(MAX_X - 2, MAX_Y - 2)))
        return FAIL;

    return OK;
}


static Testcode_t vector2_clamp_test(void)
{
    Vector2_t vec;

    vec = vec2_clamp(vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;
    
    vec = vec2_clamp(vec2(-1, -1));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_clamp_in(vec2(1, 1), 0, 0, 0, 0);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    return OK;
}

int main(void)
{
    Unit_t units[] = {
        unit("Vector 2 Equal test", &vector2_eq_test),
        unit("Vector 2 Add test", &vector2_add_test),
        unit("Vector 2 Invert test", &vector2_inv_test),
        unit("Vector 2 Clamp test", &vector2_clamp_test)
    };
    test_all(units, sizeof(units) / sizeof(Unit_t));
    return 0;
}


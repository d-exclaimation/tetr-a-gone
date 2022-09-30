//
//  vector2.c
//  
//  Module for anything related to a point in a 2D plane / 2D vector
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "vector2.h"

Vector2_t vec2(const int8_t x, const int8_t y)
{
    return (Vector2_t) {
        .x = x,
        .y = y
    };
}

bool vec2_eq(const Vector2_t lhs, const Vector2_t rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

Vector2_t vec2_add(const Vector2_t lhs, const Vector2_t rhs)
{
    return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2_t vec2_inv(const Vector2_t vec)
{
    return vec2(MAX_X - vec.x, MAX_Y - vec.y);
}

Vector2_t vec2_clamp(const Vector2_t vec)
{
    return vec2_clamp_in(vec, MIN_X, MAX_X, MIN_Y, MAX_Y);
}

Vector2_t vec2_clamp_in(const Vector2_t vec, const int8_t min_x, const int8_t max_x, const int8_t min_y, const int8_t max_y)
{
    int8_t new_x = vec.x;
    int8_t new_y = vec.y;

    // Adjust x within boundaries   
    new_x = (new_x < min_x) ? min_x : new_x;
    new_x = (new_x > max_x) ? max_x : new_x;

    // Adjust y within boundaries
    new_y = (new_y < min_y) ? min_y : new_y;
    new_y = (new_y > max_y) ? max_y : new_y;

    return vec2(new_x, new_y);
}
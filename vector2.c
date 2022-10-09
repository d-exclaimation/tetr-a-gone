//
//  vector2.c
//  
//  Module for anything related to a point in a 2D plane / 2D vector
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 30 Sep 2022
//

#include "vector2.h"

/**
 * @brief Create a new Vector2_t
 * 
 * @param x The x-axis position
 * @param y The y-axis position
 */
Vector2_t vec2(const int8_t x, const int8_t y)
{
    return (Vector2_t) {
        .x = x,
        .y = y
    };
}

/**
 * @brief Check if the left hand side vector is exactly equal to the right hand side
 * 
 * @param lhs Left hand side vector
 * @param rhs Right hand side vector
 *  
 * @returns True if both are equal
 */
bool vec2_eq(const Vector2_t lhs, const Vector2_t rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

/**
 * @brief Add the left hand side and the right hand side vectors
 * 
 * @param lhs Left hand side vector
 * @param rhs Right hand side vector
 *  
 * @returns A resulting vector
 */
Vector2_t vec2_add(const Vector2_t lhs, const Vector2_t rhs)
{
    return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

/**
 * @brief Invert the vector by the (y = 1 - x) line
 * 
 * @param vec The vector to be inverted
 *  
 * @returns A resulting (inverted) vector
 */
Vector2_t vec2_inv(const Vector2_t vec)
{
    return vec2(MAX_X - vec.x, MAX_Y - vec.y);
}

/**
 * @brief Clamp the vector be have x within 0 to MAX_X an y within 0 to MAX_Y
 * 
 * @param vec The vector to be clamped
 *  
 * @returns A resulting vector
 */
Vector2_t vec2_clamp(const Vector2_t vec)
{
    return vec2_clamp_in(vec, MIN_X, MAX_X, MIN_Y, MAX_Y);
}

/**
 * @brief Clamp the vector within the given range
 * 
 * @param vec The vector to be clamped
 * @param min_x The minimum x
 * @param max_x The maximum x
 * @param min_y The minimum y
 * @param max_y The maximum y
 *  
 * @returns A resulting vector
 */
Vector2_t vec2_clamp_in(const Vector2_t vec, const int8_t min_x, const int8_t max_x, const int8_t min_y, const int8_t max_y)
{
    int8_t new_x = vec.x;
    int8_t new_y = vec.y;

    // I don't know where the min and max functions are :)

    // Adjust x within boundaries   
    new_x = (new_x < min_x) ? min_x : new_x;
    new_x = (new_x > max_x) ? max_x : new_x;

    // Adjust y within boundaries
    new_y = (new_y < min_y) ? min_y : new_y;
    new_y = (new_y > max_y) ? max_y : new_y;

    return vec2(new_x, new_y);
}
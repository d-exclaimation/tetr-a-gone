//
//  vector2.h
//  
//  Module for anything related to a point in a 2D plane / 2D vector
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Minimum x position
 */
#define MIN_X 0

/**
 * @brief Minimum y position
 */
#define MIN_Y 0

/**
 * @brief Maximum x position
 */
#define MAX_X 9

/**
 * @brief Maximum y position
 */
#define MAX_Y 6

/**
 * @brief North direction vector
 */
#define VEC2_NORTH vec2(0, -1)

/**
 * @brief South direction vector
 */
#define VEC2_SOUTH vec2(0, 1)

/**
 * @brief West direction vector
 */
#define VEC2_WEST vec2(-1, 0)

/**
 * @brief East direction vector
 */
#define VEC2_EAST vec2(1, 0)

/**
 * @brief No direction
 */
#define VEC2_ZERO vec2(0, 0)

/**
 * @typedef Vector2_t
 * @brief A point in a 2D plane
 * 
 * @param y The row positioning (y-axis)
 * @param x The column positioning (x-axis)
 */
typedef struct {
    int8_t y;
    int8_t x;
} Vector2_t;

/**
 * @brief Create a new Vector2_t
 * 
 * @param x The x-axis position
 * @param y The y-axis position
 */
Vector2_t vec2(const int8_t x, const int8_t y);

/**
 * @brief Check if the left hand side vector is exactly equal to the right hand side
 * 
 * @param lhs Left hand side vector
 * @param rhs Right hand side vector
 *  
 * @returns True if both are equal
 */
bool vec2_eq(const Vector2_t lhs, const Vector2_t rhs);

/**
 * @brief Add the left hand side and the right hand side vectors
 * 
 * @param lhs Left hand side vector
 * @param rhs Right hand side vector
 *  
 * @returns A resulting vector
 */
Vector2_t vec2_add(const Vector2_t lhs, const Vector2_t rhs);

/**
 * @brief Invert the vector by the (y = 1 - x) line
 * 
 * @param vec The vector to be inverted
 *  
 * @returns A resulting (inverted) vector
 */
Vector2_t vec2_inv(const Vector2_t vec);

/**
 * @brief Clamp the vector be have x within 0 to MAX_X an y within 0 to MAX_Y
 * 
 * @param vec The vector to be clamped
 *  
 * @returns A resulting vector
 */
Vector2_t vec2_clamp(const Vector2_t vec);

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
Vector2_t vec2_clamp_in(const Vector2_t vec, const int8_t min_x, const int8_t max_x, const int8_t min_y, const int8_t max_y);

#endif
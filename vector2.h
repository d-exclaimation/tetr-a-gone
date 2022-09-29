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

#define MAX_X 4
#define MAX_Y 6

/**
 * \brief North direction vector
 */
#define VEC2_NORTH vec2(0, -1)

/**
 * \brief South direction vector
 */
#define VEC2_SOUTH vec2(0, 1)

/**
 * \brief West direction vector
 */
#define VEC2_WEST vec2(-1, 0)

/**
 * \brief East direction vector
 */
#define VEC2_EAST vec2(1, 0)

/**
 * \typedef
 * \brief A point in a 2D plane
 * 
 * \param y The row positioning (y-axis)
 * \param x The column positioning (x-axis)
 */
typedef struct {
    int8_t y;
    int8_t x;
} Vector2_t;

/**
 * \brief Create a new Vector2_t
 * 
 * \param x The x-axis position
 * \param y The y-axis position
 */
Vector2_t vec2(const int8_t x, const int8_t y);

#endif
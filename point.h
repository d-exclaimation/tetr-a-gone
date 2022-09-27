//
//  point.h
//  ence260
//
//  Created by vno16 on 23:16.
//

#ifndef POINT_H
#define POINT_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COL 4
#define MAX_ROW 6
#define UP (Point_t) {-1, 0}
#define DOWN (Point_t) {1, 0}
#define LEFT (Point_t) {0, -1}
#define RIGHT (Point_t) {0, 1}
#define STILL (Point_t) {0, 0}

/**
 * \typedef
 * \brief A point in a 2D dimension
 * 
 * \param row The row index of this poiny
 * \param col The column index of this poiny
 */
typedef struct {
    int8_t row;
    int8_t col;
} Point_t;

/**
 * \brief New point on the map (will be adjusted for the 14 x 5)
 * 
 * \param row The row location for the point (y, top-bottom)
 * \param col The column location for the point (x, left-right)
 * \return A new point given the row and col
 */
Point_t point(int8_t row, int8_t col);

/**
 * \brief Shift a point within the 7 x 5 grid
 * 
 * \param start The starting point
 * \param dir The direction where point should move to
 * 
 * \return A shifted / moved point within the 7 x 5 grid
 */
Point_t apply(const Point_t start, const Point_t dir);

/**
 * \brief Compare two points
 * 
 * \param lhs The left hand point
 * \param rhs The right hand point
 * 
 * \return True if points are equal
 */
bool equals(const Point_t lhs, const Point_t rhs);


/**
 * \brief Shrink the max column
 * 
 * \param target A point adjust 
 */
void shrink_column(Point_t* target);

/**
 * \brief The max column at the time
 * 
 * \return 0 - 4 (Indicate the last index of the column) 
 */
int8_t max_rows(void);

#endif
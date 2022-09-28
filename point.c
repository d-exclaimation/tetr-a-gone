//
//  point.h
//  ence260
//
//  Created by vno16 on 23:16.
//

#include "point.h"

static int8_t max_row = MAX_ROW;

Point_t point(int8_t row, int8_t col)
{
    return (Point_t) {
        row, col
    };
}

Point_t apply(const Point_t start, const Point_t dir)
{
    Point_t res = {start.row + dir.row, start.col + dir.col};

    // Check for for upper and/or left boundaries
    if (res.col < 0) {
        res.col = 0;
    }
    if (res.row < 0) {
        res.row = 0;
    }

    // Check for the lower and/or right boundaries
    if (res.col > MAX_COL) {
        res.col = MAX_COL;
    }
    if (res.row > max_row) {
        res.row = max_row;
    }
    return res;
}

bool equals(const Point_t lhs, const Point_t rhs)
{
    return lhs.col == rhs.col && lhs.row == rhs.row;
}

void shrink_rows(Point_t* player, Point_t* obj)
{
    max_row -= 1;
    *player = apply(*player, STILL);
    *obj = apply(*obj, STILL);
}

int8_t max_rows(void)
{
    return max_row;
}
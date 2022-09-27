//
//  main.c
//  group_207
//
//  Created by vno16 on 19:56.
//

#include "point.h"
#include "io.h"

bool should_shrink()
{
    return false;
}

int main(void)
{
    Point_t player = point(0, 0);    

    while (1) {

        display(&point);

        control(&point);

        // If received signal, shrink the column
        if (should_shrink()) {
            shrink_column(&player);
        }
    }

    return 0;
}
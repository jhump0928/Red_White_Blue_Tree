//
//  Display.h
//  3334 Group Project
//
//  Created by Mac J on 11/7/24.
//

#ifndef Display_h
#define Display_h

#include "SDL_Plotter.h"
#include "Font.h"
#include <cmath>

void drawNode(SDL_Plotter& g, string val, int radius, point p, font f) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (sqrt(pow(x, 2) + pow(y, 2)) <= radius) {
                g.plotPixel(x + p.x, y + p.y, 130, 0, 0);
            }
        }
    }
    f.printText(g, val, p.x - radius, p.y - radius + 5);
}

void drawLine(SDL_Plotter &g, point start, point end, color c = color(0, 0, 0)) {
    int dx = abs(end.x - start.x), sx = start.x < end.x ? 1 : -1;
    int dy = -abs(end.y - start.y), sy = start.y < end.y ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        g.plotPixel(start.x, start.y, c.R, c.G, c.B);
        if (start.x == end.x && start.y == end.y) {
                return;
        }
        e2 = 2 * err;
        if (e2 >= dy) {
                err += dy; start.x += sx;
        }
        if (e2 <= dx) {
                err += dx; start.y += sy;
        }
    }
}

#endif /* Display_h */

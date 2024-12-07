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
#include "RBT.h"
#include "Colors.h"
#include <cmath>

// Function to calculate node positions for display
point getNodePosition(int level, int index, int baseX, int baseY, int horizontalSpacing) {
    int x = baseX + index * horizontalSpacing / pow(2, level); // Adjust spacing based on level
    int y = baseY + level * 100;                             // Fixed vertical spacing
    return point(x, y);
}

void drawNode(SDL_Plotter& g, string val, int radius, point p, font f, color c) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (sqrt(pow(x, 2) + pow(y, 2)) <= radius) {
                if (sqrt(pow(x, 2) + pow(y, 2)) >= radius - 2) {
                    g.plotPixel(x + p.x, y + p.y, {0, 0, 0});
                }
                else {
                    g.plotPixel(x + p.x, y + p.y, c);
                }
            }
        }
    }
    f.printText(g, val, p.x - radius, p.y - radius + 10);
}

void drawLine(SDL_Plotter &g, point start, point end, color c = color(0, 0, 0)) {
    int dx = abs(end.x - start.x), sx = start.x < end.x ? 1 : -1;
    int dy = -abs(end.y - start.y), sy = start.y < end.y ? 1 : -1;
    int err = dx + dy, e2;

    while (start.x != end.x or start.y != end.y) {
        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 2; x++) {
                g.plotPixel(start.x + x, start.y + y, c.R, c.G, c.B);
            }
        }

        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            start.x += sx;
        }
        if (e2 <= dx) {
            err += dx;
            start.y += sy;
        }
    }
}

// Function to draw the tree
void drawTree(SDL_Plotter& g, font& iconFont, node* root, int level, int index, int baseX, int baseY, int spacing) {
    if (root == nullptr) return;

    point position = getNodePosition(level, index, baseX, baseY, spacing);

    // Draw current node (circle)
    if (root->data != -1) {
        if (root->glowingFlag == false) {
            if (root->color == 'r') {
                drawNode(g, to_string(root->data), 25, position, iconFont, red); // Circle radius of 25
            }
            else {
                drawNode(g, to_string(root->data), 25, position, iconFont, black);
            }
        }
        else {
            drawNode(g, to_string(root->data), 25, position, iconFont, yellow);
        }



        // Draw left child
        if (root->left != nullptr) {
            point leftPosition = getNodePosition(level + 1, index * 2 - 1, baseX, baseY, spacing);
            if ( root->left->data != -1) {
                drawLine(g, {position.x - 16, position.y + 16}, leftPosition, black);
            }
            drawTree(g, iconFont, root->left, level + 1, index * 2 - 1, baseX, baseY, spacing);
        }

        // Draw right child
        if (root->right != nullptr) {
            point rightPosition = getNodePosition(level + 1, index * 2 + 1, baseX, baseY, spacing);
            if (root->right->data != -1) {
                drawLine(g, {position.x + 16, position.y + 16}, rightPosition, black);
            }
            drawTree(g, iconFont, root->right, level + 1, index * 2 + 1, baseX, baseY, spacing);
        }
    }
}



#endif /* Display_h */
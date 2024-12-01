#include <iostream>
#include <vector>
#include <cmath>
#include "SDL_Plotter.h"

//THIS WILL PROBABLY NOT BE COMPATABLE WITH YOURS MAC, WE MUST COOK



using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Node {
    Point position;
    bool hasLeft, hasRight;
    Node(Point position = Point(), bool hasLeft = false, bool hasRight = false)
        : position(position), hasLeft(hasLeft), hasRight(hasRight) {}
};

void drawCircle(SDL_Plotter &g, Point center, int radius, color c = color(0, 0, 0)) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                g.plotPixel(center.x + x, center.y + y, c.R, c.G, c.B);
            }
        }
    }
}

void drawLine(SDL_Plotter &g, Point start, Point end, color c = color(0, 0, 0)) {
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

void drawBinaryTree(SDL_Plotter &g, vector<Node> &nodes, int depth, int radius = 20) {
    int screenWidth = g.getCol();
    int screenHeight = g.getRow();
    int verticalSpacing = screenHeight / (depth + 1);

    for (int d = 0; d < depth; d++) {
        int levelNodes = pow(2, d);
        int horizontalSpacing = screenWidth / (levelNodes + 1);

        for (int i = 0; i < levelNodes; i++) {
            int nodeIndex = pow(2, d) - 1 + i;
            if (nodeIndex >= nodes.size()) continue;

            // Calculate position
            nodes[nodeIndex].position = Point(
                (i + 1) * horizontalSpacing,
                (d + 1) * verticalSpacing
            );

            // Draw the node
            drawCircle(g, nodes[nodeIndex].position, radius, color(255, 0, 0));

            // Draw lines to children
            int leftChildIndex = 2 * nodeIndex + 1;
            int rightChildIndex = 2 * nodeIndex + 2;

            if (leftChildIndex < nodes.size() && nodes[leftChildIndex].hasLeft) {
                drawLine(g, nodes[nodeIndex].position,
                         nodes[leftChildIndex].position,
                         color(0, 0, 0));
            }

            if (rightChildIndex < nodes.size() && nodes[rightChildIndex].hasRight) {
                drawLine(g, nodes[nodeIndex].position,
                         nodes[rightChildIndex].position,
                         color(0, 0, 0));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Plotter g(700, 1400);
    int maxDepth = 5;
    vector<Node> nodes(31, Node());

    for (int i = 0; i < 15; i++) {
        nodes[i].hasLeft = (2 * i + 1 < 15);  // Has left child
        nodes[i].hasRight = (2 * i + 2 < 15); // Has right child
    }

    while (!g.getQuit()) {
        g.clear();

        drawBinaryTree(g, nodes, maxDepth);

        g.update();
    }

    return 0;
}

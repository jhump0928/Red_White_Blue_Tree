//
//  font.cpp
//  Group Project 1440
//
//  Created by Mac J on 4/24/24.
//

#include "font.h"

letter readLetter(ifstream& input) {
    letter newLetter;
    int pixel;
    for (int x = 0; x < L; x++) {
        for (int y = 0; y < H; y++) {
            input >> pixel;
            newLetter.grid[x][y] = pixel;
        }
    }
    return newLetter;
}

font::font(int s, color c): size(s), col(c) {
    ifstream inputFile;
    inputFile.open("font.txt");
    loadFont(inputFile);
    inputFile.close();
}

void font::loadFont(ifstream& input) {
    for (int i = 0; i < SIZE; i++) {
        letters[i] = readLetter(input);
    }
}

void font::printLetter(SDL_Plotter& g, int num, int posX, int posY) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < L; x++) {
            
            if (letters[num].grid[y][x] == 1) {
                
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        // draw each pixel in 2x2 square
                        g.plotPixel(posX + (x * size) + i, posY + (y * size) + j, col.R, col.G, col.B);
                        // draw shadow effect
                        g.plotPixel(posX + (x * size) + i + size, posY + (y * size) + j + size, 0, 0, 0);
                    }
                }
            }
        }
    }
}

void font::printText(SDL_Plotter& g, string val, int posX, int posY) {
    int offset;
    for (int i = 0; i < val.length(); i++) {
        offset = 87;
        if (isdigit(val[i])) {
            offset = 48;
        }
        if (val[i] != ' ') {
            printLetter(g, (int(val[i]) - offset), posX + (10 * size * i), posY);
        }
    }
}

void font::printTime(SDL_Plotter& g, int posX, int posY) {
    printText(g, "time 0", posX, posY);
}

void font::debugPrintFont(ostream& output) {
    for (int i = 0; i < 36; i++) {
        for (int x = 0; x < L; x++) {
            for (int y = 0; y < H; y++) {
                cout << letters[i].grid[x][y];
            }
            cout << endl;
        }
    }
}

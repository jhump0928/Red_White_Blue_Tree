//
//  font.h
//  Group Project 1440
//
//  Created by Mac J on 4/23/24.
//

#ifndef font_h
#define font_h

#include <fstream>
#include <sstream>
#include "SDL_Plotter.h"
using namespace std;

const int L = 16;
const int H = 16;
const int SIZE = 40;

struct letter {
    int grid[L][H];
    
};

class font {
private:
    letter letters[SIZE];
    int size;
    color col;
    
public:
    font(int s = 1, color c = {255, 255, 255});
    void loadFont(ifstream& input);
    void printLetter(SDL_Plotter& g, int num, int posX, int posY);
    void printText(SDL_Plotter& g, string val, int posX, int posY);
    void printTime(SDL_Plotter& g, int posX, int posY);
    void debugPrintFont(ostream& output);
    
};

letter readLetter(ifstream& input);


#endif /* font_h */

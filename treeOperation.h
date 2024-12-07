//
// Created by jhump on 11/13/2024.
//

#ifndef RBT_GROUP_PROJECT_TREEOPERATION_H
#define RBT_GROUP_PROJECT_TREEOPERATION_H

#include "SDL_Plotter.h"
#include <sstream>
#include <cctype>
#include "colors.h"
#include "Font.h"
#include <stack>
#include <cassert>

using namespace std;

point insertOperationIconPoint(20,20);
point deleteOperationIconPoint(150,20);
point findOperationIconPoint(280,20);

int stringToInt(string inputString){
    stringstream ss;
    ss << inputString;

    int result;
    ss >> result;

    return result;
}

void drawRectangle(SDL_Plotter &g, point upperLeft, int width=100, int height = 40, color c = darkBlue){
    for(int i=upperLeft.x;i<upperLeft.x+width;i++){
        for(int j=upperLeft.y;j<upperLeft.y+height;j++){
            g.plotPixel(i,j,c.R,c.G,c.B);
        }
    }
}

void writeNumber(SDL_Plotter &g, point upperLeft,char digit,int xOffset, font iconFont){
    iconFont.printText(g, to_string(char(digit)),upperLeft.x+xOffset,upperLeft.y+10);
}

class treeOperation{
private:
    int lastEnteredValue;
public:



    //The display function displays the default "Insert" or "Delete" icon.
    //You must pass either "insert" or "delete" as the operation into the function,
    //or else you will throw an exception.
    void display(SDL_Plotter &g, string operation, font iconFont){



        //1b: Font to go on the treeOperations


        //The following code writes characters based off the mode
        if(operation == "insert"){

            drawRectangle(g,insertOperationIconPoint);

            //Following line masks the confirm/backspace text from read mode
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g,"i  insert",insertOperationIconPoint.x,insertOperationIconPoint.y+10);
            iconFont.printText(g,"press k to clear tree",insertOperationIconPoint.x,insertOperationIconPoint.y+45);
        }
        else if (operation == "delete"){

            drawRectangle(g,deleteOperationIconPoint);
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g,"r  remove",deleteOperationIconPoint.x,deleteOperationIconPoint.y+10);
            iconFont.printText(g,"press k to clear tree",insertOperationIconPoint.x,insertOperationIconPoint.y+45);
        }
        else if(operation == "find"){

            drawRectangle(g,findOperationIconPoint);
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g,"f  find",findOperationIconPoint.x,findOperationIconPoint.y+10);
            iconFont.printText(g,"press k to clear tree",insertOperationIconPoint.x,insertOperationIconPoint.y+45);
        }
        else if(operation == "insertRead"){

            drawRectangle(g,insertOperationIconPoint);
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g," ",insertOperationIconPoint.x,insertOperationIconPoint.y+10);
            iconFont.printText(g,"press c to confirm, x to backspace",insertOperationIconPoint.x,insertOperationIconPoint.y+45);

        }
        else if(operation=="deleteRead"){

            drawRectangle(g,deleteOperationIconPoint);
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g," ",deleteOperationIconPoint.x,deleteOperationIconPoint.y+10);
            iconFont.printText(g,"press c to confirm, x to backspace",insertOperationIconPoint.x,insertOperationIconPoint.y+45);
        }
        else if(operation=="findRead"){

            drawRectangle(g,findOperationIconPoint);
            drawRectangle(g,point(20,60),350,20,color(255,255,255));

            iconFont.printText(g," ",findOperationIconPoint.x,findOperationIconPoint.y+10);
            iconFont.printText(g,"press c to confirm, x to backspace",insertOperationIconPoint.x,insertOperationIconPoint.y+45);
        }
        else{
            throw string("Error: Incorrect Operation Argument");
        }

    }



};

#endif //RBT_GROUP_PROJECT_TREEOPERATION_H

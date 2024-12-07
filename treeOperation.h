// RBT Group Project
// Group: Red White and Blue Tree
// Members: Andrew Crotwell, Faith Ota, Ben Collett,
//         Mac Johnson, Jonathan Humphries
// Date Last Edited: 12/7/2024
// Date Due: 12/8/2024

//The following file handles code related to the treeOperation icons in
//the top left corner of the SDL screen. It displays text and the icons
//based off a specified mode.

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

//These points are the top left corner for the icons
point insertOperationIconPoint(20,20);
point deleteOperationIconPoint(150,20);
point findOperationIconPoint(280,20);


//turns a string of numeric digits to an int
int stringToInt(string inputString){
    stringstream ss;
    ss << inputString;

    int result;
    ss >> result;

    return result;
}

//Draws a rectangle with specified size, with a specified color
void drawRectangle(SDL_Plotter &g, point upperLeft, int width=100, int height = 40, color c = darkBlue){
    for(int i=upperLeft.x;i<upperLeft.x+width;i++){
        for(int j=upperLeft.y;j<upperLeft.y+height;j++){
            g.plotPixel(i,j,c.R,c.G,c.B);
        }
    }
}

//Writes a number at a small offset off the upperLeft point
void writeNumber(SDL_Plotter &g, point upperLeft,char digit,int xOffset, font iconFont){
    iconFont.printText(g, to_string(char(digit)),upperLeft.x+xOffset,upperLeft.y+10);
}

//The following class creates and displays the icons for the treeOperations. 
class treeOperation{
private:
    int lastEnteredValue;
public:

    //The display function displays the default "Insert" or "Delete" icon.
    //You must pass either "insert" or "delete" as the operation into the function,
    //or else you will throw an exception.
    void display(SDL_Plotter &g, string operation, font iconFont){

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

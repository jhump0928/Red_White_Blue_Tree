//
//  main.cpp
//  3334 Group Project
//
//  Created by Mac J on 10/22/24.
//

//Agony and pain by Andrew

#include <iostream>
#include <vector>
#include <cmath>
#include "SDL_Plotter.h"
#include "Font.h"
#include "Display.h"
#include "Interface.h"
#include "RBT.h"

using namespace std;

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;

int main(int argc, char* argv[]) { //Apparently main must have arguments in this
    // SDL_Plotter instance
    SDL_Plotter g(SCREEN_HEIGHT, SCREEN_WIDTH);
    
    // RBT instance
    RBT tree;

    // Load fonts
    font iconFont(1, {255, 255, 255});
    font nodeFont(2, {255, 255, 255});

    // Create tree and add test values
    vector<node*> nodes;

    // Variables for UI
    treeOperation operationDisplay;
    string inputNumber;
    bool readMode = false;
    
    treeOperation insertOperationIcon;
    treeOperation deleteOperationIcon;
    treeOperation findOperationIcon;
    bool enterPressed = false;
    int finalNumber;
    char lastOperation;

    // Calculate tree base position and spacing
    int baseX = SCREEN_WIDTH / 2;
    int baseY = 150;
    int spacing = SCREEN_WIDTH / 2;

    // Main draw loop
    while (!g.getQuit()) {

        // Draw UI buttons (I think this is how they work)
        if (!readMode) {
            operationDisplay.display(g, "insert", iconFont);
            operationDisplay.display(g, "delete", iconFont);
            operationDisplay.display(g, "find", iconFont);
        } 

        // Draw tree
        nodes = tree.getLevelOrder();
        tree.printLevelOrder();
        if (nodes.size() > 0) {
            drawTree(g, nodeFont, nodes[0], 0, 0, baseX, baseY, spacing);
        }
        

         //Handle SDL events
//        if (g.kbhit()) {
//            char key = g.getKey();
//            if (isdigit(key)) {
//                inputNumber += key;
//                readMode = true;
//                operationDisplay.display(g, "insertRead", iconFont);
//            } else if (key == 'i' && !inputNumber.empty()) {
//                tree.insert(stringToInt(inputNumber));
//                inputNumber.clear();
//                readMode = false;
//            } else if (key == 'x') {
//                if (!inputNumber.empty()) {
//                    inputNumber.pop_back();
//                }
//            } else if (key == 'q') {
//                break;
//            }
//        }
        
        
        
        
        
        
        
        if(g.kbhit()) {
            char c = tolower(g.getKey()); //this is the key you read in
            cout << c << endl;

            //These 3 if statements change the specified displayed icon to "read" mode
            if (c == 'i') {
                insertOperationIcon.display(g, "insertRead", iconFont);
                lastOperation = 'i';
                readMode = true;
                g.update();
            }
            else if (c == 'r') {
                insertOperationIcon.display(g, "deleteRead", iconFont);
                lastOperation = 'r';
                readMode = true;
                g.update();
            }
            else if (c == 'f') {
                insertOperationIcon.display(g, "findRead", iconFont);
                lastOperation = 'f';
                readMode = true;
                g.update();
            }
            else if (c == 'k') {
                if (nodes.size() > 0) {
                    tree.clearTree(nodes[0]);
                    nodes.clear();
                    g.clear();
                } 
            } 
            else if(c>=48 and c<=57){ //if within 0-9, ASCII
                if(readMode) {
                    if (inputNumber.size() < 2) {
                        inputNumber.push_back(c);
                        if(lastOperation=='i'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,insertOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                                    }
                                }
                        else if(lastOperation=='r'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,deleteOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                                    }
                        }
                        else if(lastOperation=='f'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,findOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                                    }
                        }
                    }
                }
            }
            else if(c=='x'){ //if backspace
                if(readMode) {
                    if (!inputNumber.empty()) {
                        inputNumber.pop_back();

                        int emptySpaces = 2-inputNumber.size();

                        if(lastOperation=='i'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,insertOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                            }

                            for(int i=0;i<emptySpaces;i++){
                                drawRectangle(g,point(insertOperationIconPoint.x+36-12*emptySpaces,
                                                      insertOperationIconPoint.y),
                                              15,30);
                            }
                        }
                        else if(lastOperation=='r'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,deleteOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                            }

                            for(int i=0;i<emptySpaces;i++){
                                drawRectangle(g,point(deleteOperationIconPoint.x+36-12*emptySpaces,
                                                        deleteOperationIconPoint.y),
                                                      15,30);
                            }
                        }
                        else if(lastOperation=='f'){
                            for(int i=0;i<inputNumber.size();i++){
                                writeNumber(g,findOperationIconPoint,inputNumber[i]-48,10+(i*12),iconFont);
                            }

                            for(int i=0;i<emptySpaces;i++){
                                drawRectangle(g,point(findOperationIconPoint.x+36-12*emptySpaces,
                                                                findOperationIconPoint.y),
                                                      15,30);
                            }
                        }
                    }
                }
            }
            else if(c=='c'){// if c (for confirm) is pressed
                if(readMode) {

                    //NOTE: Final Number is what you place into your actual tree.
                    //This is the number that you will call .insert(finalNumber) with
                    if(!inputNumber.empty()) {
                        finalNumber = stringToInt(inputNumber);//only do this if inputNumber is not empty
                        if (lastOperation == 'i') {
                            if (nodes.size() > 0) {
                                drawPath(g, nodes[0], finalNumber, 0, 0, baseX, baseY, spacing);
                            }
                            g.Sleep (400);
                            tree.insert(finalNumber);
                            tree.stopAllGlowing();
                        }
                        else if (lastOperation == 'r') {
                            tree.remove(finalNumber);
                            tree.getLevelOrder();
                            tree.stopAllGlowing();
                            g.clear();
                        } 
                        else if (lastOperation == 'f') {
                            tree.stopAllGlowing();
                            tree.find(finalNumber);
                        }
                    }

                    inputNumber.clear(); //clears inputNumber string
                    readMode = false;

                }
            }
        }
 
        g.update();
    }
    
    
    return 0;
}

//Agony and pain by Andrew

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "SDL_Plotter.h"
#include "Font.h"
#include "Display.h"
#include "Interface.h"
#include "RBT.h"


// Made new simplified version need to merge based on others
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to insert into the binary tree (very bad, hopefully temp)
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}


// Function to calculate node positions for display
point getNodePosition(int level, int index, int baseX, int baseY, int horizontalSpacing) {
    int x = baseX + index * horizontalSpacing / (1 << level); // Adjust spacing based on level
    int y = baseY + level * 100;                             // Fixed vertical spacing
    return point(x, y);
}

// Function to draw the tree *NEEDS FIX*
void drawTree(SDL_Plotter& g, font& iconFont, Node* root, int level, int index, int baseX, int baseY, int spacing) {
    if (root == nullptr) return;

    point position = getNodePosition(level, index, baseX, baseY, spacing);

    // Draw current node (circle)
    drawNode(g, "", 25, position, iconFont); // Circle radius of 25
    iconFont.printText(g, std::to_string(root->value), position.x - 10, position.y - 10);

    // Draw left child
    if (root->left != nullptr) {
        point leftPosition = getNodePosition(level + 1, index * 2, baseX, baseY, spacing);
        drawTree(g, iconFont, root->left, level + 1, index * 2, baseX, baseY, spacing);
    }

    // Draw right child
    if (root->right != nullptr) {
        point rightPosition = getNodePosition(level + 1, index * 2 + 1, baseX, baseY, spacing);
        drawTree(g, iconFont, root->right, level + 1, index * 2 + 1, baseX, baseY, spacing);
    }
}

//using namsepace std; //breaks everything for some reason


const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 700;

int main(int argc, char* argv[]) { //Apparently main must have arguments in this
    // SDL_Plotter instance
    SDL_Plotter g(SCREEN_HEIGHT, SCREEN_WIDTH);

    // Load font
    font iconFont(1, {255, 255, 255});
    std::ifstream fontStream("Font.txt");
    assert(fontStream.is_open());
    iconFont.loadFont(fontStream);
    fontStream.close();

    // Create tree and add test values
    Node* root = nullptr;
    std::vector<int> testValues = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0 ; i < testValues.length() ; i ++) {
        root = insert(root, i);
    }

    // Variables for UI
    treeOperation operationDisplay;
    std::string inputNumber;
    bool readMode = false;

    // Calculate tree base position and spacing
    int baseX = SCREEN_WIDTH / 2;
    int baseY = 150;
    int spacing = SCREEN_WIDTH / 2;

    // Main draw loop
    while (!g.getQuit()) {
        g.clear();

        // Draw UI buttons (I think this is how they work)
        if (!readMode) {
            operationDisplay.display(g, "insert", iconFont);
            operationDisplay.display(g, "delete", iconFont);
            operationDisplay.display(g, "find", iconFont);
        }

        // Draw tree (Once again fix)
        drawTree(g, iconFont, root, 0, 0, baseX, baseY, spacing);

        // Handle SDL events
        if (g.kbhit()) {
            char key = g.getKey();
            if (isdigit(key)) {
                inputNumber += key;
                readMode = true;
                operationDisplay.display(g, "insertRead", iconFont);
            } else if (key == 'i' && !inputNumber.empty()) {
                root = insert(root, stringToInt(inputNumber));
                inputNumber.clear();
                readMode = false;
            } else if (key == 'x') {
                if (!inputNumber.empty()) {
                    inputNumber.pop_back();
                }
            } else if (key == 'q') {
                break;
            }
        }

        g.update();
    }
    
    
    return 0;
}

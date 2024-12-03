//
// Created by jhump on 11/25/2024.
//

#ifndef RED_BLACK_TREE_RBT_H
#define RED_BLACK_TREE_RBT_H

#include <string>
#include <vector>

using namespace std;

struct node{
    int data;
    char color;
    bool isLeftChild;
    bool isRightChild;
    node* parent;
    node* left;
    node* right;

    //Default Constructor = all false/nullptr, and data=0
    node(){
        data = 0;
        color = 'b';
        isLeftChild = false;
        isRightChild = false;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }


    //NOTE: Null Nodes at end are represented with data = -1
    node(int data, char color = 'b', node* parent = nullptr, node* left = nullptr,
         node* right = nullptr, bool isLeftChild = false, bool isRightChild = false)
         {

            this->data = data;
            this->color = color;
            this->parent = parent;
            this->left = left;
            this->right = right;
            this->isLeftChild = isLeftChild;
            this->isRightChild = isRightChild;

        }
};

class RBT{
private:
    node* root;
    int size;
    vector<int> order;
    vector<int> arr;
    vector<char> colors;
    void rotateLeft(node* n){
        node* temp = n->right;

        bool tempLeftChild = false;
        bool tempRightChild = false;

        if(n!=root) {
            if(n->parent->left == n) {
                tempLeftChild = true;
                tempRightChild = false;
            }
            else if(n->parent->right == n) {
                tempRightChild = true;
                tempLeftChild = false;
            }
        }


        if(n!=root) {
            if (n->isLeftChild and tempLeftChild == true) {
                n->parent->left = n->right;

                temp->isLeftChild = true;
                temp->isRightChild = false;

            } else { //n is a right child
                n->parent->right = n->right;

                n->isRightChild = false;
                n->isLeftChild = true;
            }

            temp->parent = n->parent;
        }
        else if(n==root){
            root = n->right;
            temp->parent = nullptr;

            temp->isRightChild = false;
            temp->isLeftChild = false;

            n->isLeftChild = true;
            n->isRightChild = false;

        }

        // temp->left->isLeftChild = false;
        // temp->left->isRightChild = true;

        temp->left->parent = n; //temp's right subtree's parent is now the node n points to
        n->parent = temp; //n's parent is now the node temp points to

        n->right = n->right->left;
        temp->left = n;
    }

    void rotateRight(node* n){
        node* temp = n->left;
        if(n!=root) {
            if (n->isLeftChild) {
                n->parent->left = n->left;

                n->isLeftChild = false;
                n->isRightChild = true;
            } else {
                n->parent->right = n->left;

                temp->isRightChild = true;
                temp->isLeftChild = false;
            }

            temp->parent = n->parent;
        }
        else if(n==root){
            root=n->left;
            temp->parent = nullptr;

            temp->isRightChild = false;
            temp->isLeftChild = false;

            n->isRightChild = true;
            n->isLeftChild = false;
        }
        temp->right->isRightChild = false; //because this subtree goes from being a right to left child
        temp->right->isLeftChild = true;

        temp->right->parent = n; //temp's right subtree's parent is now the node n points to
        n->parent = temp; //n's parent is now the node temp points to

        n->left = n->left->right;
        temp->right = n;
    }


    void recolor(){

    }
    //This function is to be used in tandem with insert
    void handleTree(node* newNode){
        //Adjusting Color, and necessary rotations
        //Case 1: Parent of newNode is black
        if(newNode->parent->color == 'b'){
            newNode->color = 'r';
        }
        //Case 2a: Both parent and uncle of new node are red, and newNode's parent is a left child
        else if(newNode->parent->color == 'r' and newNode->parent->isLeftChild
                and newNode->parent->parent->right->color == 'r'){

            node* currNode = newNode;

            currNode->color = 'r'; //currNode is red
            currNode->parent->color = 'b'; //currNode's parent is black
            currNode->parent->parent->right->color = 'b'; //currNode's uncle is black
            currNode->parent->parent->color = 'r'; //currNode's grandparent is red

            currNode = currNode->parent->parent;

            if(currNode!=root and currNode->parent!=root){
                handleTree(currNode);
            }


        }
        //Case 2b: Both parent and uncle of new node are red, and newNode's parent is a right child
        else if(newNode->parent->color == 'r' and newNode->parent->isRightChild
                and newNode->parent->parent->left->color == 'r'){

            node* currNode = newNode;

            currNode->color = 'r'; //newNode is red
            currNode->parent->color = 'b'; //newNode's parent is black
            currNode->parent->parent->left->color = 'b'; //newNode's uncle is black
            currNode->parent->parent->color = 'r'; //newNode's grandparent is red

            currNode = currNode->parent->parent;
            if(currNode!=root and currNode->parent!=root){
                handleTree(currNode);
            }


        }
        //Case 3a: Parent is red and a right child, uncle is black, and newNode is a right child
        else if(newNode->isRightChild and newNode->parent->isRightChild and
                newNode->parent->color=='r' and newNode->parent->parent->left->color == 'b'){

            newNode->color = 'r';
            newNode->parent->color = 'b';
            newNode->parent->parent->color = 'r';
            rotateLeft(newNode->parent->parent);


        }
        //Case 3b: Parent is red and a left child, uncle is black, and newNode is a left child
        else if(newNode->isLeftChild and newNode->parent->isLeftChild and
                newNode->parent->color=='r' and newNode->parent->parent->right->color == 'b'){

            newNode->color = 'r';
            newNode->parent->color = 'b';
            newNode->parent->parent->color = 'r';
            rotateRight(newNode->parent->parent);


        }
        //Case 4a: Parent is red and a left child, uncle is black, and newNode is a right child
        else if(newNode->isRightChild and newNode->parent->isLeftChild and
                newNode->parent->color=='r' and newNode->parent->parent->right->color == 'b'){

            newNode->color = 'b';
            newNode->parent->color = 'r';
            newNode->parent->parent->color = 'r';

            //Creating these pointers because rotations could change things,
            //simplifies tracking which node the rotation is in relation to.
            node* oldNewNodeGrandparent = newNode->parent->parent;
            node* oldNewNodeParent = newNode->parent;
            rotateLeft(oldNewNodeParent);
            rotateRight(oldNewNodeGrandparent);

        }
        //Case 4b: Parent is red and a right child, uncle is black, and newNode is a left child
        else if(newNode->isLeftChild and newNode->parent->isRightChild and
                newNode->parent->color=='r' and newNode->parent->parent->left->color=='b'){
            newNode->color = 'b';
            newNode->parent->color = 'r';
            newNode->parent->parent->color = 'r';

            //Creating these pointers because rotations could change things,
            //simplifies tracking which node the rotation is in relation to.
            node* oldNewNodeGrandparent = newNode->parent->parent;
            node* oldNewNodeParent = newNode->parent;
            rotateRight(oldNewNodeParent);
            rotateLeft(oldNewNodeGrandparent);
        }


        //Root always black, so recoloring if necessary
        root->color = 'b';
    }
    void createLevelOrder(node* root) {
        if (root == nullptr)
            return;

        // Create an empty queue for level order traversal
        queue<node*> q;

        // Enqueue Root
        q.push(root);

        while (q.empty() == false) {

            // Print front of queue and remove it from queue
            node* node = q.front();
            arr.push_back(node->data);
            colors.push_back(node->color);
            //cerr << node->data << " ";
            q.pop();

            // Enqueue left child
            if (node->left->data != -1)
                q.push(node->left);

            // Enqueue right child
            if (node->right->data != -1)
                q.push(node->right);
        }
        //cerr << endl;
    }
    void printLevelOrder(node* root) {
        createLevelOrder(root);
        arr.clear();
        for(int i=0; i < size; i++) {
            cerr << arr[i] << " ";
        }
        cerr << endl;
    }

public:

    RBT(){
        //Root points to a node with value val
        root = nullptr;
        size=0;
    }

    RBT(int val){

        //Root points to a node with value val
        root = new node(val);

        //The root node's left and right ptrs point to null nodes
        root->left = new node(-1);
        root->left->parent = root;

        root->right = new node(-1);
        root->right->parent = root;

        size=1;
    }


    //destructor
    ~RBT(){
        cout << "DEstructor Called" << endl;
        clearTree(root);
    }
    void clearTree(node* root) {
        if(root->data != -1) {
            clearTree(root->left);
            clearTree(root->right);
            //cout << root->data << " ";
            delete root;
        }
    }
    void createLevelOrder() {
        arr.clear();
        createLevelOrder(root);
    }
    void printLevelOrder() {
        createLevelOrder(root);
        printLevelOrder(root);
    }
    vector<int>& getLevelOrder() {
        arr.clear();
        colors.clear();
        createLevelOrder(root);
        return arr;
    }
    vector<char>& getColorOrder() {
        colors.clear();
        arr.clear();
        createLevelOrder(root);
        return colors;
    }

    node* find(node* root, int val) {
        if (root == NULL || root->data == val)
            return root;
        if (root->data < val)
            return find(root->right, val);
        return find(root->left, val);
    }

void insert(int val){
        if(val<0) {
            throw string("Error: Negative Node Value");
        }
        if(val > 99){
            throw string("Error: Value Too Large");
        }
        order.push_back(val);
        if(root==nullptr){ //If the tree is empty

            //Root points to a node with value val
            root = new node(val);

            //The root node's left and right ptrs point to null nodes
            root->left = new node(-1);
            root->left->parent = root;

            root->right = new node(-1);
            root->right->parent = root;

            root->color = 'b';

        }
        else{ //Tree is not empty

            node *newNode = root; //newNode is used to find correct insertion point

            while (newNode->data != -1) {
                if (val < newNode->data) {
                    newNode = newNode->left;
                } else {
                    newNode = newNode->right;
                }
            }

            //Now, the newNode ptr is pointing to the location where
            //node needs to be inserted.

            //assigning what WAS a null node with a value now, and adjusting its properties
            //Adjusting Data
            newNode->data = val;

            //Adjusting isLeftChild and isRightChild
            if (newNode->parent->left == newNode) {
                newNode->isLeftChild = true;
                newNode->isRightChild = false;
            } else {
                newNode->isLeftChild = false;
                newNode->isRightChild = true;
            }

            //No need to adjust temp's parent because every time a null node is created, it points back to its parent.
            //Thus, the node that was just "inserted" already points back to parent

            //Adjusting left and right:
            //pointing left and right ptrs to null nodes, thus creating null nodes
            newNode->left = new node(-1);
            newNode->left->parent = newNode;
            newNode->left->isLeftChild = true;
            newNode->left->isRightChild = false;

            newNode->right = new node(-1);
            newNode->right->parent = newNode;
            newNode->right->isLeftChild = false;
            newNode->right->isRightChild = true;

            //Adjusting Color, and necessary rotations

            //TODO TEST
            handleTree(newNode);
        }

        size++;
    }
    void transplant(node* oldNode, node* newNode) {
        if(oldNode->parent == nullptr) {
            root = newNode;
        }
        else if( oldNode == oldNode->parent->left) {
            oldNode->parent->left = newNode;
        }
        else {
            oldNode->parent->right = newNode;

        }
        newNode->parent = oldNode->parent;
    }
    node* maxMin(node* p) {
        p = p->left;
        while(p->right->data != -1) {
            p = p->right;
        }
        return p;
    }
    void remove(int val) {
        size--;
        node* z = find(root,val);
        node* y;
        node* x;
        char ogCol = 'b';
        //no Children Case
        if(z->right->data == -1 && z->left->data == -1) {
            //no children
            ogCol = z->color;
            y= z->parent;
            if(z->parent->right == z) {
                y->right = new node(-1);
                x = y->right;
                x->parent = y;
            }
            else {
                z->parent->left = new node(-1);
                x =y->left;
                x->parent = y;
            }
            delete z;

        }
        //RIGHT CHILD
        else if(z->left->data == -1 ) { //right child
            x = z->right;
            transplant(z,x);
        }
        //LEFT CHILD
        else if(z->right->data == -1) { //left child
            x = z->left;
            transplant(z,x);
        }
        //DOUBLE CHILDREN
        else { //case 4 2 children
            y = maxMin(z);
            x = y->left;
            ogCol= y->color;
            if(y->parent == z) {
                x->parent = y;
            }
            else {
                transplant(y,x);
                y->left = z->left;
                y->left->parent = y;
            }
            transplant(z,y);
            y->right = z-> right;
            y->right->parent = y;
            y->color = z->color;
            //y->right=
        }
        //Always ececutes unless replacing red node with double Child
        if(ogCol == 'b' ) {
            removeFix(x);
        }
    }
    void removeFix(node* x) {
        bool doubleBlack = true;
        node* w;
        while( x!= root && x->color == 'b') {
            if(x->parent->left->data == x->data) {
                w = x->parent->right;
            }
            else
                w = x->parent->left;
            //case 1 sbling red
            if(w->color == 'r') {
                w->color ='b';
                x->parent->color = 'r';
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            //case 2 sibling black and both nephews black
            if(w->left->color == 'b' && w->right->color == 'b') {
                w->color = 'r';
                x = x->parent;
            }
            else { // case 3 w is black right nephew red
                if( w->right->color == 'r') {
                    w->right->color = 'b';
                    w->color = 'r';
                    rotateRight(w);
                    w = x->parent->right;
                }
                //case 4 left nephew red
                     w->color = x->parent->color;
                     x->parent->color = 'b';
                     w->left->color = 'b';
                    rotateRight(x->parent);
                     x = root;
            }

        }
        x->color = 'b';
    }
};

#endif //RED_BLACK_TREE_RBT_H

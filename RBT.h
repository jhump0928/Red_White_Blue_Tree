//
// Created by jhump on 11/25/2024.
//

#ifndef RED_BLACK_TREE_RBT_H
#define RED_BLACK_TREE_RBT_H

#include <string>

using namespace std;

struct node{
    int data;
    char color;

    bool isDoubleBlack;
    node* parent;
    node* left;
    node* right;

    //Default Constructor = all false/nullptr, and data=0
    node(){
        data = 0;
        color = 'b';
        isDoubleBlack = false;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }


    //NOTE: Null Nodes at end are represented with data = -1
    node(int data, char color = 'b', node* parent = nullptr, node* left = nullptr,
         node* right = nullptr, bool isLeftChild = false, bool isRightChild = false, bool isDoubleBlack = false)
    {

        this->data = data;
        this->color = color;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->isDoubleBlack = isDoubleBlack;

    }

};

class RBT{
private:
    node* root;
    int size;
    vector<int> arr;
    vector<char> colors;

    void rotateLeft(node* n){
        node* temp = n->right;
        if(n!=root) {
            if (isLeftChild(n)) {
                n->parent->left = n->right;


            } else { //n is a right child
                n->parent->right = n->right;

            }

            temp->parent = n->parent;
        }
        else if(n==root){
            root = n->right;
            temp->parent = nullptr;


        }


        temp->left->parent = n; //temp's right subtree's parent is now the node n points to
        n->parent = temp; //n's parent is now the node temp points to

        n->right = n->right->left;
        temp->left = n;
    }

    void rotateRight(node* n){
        node* temp = n->left;
        if(n!=root) {
            if (isLeftChild(n)) {
                n->parent->left = n->left;

            } else {
                n->parent->right = n->left;

            }

            temp->parent = n->parent;
        }
        else if(n==root){
            root=n->left;
            temp->parent = nullptr;

        }

        temp->right->parent = n; //temp's right subtree's parent is now the node n points to
        n->parent = temp; //n's parent is now the node temp points to

        n->left = n->left->right;
        temp->right = n;
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
        for(int i=0; i < size; i++) {
            cerr << arr[i] << " ";
        }
        cerr << endl;
    }


    //This function is to be used in tandem with insert
    void handleTree(node* newNode){
        //Adjusting Color, and necessary rotations
        //Case 1: Parent of newNode is black
        if(newNode->parent->color == 'b'){
            newNode->color = 'r';
        }
            //Case 2a: Both parent and uncle of new node are red, and newNode's parent is a left child
        else if(newNode->parent->color == 'r' and isLeftChild(newNode->parent)
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
        else if(newNode->parent->color == 'r' and isRightChild(newNode->parent)
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
        else if(isRightChild(newNode) and isRightChild(newNode->parent) and
                newNode->parent->color=='r' and newNode->parent->parent->left->color == 'b'){

            newNode->color = 'r';
            newNode->parent->color = 'b';
            newNode->parent->parent->color = 'r';
            rotateLeft(newNode->parent->parent);


        }
            //Case 3b: Parent is red and a left child, uncle is black, and newNode is a left child
        else if(isLeftChild(newNode) and isLeftChild(newNode->parent) and
                newNode->parent->color=='r' and newNode->parent->parent->right->color == 'b'){

            newNode->color = 'r';
            newNode->parent->color = 'b';
            newNode->parent->parent->color = 'r';
            rotateRight(newNode->parent->parent);


        }
            //Case 4a: Parent is red and a left child, uncle is black, and newNode is a right child
        else if(isRightChild(newNode) and isLeftChild(newNode->parent) and
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
        else if(isLeftChild(newNode) and isRightChild(newNode->parent) and
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


            //No need to adjust temp's parent because every time a null node is created, it points back to its parent.
            //Thus, the node that was just "inserted" already points back to parent

            //Adjusting left and right:
            //pointing left and right ptrs to null nodes, thus creating null nodes
            newNode->left = new node(-1);
            newNode->left->parent = newNode;

            newNode->right = new node(-1);
            newNode->right->parent = newNode;

            //Adjusting Color, and necessary rotations
            handleTree(newNode);

        }

        size++;
    }



    //This function returns the tree position of a node with the value you
    //pass into the function. Otherwise, it throws an exception if node does not exist.
    //It should be part of the RBT Class as a public function
    int getNodePosition(int val){
        node* currNode = root;
        bool found = false;
        int position = 0;

        if (currNode!=nullptr) {
            position = 1; //currNode starts at root, at position 1

            //CurrNode searches for the value, updating position based on if it goes left
            //or right. Going left makes position*=2, whereas going right doubles position
            //and adds 1.
            while (currNode->data!=-1 and !found) {
                if(val<currNode->data){
                    currNode = currNode->left;
                    position *= 2;
                }
                else if(val > currNode->data){
                    currNode = currNode->right;
                    position = (2*position) + 1;
                }
                else{ //the value has been found
                    found = true;
                }
            }

        }

        if(!found) position = -1;

        return position;
    }

    bool isLeftChild(node* currNode){
        bool result = false;

        if(currNode!=root){
            if(currNode->parent->left == currNode){
                result = true;
            }
        }

        return result;
    }

    bool isRightChild(node* currNode){
        bool result = false;

        if(currNode!=root){
            if(currNode->parent->right == currNode){
                result = true;
            }
        }

        return result;
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
    node* getSib(node* x) {
        if(isLeftChild(x) ) {
            return x->parent->right;
        }
        return x->parent->left;
    }
     void remove(int val) {
        size--;
        node* oldNode = find(root,val);
        node* father;
        node* newNode;
        char ogCol = 'b';
        //no Children Case
        if(oldNode->right->data == -1 && oldNode->left->data == -1) {
            //no children
            ogCol = oldNode->color;
            father= oldNode->parent;
            newNode = new node(-1);
            if(oldNode->parent->right == oldNode) {
                father->right = newNode;
                newNode->parent = father;
                if(ogCol == 'b') {
                    newNode->color = 'B';
                }
                delete oldNode;
            }
            else {
                father->left= newNode;
                newNode->parent = father;
                if(ogCol == 'b') {
                    newNode->color = 'B';
                }
                delete oldNode;
            }

        }
        //RIGHT CHILD
        else if(oldNode->left->data == -1 ) { //right child
            newNode = oldNode->right;
            transplant(oldNode,newNode);
            if(newNode->color == 'r' || oldNode->color == 'r') {
                newNode->color = 'b';
                ogCol= 'r';
            }
        }
        //LEFT CHILD
        else if(oldNode->right->data == -1) { //left child
            ogCol= oldNode->color;
            newNode = oldNode->left;
            transplant(oldNode,newNode);
            if(newNode ->color== 'r' || oldNode->color == 'r') {
                newNode->color = 'b';
                ogCol= 'r';
            }
        }
        //DOUBLE CHILDREN
        else { //case 4 2 children
            father = maxMin(oldNode);
            newNode = father->left;
            ogCol= father->color;
            if(father->parent == oldNode) {
                newNode->parent = father;
            }
            else {
                transplant(father,newNode);
                father->left = oldNode->left;
                father->left->parent = father;
            }
            transplant(oldNode,father);
            father->right = oldNode-> right;
            father->right->parent = father;
            father->color = oldNode->color;
            //father->right=
        }
        //Alwafathers ececutes unless replacing red node with double Child
        if(ogCol == 'b' ) {
            newNode->color= 'B';
            removeFix(newNode);
        }
    }
    void removeFix(node* x) {
        node* sib = getSib(x);
        if(root== x) {
            x->color= 'b';
        }
        //-------------------------------------------------
        //sibling is black and atleast one nephew is red
        if(isLeftChild(sib) && sib->color == 'b' && x->color == 'B') {
            //case 1 LEFT LEFT
            if(sib->left->color == 'r') {
                sib->color= sib->parent->color;
                sib->parent->color = 'b';
                rotateRight(sib->parent);
                sib->left->color = 'b';
                x->color = 'b';
                sib = getSib(x);
            }
            //case 2 Left Right
            if(sib->right->color == 'r') {
                sib->right->color = sib->color;
                sib->color = 'r';
                rotateLeft(sib);
                removeFix(x);
            }
        }
        if(isRightChild (sib) && sib->color == 'b'&& x->color == 'B') {
            //case 3 RIGHT RIGHT =
            if(sib->right->color == 'r') {
                sib->color= sib->parent->color;
                sib->parent->color = 'b';
                rotateLeft(sib->parent);
                sib->right->color = 'b';
                x->color = 'b';
            }
            //case 4 RIGHT LEFT
            if(sib->left->color == 'r') {
                sib->left->color = sib->color;
                sib->color = 'r';
                rotateRight(sib);
                removeFix(x);
            }
        }
        //END black red cases
        //CASE B all black cousins ----------------------
        if( x->color == 'B' && sib->color == 'b' &&
            sib->left->color == 'b' &&
            sib->right->color == 'b') {
            sib->color = 'r';
            if(x->parent->color == 'r') {
                x->parent->color = 'b';
            }
            else
                x->parent->color = 'B';
            x->color = 'b';
            removeFix(x->parent);
            }
        //END CASE B ------------------------------
        //-----------------------------------------------
        //CASE C RED SIBLING
        else if(sib->color == 'r' && x->color == 'B') {
            sib->color = 'b';
            sib->parent->color = 'r';
            if(isLeftChild(x)) {
                rotateLeft(x->parent);
            }
            else
                rotateRight(x->parent);
            removeFix(x);
        }
        //END CASE RED SIBLING
    }
};

#endif //RED_BLACK_TREE_RBT_H

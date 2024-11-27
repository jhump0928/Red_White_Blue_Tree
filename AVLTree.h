#include <iostream>
using namespace std;

const int MAX_BALANCE = 1;

template <typename T>
struct Node{
    T data;
    Node<T> *left;
    Node<T> *right;
    int height;
    
    Node(const T& d, Node* lt, Node* rt, int h=0): data(d), left(lt), right(rt)
        , height(h) {}
    
    //Move Constructor: move() will make variable an r-value (DO NOT USE)
    Node(const T&& d, Node* lt, Node* rt, int h=0): data(move(d)), left(lt),
        right(rt), height(h) {}
};

template <typename T>
class AVLTree{
private:
    Node<T> *root;
    
    //clone();
    
    //makeEmpty();
    int height(Node<T> *p){
        int h = 0;
        while(p->left != nullptr || p->right != nullptr){
            h++;
            height(p->left);
            height(p->right);
        }
        return h;
    }

    void insert(const T& value, Node<T>*& p){ //p IS the root, able to modify tree
        if(p == nullptr){
            p = new Node<T>{value, nullptr, nullptr}; //{} for consistency between objects
        }
        else if(value < p->value){
            insert(value, p->left);

        }
        else if(value > p->value){
            insert(value, p->right);
        }
        //no duplicates (no else{})
        balance(p);
    }
    
    void rotateWithLeftChild(Node<T>*& p){ //right rotation
        Node<T>* temp = p->left;
        p->left = temp->right;
        temp->right = p;
        
        //update height:
        p->height = max(height(p->right), height(p->left)) + 1;
        temp->height = max(temp->right->height, height(temp->left)) + 1;
        p = temp;
    }
    
    void rotateWithRightChild(Node<T>*& p){ //left rotation
        Node<T>* temp = p->right;
        p->right = temp->left;
        temp->left = p;
        
        //repair height:
        p->height = max(height(p->right), height(p->left)) + 1;
        temp->height = max(height(temp->right), height(temp->left)) + 1;
        p = temp;
    }
    
    void doubleWithLeftChild(Node<T>*& p){
        rotateWithRightChild(p->left);
        rotateWithLeftChild(p);
    }
    
    void doubleWithRightChild(Node<T>*& p){
        rotateWithLeftChild(p->right);
        rotateWithRightChild(p);
    }
    
    void balance(Node<T>*& p){
        if(p == nullptr){
            return; //base case, no need balance
        }
        
        if(height(p->left) - height(p->right) > MAX_BALANCE){ //which subtree?
            if(heigh(p->left->left) >= height(p->left->right)){ //single/double rotation?
                rotateWithLeftChild(p);
            }
            else{
                doubleWithLeftChild(p);
            }
        }
        
        if(height(p->right) - height(p->left) > MAX_BALANCE){
            if(height(p->right->right) >= height(p->right->left)){
                rotateWithRightChild(p);
            }
            else{
                doubleWithRightChild(p); 
            }
        }
    }
    
public:
    AVLTree(): root(nullptr) {} //root is a pointer NOT a node, no need 4 arg.
    
    //Move Constructor
    AVLTree(AVLTree&& rhs): root(rhs.root){
        rhs.root = nullptr;
    }
    
    //Copy Constructor
    AVLTree(const AVLTree& rhs){
        root = clone(rhs.root); //clone is general function for AVLTree
    }
    
    ~AVLTree(){
        makeEmpty(root);
    }
    
    void insert(const T& d){
        insert(d, root); 
    }
};

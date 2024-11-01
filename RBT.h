/*
 *Author: Faith Ota
 *Title: Red-Black Tree Implementation
 *Date Last Modified: 10/31/2024
 */
#ifndef RBT_h
#define RBT_h

using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    int height=0;
    bool isRed=true;
    
    Node(const T& d, Node<T>* l, Node<T>* r, Node<T>* p): data(d), left(l),
        right(r), parent(p){}
};

template <typename T>
class RBT{
private:
    Node<T>* root;
    //single rotates
    void rotateL(){}
    void rotateR(){}
    
    //double rotates
    void doubleRotateWithLeft(){}
    void doubleRotateWithRight(){}
    
    //rebalance colors
    void rebalance(){}
    
    //insert/remove with a pointer
    void insert(T& val, Node* p){}
    void remove(T& val, Node* p){}
    
    
public:
    RBT():root(nullptr){}
    ~RBT(){ root = nullptr; }
    
    void insert(T& val){}
    void remove(T& val){}
    Node<T>& find(T& val){}
};

#endif /* RBT_h */

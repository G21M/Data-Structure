#include <iostream>
#include "BinarySearchTree.h"
using namespace std;
class AVLTree:public BinarySearchTree
{
private:

    node* LeftRotation(node*);
    node* RightRotation(node*);
    node* Insert(node*, const string &);
    node* Delete(node*,const string &);
public:

    int BalanceFactor(node*);
    void Insert(const string &);

    bool Delete(const string &);

    int Search(string);

    int getCount(string);

    void PrintInOrder();
    void PrintPreOrder();
    void PrintPostOrder();

};

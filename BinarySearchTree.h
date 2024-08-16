#ifndef binarysearchtree_h
#define binarysearchtree_h
#include <iostream>
using namespace std;
class node
{
    public:
        string value;
        int count;
        int height;
        node* right;
        node* left;
        node* parent;
    public:
        node();
        node(string);

        string getValue(){return value;}
        int getCount(){return count;}
        node* getRight(){return right;}
        node* getLeft(){return left;}
        node* getParent(){return parent;}

        void setValue(string str){value = str;}
        void setCount(int c){count = c;}
        void setRight(node* r){right = r;}
        void setLeft(node* l){left = l;}
        void setParent(node* p){parent = p;}
};
class BinarySearchTree
{
    protected:
        node* root;
        bool Insert(node* , const string&);
        node* Search(node* , string);
        void inOrder(node *);
        void preOrder(node *);
        void postOrder(node *);
        bool Delete(node*);
        int getHeight(node* );
        int getWords(node*);
    public:
        BinarySearchTree();


        node* getRoot() const {return root;}

        bool Insert (const string &);
        int Search (string);
        bool Delete(string);

        int getHeight();
        void PrintInOrder();
        void PrintPreOrder();
        void PrintPostOrder();

        node* minNode(node* );
        node* maxNode(node* );

        int getCount(string);
        int getWords();
};


#endif

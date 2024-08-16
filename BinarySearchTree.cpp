#include "BinarySearchTree.h"
// Node constructors either with declaration of the string's value and its count
// or without (we mostly use the one with the declaration)
node::node()
{
    right= nullptr;
    left = nullptr;
    parent = nullptr;
    height = 0;
    count = 0;
}
node::node(string str)
{
    right = nullptr;
    left= nullptr;
    parent = nullptr;
    value = str;
    height = 0;
    count = 1;
}
//Constructor of BST
//Set the root as nullptr in order for the insert to recognise the first insertion
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}
bool BinarySearchTree::Insert(const string & str)
{
    // If the root is null then its the first insertion so create a node with the string and assign it to the root
    if (root==nullptr)
    {
        root = new node(str);
        return true;
    }
     return Insert(root,str); // If the root is not null go on with the normal insertion
}
bool BinarySearchTree::Insert(node * r, const string & str)
{
    if (str==r->getValue())// If the string already exists this condition will become true after recursive calls of the Insert function
    {
        r->setCount(r->getCount()+1);
        return false;
    }
    if (str>r->getValue())// If the string is greater than the root, if the root doesn't have a right child , assign the string to the right child after creating a node
        // If the root has children call the Insert function for the right subtree
        //This is recursive and applies to every node for which the function is calle
    {
        if (r->getRight()== nullptr)
        {
            r->setRight(new node(str));
            r->getRight()->setParent(r);
            return true;
        }
        return Insert(r->getRight(),str);
    }
    else   // If the string is less than the root, if the root doesn't have a left child , assign the string to the left child after creating a node
        // If the root has children call the Insert function for the left subtree
        //This is recursive and applies to every node for which the function is called
    {
        if (r->getLeft()==nullptr)
        {
            r->setLeft(new node(str));
            r->getLeft()->setParent(r);
            return true;
        }
        return Insert(r->getLeft(),str);
    }

}
node* BinarySearchTree::Search(node* p,string str)
{
    // Search in the tree depending every time if the string is greater or less than the value of the node, starting from the root.
    // If the search finds the string or ends in a nullptr return the node
    while (p!= nullptr && p->getValue()!=str)
        if (str>p->getValue())
            p = p->getRight();
        else
            p = p->getLeft();
    return p;
}
// This is the public Search function
// If the private one returned nullptr or the string isn't the correct it returns -1
// If the string is the correct one it returns 1
int BinarySearchTree::Search(string str)
{
    node * p = Search(root,str);
    if (p== nullptr)
        return -1;
    else if (p->getValue() == str)
        return 1;
    else
        return -1;
}
// Traverse the tree inOrder and print the values and the counts of the tree
void BinarySearchTree::inOrder(node * p)
{
    if (p== nullptr)
        return;
    inOrder(p->getLeft());
    cout << p->getValue() << " " << p->getCount() << endl;
    inOrder(p->getRight());
}
//Call the private inOrder for the root
void BinarySearchTree::PrintInOrder()
{
    inOrder(root);
}
// Traverse the tree preOrder and print the values and the counts of the tree
void BinarySearchTree::preOrder(node * p)
{
    if (p == nullptr)
        return;
    cout << p->getValue() << " " << p->getCount() << endl;
    preOrder(p->getLeft());
    preOrder(p->getRight());
}
//Call the private preOrder for the root
void BinarySearchTree::PrintPreOrder()
{
    preOrder(root);
}
// Traverse the tree postOrder and print the values and the counts of the tree
void BinarySearchTree::postOrder(node * p)
{
    if (p == nullptr)
        return;
    postOrder(p->getLeft());
    postOrder(p->getRight());
    cout << p->getValue() << " " << p->getCount() << endl;
}
//Call the private postOrder for the root
void BinarySearchTree::PrintPostOrder()
{
    postOrder(root);
}
//Recursively get the height of its subtree and return the greater of the 2.
int BinarySearchTree::getHeight(node* r)
{
    if (r ==nullptr)
        return 0;
    int left,right;
    left = 1+getHeight(r->getLeft());
    right = 1+getHeight(r->getRight());
    if (left>right)
        return left;
    else
        return right;
}
// Call the private getHeight function
int BinarySearchTree::getHeight()
{
    return getHeight(root);
}
// Find the smallest node in the tree (the one that's most left)
node * BinarySearchTree::minNode(node * r)
{
    node* temp = r;
    while (temp->getLeft()!= nullptr)
        temp = temp->getLeft();
    return temp;
}
// Find the greatest node in the tree (the one that's most right)
node * BinarySearchTree::maxNode(node * r)
{
    node* temp = r;
    while (temp->getRight()!= nullptr)
        temp = temp->getRight();
    return temp;
}
bool BinarySearchTree::Delete(node * child)
{
    node *parent;
    parent = child->getParent();
    if (child->getLeft() == nullptr && child->getRight()==nullptr) //The node we want to delete has no children
    {
        if (parent==nullptr) //If the parent is null then the node is actually the root so we change it to a nullptr
        {
            delete(child);
            root=nullptr;
        }
        else if (parent->getLeft() == child)//If the node is not the root just set the node to nullptr after finding which node it is (left or right of its parent)
        {
            delete (parent->getLeft());
            parent->setLeft(nullptr);
        }
        else
        {
            delete (parent->getRight());
            parent->setRight(nullptr);
        }
    }
    else if (child->getLeft() == nullptr ||child->getRight() == nullptr ) //The node we want to delete has one child
    {
        if (parent==nullptr) // If it's the root change it with its child
        {
            if (child->getLeft() == nullptr)
                root = child->getRight();
            else
                root = child->getLeft();
            delete (child);
        }
        else if (parent->getLeft()==child)  //If its not the root find which node it is (left or right of its parent) and change it with its child
        {
            if (child->getLeft() == nullptr)
                parent->setLeft(child->getRight());
            else
                parent->setLeft(child->getLeft());
            delete (child);
        }
        else
        {
            if (child->getLeft() == nullptr)
                parent->setRight(child->getRight());
            else
                parent->setRight(child->getLeft());
            delete (child);
        }
    }
    else // The node we want to delete has 2 children
    {
        // Find the smallest right child of the node we want to delete and change it with that.
        node *min=minNode(child->getRight());
        child->setValue(min->getValue());
        Delete(min);
    }
    return true;
}
// Call the private delete function
bool BinarySearchTree::Delete(string str)
{
    node *child;
    child = Search(root,str);
    if (child!=nullptr)
        return Delete(child);
    return false;
}
//Return the count of the word after finding which node it is on
int BinarySearchTree::getCount(string str)
{
    return Search(root,str)->getCount();
}
// Call the private getWords function
int BinarySearchTree::getWords()
{
   return BinarySearchTree::getWords(root);
}
// Recursively find the height of the right and left subtree, add 1 (the root) and return it
int BinarySearchTree::getWords(node * r)
{
    if (r== nullptr)
        return 0;
    return 1 + getWords(r->getLeft()) + getWords(r->getRight());
}
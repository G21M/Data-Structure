#include "AVLTree.h"
#include <iostream>
using namespace std;
int AVLTree::BalanceFactor(node* r)//The function calculates and returns the balance of a branch only if
{                                  //the branch is not null.
    if (r == nullptr)
        return 0;
    else
        return getHeight(r->getLeft()) - getHeight(r->getRight());
}

node* AVLTree::LeftRotation(node* r)//The function performs a left rotation to the subtree rooted with r.
{
    node* child = r->getRight();
    node* T = child->getLeft();

    child->setLeft(r);//Performs the rotation
    r->setRight(T);

    return child;//Returns the new root
}
node* AVLTree::RightRotation(node* r)//The function performs a right rotation to the subtree rooted with r.
{
    node* child = r->getLeft();
    node* T = child->getRight();

    child->setRight(r);//Performs the rotation
    r->setLeft(T);

    return child;//Returns the new root
}


void AVLTree::Insert(const string & str)//Insertion function
{
    root = Insert(root,str);
}
node* AVLTree::Insert(node * r, const string &str)
{
    node* searchres = BinarySearchTree::Search(r,str);//Checking if the string is in the tree
    if (r == nullptr)
        return(new node(str));
    if (searchres  == nullptr)//The string is not already in the tree
    {
        if (str < r->getValue())//If the string is less than the value of the node, it recalls the
            r->setLeft(Insert(r->getLeft(), str));//function insert(node*, const string &) for the left subtree.
        else if (str > r->getValue())//If the string is greater than the value of the node, it recalls the
            r->setRight(Insert(r->getRight(), str));//function insert(node*, const string &) for the right subtree.
    }
    else//The string was found. Equal keys are not allowed in BST
    {
        searchres->setCount(searchres->getCount()+1);//Increases the variable count of the word.
        return r;
    }

    int balance = BalanceFactor(r);//Gets the balance of the node r.

    if (balance > 1 && str < r->getLeft()->getValue())//Left Left Case
        return RightRotation(r);
    if (balance < -1 && str > r->getRight()->getValue())//Right Right Case
        return LeftRotation(r);
    if (balance > 1 && str > r->getLeft()->getValue())//Left Right Case
    {
        r->setLeft(LeftRotation(r->getLeft()));//Transform the Left Right Case into a Left Left Case
        return RightRotation(r);
    }
    if (balance < -1 && str < r->getRight()->getValue())//Right Left Case
    {
        r->setRight(RightRotation(r->getRight()));//Transform the Right Left Case into a Right Right Case
        return LeftRotation(r);
    }
    return r;
}
bool AVLTree::Delete(const string &str)
{
    if (root!=nullptr && Search(str)) //Checking if the root is not null and the string we are
    {                                    //looking for is in the tree. If the expression is true,
        root = Delete(root, str);       //we delete the branch that contains the word and the function
        return true;                    //return true. Otherwise, the function returns false.
    }
    else
        return false;
}
node * AVLTree::Delete(node* r, const string & str)
{
    node* t;
    if(str>r->getValue())//If the string is greater than the value of the node, it recalls the function delete
        r->setRight(Delete(r->getRight(),str));//for the right subtree.
    else if (str<r->getValue())//If the string is less than the value of the node, it recalls the function delete
        r->setLeft(Delete(r->getLeft(),str));//for the left subtree.
    else//The string is equal to the node's value
    {
        if (r->getLeft()==nullptr && r->getRight()==nullptr)//Node with no children
        {
            delete r;//Deletion of the branch.
            return nullptr;
        }
        else if (r->getLeft()==nullptr)//Node with only one child, the right one.
        {
            t=r->getRight();//The pointer of the right child is stored temporary.
            delete r;//Deletion of the branch.
            return t;//It returns the pointer of the right child.
        }
        else if (r->getRight()==nullptr)//Node with only one child, the left one.
        {
            t=r->getLeft();//The pointer of the left child is stored temporary
            delete r;//Deletion of the branch
            return t;//It returns the pointer of the left child
        }
        else//Node with two children
        {
            node *min=r->getRight();
            while (min->getLeft()!= nullptr)//Finding the closest value to the deleting node.
                min = min->getLeft();
            r->setValue(min->getValue());//Replacement of the value of the node that has to be deleted by the min's value.
            r->setRight(Delete(r->getRight(),min->getValue()));//Deletion of the node whose value is equal
        }                                                            //with min's value in the right subtree of node r.
    }
    int balance = BalanceFactor(r);
    if (balance > 1 && BalanceFactor(r->getLeft())>=0)//Left Left Case
        return RightRotation(r);
    if (balance < -1 && BalanceFactor(r->getRight())<=0)//Right Right Case
        return LeftRotation(r);
    if (balance > 1 && str > r->getLeft()->getValue())//Left Right Case
    {
        r->setLeft(LeftRotation(r->getLeft()));//Transformation the Left Right Case into a Left Left Case.
        return RightRotation(r);
    }
    if (balance < -1 && str > r->getRight()->getValue())//Right Left Case
    {
        r->setRight(RightRotation(r->getRight()));//Transformation of the Right Left Case into a Right Right Case.
        return LeftRotation(r);
    }
    return r;
}
int AVLTree::Search(string str)//The function uses the BinarySearchTree search function.
{
    return BinarySearchTree::Search(str);
}
void AVLTree::PrintInOrder()//The function uses the BinarySearchTree inOrder function.
{
    BinarySearchTree::inOrder(root);
}


void AVLTree::PrintPreOrder()//The function uses the BinarySearchTree preOrder function.
{
    BinarySearchTree::preOrder(root);
}


void AVLTree::PrintPostOrder()//The function uses the BinarySearchTree postOrder function.
{
    BinarySearchTree::postOrder(root);
}

int AVLTree::getCount(string str)//The function uses the BinarySearchTree search function and returns the count of the node the search function returned
{
    return BinarySearchTree::Search(root,str)->getCount();
}

#include <iostream>
#include "SortedArray.h"
using namespace std;
// Perform binary search by finding a mid position and checking if the given string is
// greater or smaller (alphabetically) than the string in the mid position.
// If its greater search in the right subarray
// If its not search in the left subarray
// Perform the same process using recursion until you either find the word you are searching for
// or find the position in which it should be if it existed in the array.
int binarysearch(adata* a,int l,int h,string x)
{
    int mid;
    if (h>=l)
    {
        mid = l + (h - l) / 2;
        if (a[mid].value == x)
            return mid;
        if (a[mid].value > x)
            return binarysearch(a, l, mid - 1, x);
        if (a[mid].value < x)
            return binarysearch(a, mid+1, h, x);
    }
    return l;
}
// Using binary search either find the position of the string in the array or the position it should be if its not already there
// If the string already exists, increase its count by 1
// If it doesn't, move every string one cell to the right and insert the new string to its correct index position
// This way the array always remains sorted without actually using any sorting algorithm.
void SortedArray::Insert(string str)
{
    if (size==0)
    {
        aData[0].value=str;
        aData[0].count+=1;
        size+=1;
    }
    else
    {
        int searchres = binarysearch(aData,0,size-1,str);
        bool exists=false;
        if (aData[searchres].value==str)
        {
            exists=true;
            aData[searchres].count+=1;
        }
        if (!exists)
        {
            adata *temp;
            if (size%1000==0 || size==1)
            {
                temp = new adata[size + 1000];
                for (int i = 0; i < size; i++) {
                    temp[i] = aData[i];
                }
                delete[] aData;
                aData = temp;
            }
            int insindex= searchres;
            for (int i=size-1;i>=insindex;i--)
                aData[i+1]=aData[i];
            aData[insindex].value = str;
            aData[insindex].count = 1;
            size += 1;

        }
    }
}
// Search for the string using binary search since the array is sorted
// If it is in the array return its position
// If it is not return -1
int SortedArray::Search(string str)
{
    int searchres = binarysearch(aData,0,size-1,str);
    if (aData[searchres].value==str)
        return searchres;
    else
        return -1;
}
// Search for the string using the Search function
// If the string is not present in the array, do nothing
// If it is, create a new temp adata pointer with one less cell
// Perform the same process we used in the Unsorted Array Delete function
void SortedArray::Delete(string str)
{
    int searchres = Search(str);
    int j,q;
    if(searchres!=-1)
    {
        for (j = searchres; j < size - 1; j++)
            aData[j] = aData[j + 1];
        adata *temp;
        temp = new adata[size - 1];
        for (q = 0; q < size - 1; q++)
            temp[q] = aData[q];
        delete[] aData;
        aData = temp;
        size -= 1;
    }
}
int SortedArray::getCount(string str)
{
    return aData[Search(str)].count;
}
#include "UnsortedArray.h"
#include <cstring>
// Constructors either with declaration of size or without
UnsortedArray::UnsortedArray()
{
    aData = new adata[1];
    aData[0].count=0;
    size = 0;
}
UnsortedArray::UnsortedArray(int a)
{
    aData = new adata[a];
    size=a;
    for (int i=0;i<size;i++)
        aData[i].count=0;
}
// Insert a string. If the string already exists increase its count by 1
// If it doesn't once in 1000 words increase the array's size
// Insert the string in the first position with an empty cell and set its initial count as 1
// Increase the size variable by 1
void UnsortedArray::Insert(string str)
{
    if (size==0)
    {
        aData[0].value=str;
        aData[0].count+=1;
        size+=1;
    }
    else
    {
        bool exists=false;
        for (int i=0;i<size;i++)
            if(str==aData[i].value)
            {
                aData[i].count++;
                exists=true;
                break;
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
                aData[size].value = str;
                aData[size].count = 1;
                size += 1;
        }
    }
}
// Print the Array
void UnsortedArray::PrintArray()
{
    int i;
    for (i=0;i<size;i++)
        cout << i+1 << ". " << aData[i].value << " " << aData[i].count << endl;
}
// Use serial search to find the string (since the array is unsorted)
// Return its position in the array if found
// Return -1 if not.
int UnsortedArray::Search(string str)
{
    int i;
    int result=-1;
    for (i=0;i<size;i++)
    {
        if (aData[i].value==str)
            result=i;
    }
    if (result>=0)
        return result;
    else
        return -1;
}
// Use the search function to check if the string we want to delete is in the array
// If it is not, return
// If it is create a new temporary adata struct pointer with one less cell
// Move every value from the position of the string we want to delete one cell to the left
// Copy the temp pointer the main aData pointer after deleting the old one.
void UnsortedArray::Delete(string str)
{
    if (Search(str)==-1)
        return;
    int i,j,q;
            for (j = Search(str); j < size - 1; j++)
                aData[j] = aData[j + 1];
            adata *temp;
            temp = new adata[size - 1];
            for (q = 0; q < size - 1; q++)
                temp[q] = aData[q];
            delete[] aData;
            aData = temp;
            size -= 1;

}
// Use the search function to find the position of the string and return its count.
int UnsortedArray::getCount(string str)
{
    return aData[Search(str)].count;
}
//Return the number of words present in the array by returning its size
int UnsortedArray::getWords()
{
    return size;
}
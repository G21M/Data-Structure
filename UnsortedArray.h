#ifndef UnsortedArray_h
#define UnsortedArray_h

#include <iostream>
using namespace std;
typedef struct adata
{
    string value;
    int count;
}adata;
class UnsortedArray
{
protected:
    adata* aData;
    int size;
public:
    UnsortedArray();
    UnsortedArray(int);
    void Insert(string);
    void Delete(string);
    int Search(string);
    void PrintArray();
    int getCount(string);
    int getWords();
};
#endif

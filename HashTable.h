#include <iostream>
using namespace std;
class HashTable
{
    typedef struct adata
    {
        string value;
        int count;
    }adata;
    private:
        adata* aData;
        int size;
        int words;
    public:
        HashTable();
        HashTable(int);

        long long int Insert(string);
        long long int Search(string);

        int getCount(string);
        int getWords(){return words;}
        void Print();
};


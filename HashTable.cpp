#include "HashTable.h"
// This function is used to create the hash key used for the insertion of the words in the table
// Multiplying by some prime numbers helps reduce collisions along with a factor dependent from i
// so that words with the same letters have different hash keys if the letters are in different positions
long long int getHashKey(string str)
{
    long long int key=0;
    for(int i=0;i<str.length();i++)
        key+=str[i]*31*19*7*3*(i+3);
    return key;
}
// Constructor either with declaration of size or without. Starts at 10000 words so that rehashing isn't performed a lot of times
// Sets the value of all the words to "." in order to differentiate them from the ones that have actual values
// This happens in order for the insertion and search functions to work
HashTable::HashTable()
{
    aData = new adata[10000];
    size=10000;
    for (int i=0;i<size;i++)
        aData[i].value=".";
    words=0;
}
HashTable::HashTable(int s)
{
    aData = new adata[s];
    size=s;
    for (int i=0;i<s;i++)
        aData[i].value=".";
    words=0;
}
// Find the hash key of the string if its not empty
// Search for the word using the search function until you either find the word or find out that the word doesn't exist in the table
// If the word is already there, increase its count by 1
// If its not insert it and set its count to 1;
// Increase the number of words inserted
// When the number of words inserted becomes larger than the size of the table divided by 2 rehash.
// Insert the words from the previous hash table adata to a new temporary adata struct and copy their count.
// Assign the temporary adata struct to the adata of the class' hash table.
long long int HashTable::Insert(string str)
{
    long long int key = getHashKey(str);
    long long int searchres = Search(str);
    if (searchres!=-1 )
        aData[searchres].count+=1;
    else
    {
        while (aData[key % size].value != ".")
        {
            key++;
        }
        aData[key%size].value=str;
        aData[key%size].count=1;
        words++;
        return key%size;
    }
    if (words>=size/2)
    {
        HashTable temp(2*size);
        for (int i=0;i<size;i++)
        {
            if (aData[i].value!=".")
            {
                temp.Insert(aData[i].value);
                temp.aData[temp.Search(aData[i].value)].count=aData[i].count;
            }
        }
        size*=2;
        *this = temp;
    }
    return 0;

}
// Search by finding the hashkey and checking if the string is in that position
// If its not continue by moving one place to the right
// If the string is found return its position
// If the string is not found return -1
long long int HashTable::Search(string str)
{
    long long int key = getHashKey(str);
    while (aData[key%size].value!=".")
    {
        if (aData[key%size].value==str)
            return key%size;
        key++;
    }
    return -1;
}
// Print the contents of the Hash Table
void HashTable::Print()
{
    for (int i=0;i<size;i++)
        if (aData[i].value!=".")
        cout << aData[i].value << " " << aData[i].count << endl;
}
// Find a string in the Hash Table and return its count
int HashTable::getCount(string str)
{
    return aData[Search(str)].count;
}

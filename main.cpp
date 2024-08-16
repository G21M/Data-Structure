#include <iostream>
#include <fstream>
#include <chrono>
#include "UnsortedArray.h"
//#include "SortedArray.h"
//#include "BinarySearchTree.h"
//#include "HashTable.h"
//#include "AVLTree.h"

using namespace std;
using namespace std::chrono;
int countWords(ifstream &ifs)
{
    string temp;
    int i = 0;
    while (ifs >> temp)
    {
        i++;
    }
    return i;
}
bool deleteSpecialChars(string & temp)
{
    int j;
    for (j=0;j<temp.length();j++)
    {
        if ((temp[j] >= 'A' && temp[j] <= 'Z'))
            temp[j]+=32;
        if ((temp[j] < 'a' || temp[j] > 'z') && (temp[j] < 'A' || temp[j] > 'Z'))
        {

            temp.erase(temp.begin() + j);
            j-=1;
        }
    }
    if (!temp.empty())
        return true;
    else
        return false;
}
int main()
{
    HashTable HT;
    BinarySearchTree BST;
    SortedArray SA;
    UnsortedArray UA;
    AVLTree AVL;
    string* a;
    string* q;
    string temp;
    long long int i,count=0;
    ifstream ifs;
    ofstream ofs;
    string filename="small-file.txt";
    ifs.open(filename);
    // Count the number of words in the next, taking into factor the words that might come from a possible split
    if (ifs.is_open())
    {
        count = countWords(ifs);
        ifs.close();
        ifs.open(filename);
    }
    // Read the words and assign them to the string pointer.
    if (ifs.is_open())
    {
        a = new string[count];
        cout << "File opened.";
        for (i = 0; ifs >> temp; i++)
        {
            // Check for special characters or split words
            if (deleteSpecialChars(temp))
            {
                // If the string isn't empty after deleting all the characters assign it to the string pointer.
                a[i] = temp;
            } else
            {
                // If it's empty reduce the number of words by one.
                i--;
            }
        }
        auto start = high_resolution_clock::now();
        count = i;
        for (i = 0; i < count; i++)
        {

                SA.Insert(a[i]);
                BST.Insert(a[i]);
                AVL.Insert(a[i]);
                HT.Insert(a[i]);
                UA.Insert(a[i]);

        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        int searchsize = 1000;
        (srand(time(nullptr)));
        q = new string[searchsize];
        for (i=0;i<searchsize;i++)
        {
            q[i]=a[rand()%count];
        }
        ofs.open("output5.txt");
        if (ofs.is_open())
        {
            ofs << "The insertion took " << duration.count() << " milliseconds." << endl;
            // Search in the unsorted array
            start = high_resolution_clock::now();
            for (i = 0; i < searchsize; i++)
            {
                if (UA.Search(q[i])!=-1)
                    ofs << "Found the word \"" << q[i] << "\" " << UA.getCount(q[i]) << " times in the unsorted array." << endl;
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            ofs << "The search of the unsorted array took " << duration.count() << " milliseconds." << endl;
            // Search in the sorted array
            start = high_resolution_clock::now();
            for (i = 0; i < searchsize; i++)
            {
                if (SA.Search(q[i])!=-1)
                    ofs << "Found the word \"" << q[i] << "\" " << SA.getCount(q[i]) << " times in the sorted array." << endl;
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            ofs << "The search of the sorted array took " << duration.count() << " milliseconds." << endl;
            // Search in the binary search tree array
            start = high_resolution_clock::now();
            for (i = 0; i < searchsize; i++)
            {
                if (BST.Search(q[i])!=-1)
                    ofs << "Found the word \"" << q[i] << "\" " << BST.getCount(q[i]) << " times in the BST." << endl;
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            ofs << "The search of the binary search tree took " << duration.count() << " milliseconds." << endl;
            // Search in the AVL tree
            start = high_resolution_clock::now();
            for (i = 0; i < searchsize; i++)
            {
                if (AVL.Search(q[i])!=-1)
                    ofs << "Found the word \"" << q[i] << "\" " << AVL.getCount(q[i]) << " times in the AVL tree." << endl;
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            ofs << "The search of the AVL tree took " << duration.count() << " milliseconds." << endl;
            // Search in the hash table
            start = high_resolution_clock::now();
            for (i = 0; i < searchsize; i++)
            {
                if (HT.Search(q[i])!=-1)
                    ofs << "Found the word \"" << q[i] << "\" " << HT.getCount(q[i]) << " times in the hash table." << endl;
            }
            stop = high_resolution_clock::now();
            duration = duration_cast<milliseconds>(stop - start);
            ofs << "The search of the hashtable took " << duration.count() << " milliseconds." << endl;
        }
    }
    else
        cout << "File error.";

}
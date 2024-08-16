#include "UnsortedArray.h"
#ifndef PROJECT2021_SORTEDARRAY_H
#define PROJECT2021_SORTEDARRAY_H

// The sorted array class inherits most of its components from the unsorted array class
// However the main functions are changed in order for the array to always remain sorted
class SortedArray : public UnsortedArray
{
    public:
        void Insert(string);
        int Search(string);
        void Delete(string);

        int getCount(string);
};


#endif //PROJECT2021_SORTEDARRAY_H

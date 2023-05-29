#ifndef FILTER_ITERATOR_H
#define FILTER_ITERATOR_H

#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>

// 
// @PURPOSE: to provide different ways to iterate data items
//
// @CLASSES: QuDataSet, QuDataSet::Iterator
// 
// @DESCRIPTION: single data buffer (vector is used here to store data), we can iterate the data in 
//  different ways based on a filter function provided. If no filter function is provided, the 
//  iterator will traverse all items.
//
//  for example, for following data items, we can create different iterators based on filters:
//  data:      |d0 |d1 |d2 |d3 |d4 |d5 |d6 |d7 |d8 |d9 |d10|d11|d12|d13|d14|d15|d16|d17|d18|d19|...
//  default      0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19 ...
//  filter1              0           1   2                       3           4           5      ...
//  filter2      0               1               2                               3              ...
// 
// @USAGE: a usage example of how to use multi iterators is provided in test.cpp 
// 
namespace qujifa::iterator {
 
                            //---------------- 
                            // Class QuDataSet
                            //---------------- 

template <typename T>
class QuDataSet {
    std::vector<T>                  d_data;         // data buffer
    std::function<bool(const T&)>   d_function;     // filter function

    // calculate current index based on filter
    size_t current(size_t curr);
public:
    QuDataSet() { d_function = [](const T& val) {return true;}; }
    std::vector<T>& data() { return d_data; }

   // using ITERATOR_T = DATA_T::iterator;

    class Iterator  {
        QuDataSet<T>*                   d_ptr;      // pointer to QuDataSet object
        size_t                          d_current;  // current index in d_data vector
    public:
        Iterator(QuDataSet* ptr, size_t curr) : d_ptr(ptr), d_current(curr) {}

        // pre increment
        Iterator& operator++() {
            d_current = d_ptr->current(++d_current);
            return *this;
        }

        // post increment
        Iterator& operator++(int) {
            Iterator* tmp = this;
            d_current = d_ptr->current(++d_current);
            return *tmp;
        }
        T& operator*() { return d_ptr->d_data[d_current];}
        // return a reference

        T* operator->() {return &(d_ptr->d_data[d_current]);}
        // return a pointer

        // compare two iterator objects
        bool operator!=(const Iterator& rhs) {return d_current != rhs.d_current;}
        bool operator==(const Iterator& rhs) {return d_current == rhs.d_current;}
    };

    // provide a filter function, by default, iterator will traverse all items
    void setFilter(std::function<bool(const T&)> f = [](const T& val) {return true;}) { d_function = f; }

    // iterator begin
    Iterator begin() { return {this, current(0)}; }

    // iterator end
    Iterator end() { return {this, d_data.size()};}
};

template<typename T>
size_t QuDataSet<T>::current(size_t curr) {
    while(curr < d_data.size() && !d_function(d_data[curr]))
        ++curr;
    return curr;
}

} // close of namespace qujifa::iterator

#endif

#include <iostream>
#include "UnorderedArray.h"
#include "array_helpers.h"

using namespace std;

/**
 * @brief           constructor
 * @param size      size of array
 */
UnorderedArray::UnorderedArray(long size) {
    array = new Pair*[size];
    this->size = size;
    next_free_slot = 0;
}

/**
 * @brief           destructor
 */
UnorderedArray::~UnorderedArray() {
    delete[] array;
}

/**
 * @brief           insert pair in array
 * @param pair      pair to insert
 * @return true     pair inserted successfully
 * @return false    pair insertion failed
 */
bool UnorderedArray::insert(Pair* pair) {
    long pos = search(pair);
    if (pos != -1) { // if pair is already in array 
        array[pos]->increment_occurrences();
        return true;
    }
    else { // if pair is not present in array 
        array[next_free_slot] = pair;
        next_free_slot++;
        return true;
    }
    return false;
}

/**
 * @brief           search pair in array
 * @param pair      pair to search
 * @return long     if pair is found return position in array, else -1
 */
long UnorderedArray::search(Pair* pair) {
    for (long i=0; i<next_free_slot; i++)
        if (*array[i] == *pair)
            return i;
    return -1;
}

/**
 * @brief           remove pair from array
 * @param pair      pair to remove
 * @return true     pair removed successfully
 * @return false    pair not removed
 */
bool UnorderedArray::remove(Pair* pair) {
    long pos = search(pair);
    if (pos != -1) { // if pair exists
        for (long i = pos; i < size-1; i++)
            array[i] = array[i+1];
        next_free_slot--;
        return true;
    }
    return false;
}

/**
 * @brief           print all pairs
 */
void UnorderedArray::print() {
    for (long i=0; i < next_free_slot; i++)
        cout << *array[i] << endl;
    cout << endl;
}
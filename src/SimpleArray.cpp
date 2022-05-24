#include <iostream>
#include "array_helpers.h"
#include "SimpleArray.h"

using namespace std;

/**
 * @brief           constructor
 * @param size      size of array
 */
SimpleArray::SimpleArray(long size) {
    array = new Pair*[size];
    this->size = size;
    next_free_slot = 0;
}

/**
 * @brief           destructor
 */
SimpleArray::~SimpleArray() {
    delete[] array;
}

/**
 * @brief           insert pair in array
 * @param pair      pair to insert
 * @return true     pair inserted successfully
 * @return false    pair insertion failed
 */
bool SimpleArray::insert(Pair* pair) {
    if (next_free_slot < size) { // if array has enough free space
        array[next_free_slot] = pair;
        next_free_slot++;
        return true;
    }
    else { // if free space is insufficient, create new array of doubled size and try again
        Pair** new_array = new Pair*[size*2];
        clone_array(new_array, array, size);
        array = new_array;
        size = size*2;
        array[next_free_slot] = pair;
        next_free_slot++;
        return true;
    }
    return false;
}

/**
 * @brief           print all pairs
 */
void SimpleArray::print() {
    for (long i=0; i < next_free_slot; i++) {
        cout << *array[i] << endl;
    }
    cout << endl;
}
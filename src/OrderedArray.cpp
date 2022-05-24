#include <iostream>
#include "OrderedArray.h"
#include "array_helpers.h"

using namespace std;

/**
 * @brief           constructor
 * @param size      size of array
 */
OrderedArray::OrderedArray(long size) {
    array = new Pair*[size];
    this->size = size;
	used_slots = 0;
}

/**
 * @brief           destructor
 */
OrderedArray::~OrderedArray() {
    delete[] array;
}

/**
 * @brief           insert pair in array
 * @param pair      pair to insert
 * @return true     pair inserted successfully
 * @return false    pair insertion failed
 */
bool OrderedArray::insert(Pair* pair) {
	long pos = search(pair, 0, used_slots-1);
    if (pos != -1) { // if pair is already in array 
        array[pos]->increment_occurrences();
        return true;
    }
	else { // if pair is not present in array 
        long i;
        for (i = used_slots - 1; (i >= 0 && (*array[i] > *pair)); i--)
            array[i+1] = array[i];
        array[i+1] = pair;
        used_slots++;
        return true;
    }
    return false;
}

// binary search pair in array
/**
 * @brief           binary search pair in array
 * 
 * @param pair      pair to search
 * @param start     binary search start point
 * @param end       binary search end point
 * @return long     if pair is found return position in array, else -1
 */
long OrderedArray::search(Pair* pair, long start, long end) {
    if (end >= start) {
        long m = start + (end - start) / 2;
        if (*array[m] == *pair)
            return m;
        else if (*array[m] > *pair)
            return search(pair, start, m - 1);
        else
            return search(pair, m + 1, end);
    }
    return -1;
}

/**
 * @brief           remove pair from array
 * @param pair      pair to remove
 * @return true     pair removed successfully
 * @return false    pair not removed
 */
bool OrderedArray::remove(Pair* pair) { 
    long pos = search(pair, 0, used_slots-1); 
    if (pos != -1) { 
		for (long i = pos; i < used_slots-1; i++)
			array[i] = array[i+1];
		used_slots--;
		return true; 
    } 
    return false;
} 

/**
 * @brief           print all pairs
 */
void OrderedArray::print() {
    for (long i=0; i < used_slots; i++)
        cout << *array[i] << endl;
    cout << endl;
}
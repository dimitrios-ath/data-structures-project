#include <iostream>
#include <string>
#include "HashTable.h"
#include "Pair.h"
#include "array_helpers.h"

using namespace std;

/**
 * @brief           constructor
 * @param size      size of hash table
 */
HashTable::HashTable(long size) {
    hashtable = new Pair*[size*2];
    this->size = size;
    used_slots = 0;
}

/**
 * @brief           destructor
 */
HashTable::~HashTable() {
    delete[] hashtable;
}

/**
 * @brief                   calculate hash for given pair
 * @param pair              pair to calculate hash for
 * @return unsigned long    hash
 */
unsigned long HashTable::pair_hash(Pair* pair) { // hash function found at: http://www.cse.yorku.ca/~oz/hash.html
    string pair_concated = pair->getWord1()+pair->getWord2();
    unsigned long hash = 5381;
    unsigned int l = pair_concated.length();
    for (int i = 0; i<l ; i++)
        hash = ((hash << 5) + hash) + (pair_concated[i]);
    return hash%size;
}

/**
 * @brief           insert pair in hash table
 * @param pair      pair to insert
 * @return true     pair inserted successfully
 * @return false    pair insertion failed
 */
bool HashTable::insert(Pair* pair) {
    unsigned long hash, first_hash;
    hash = pair_hash(pair); // calculate hash for given pair
    first_hash = hash;
    do {
        if (!hashtable[hash]) { // if slot is free
            hashtable[hash] = pair;
            return true;
        }
        else if (*hashtable[hash] == *pair) { // if pair is already in the hash table
            hashtable[hash]->increment_occurrences();
            return true;
        }
        else
            hash = (hash+1) % size;
    } while (first_hash != hash);
    return false;
}

/**
 * @brief           search pair in hash table
 * @param pair      pair to search
 * @return long     if pair is found return position in hash table, else -1
 */
long HashTable::search(Pair* pair) {
    unsigned long hash, first_hash;
    hash = pair_hash(pair); // calculate hash for given pair
    first_hash = hash;
    do {
        if (hashtable[hash]) {
            if (*hashtable[hash] == *pair) // if given pair is found
                return hash;
            else
                hash = (hash+1) % size;    
        }
        else
            hash = (hash+1) % size;
    } while (first_hash != hash);
    return -1;
}

/**
 * @brief           remove pair from hash table
 * @param pair      pair to remove
 * @return true     pair removed successfully
 * @return false    pair not removed
 */
bool HashTable::remove(Pair* pair) {
    unsigned long hash, first_hash;
    hash = pair_hash(pair); // calculate hash for given pair
    first_hash = hash;
    do {
        if (hashtable[hash]) {
            if (*hashtable[hash] == *pair) {
                hashtable[hash] = NULL;
                return true;
            }
            else
                hash = (hash+1) % size;
        }
        else
            hash = (hash+1) % size;
    } while (first_hash != hash);
    return false;
}

/**
 * @brief           print all pairs
 */
void HashTable::print() {
    for (long i=0; i < size; i++)
        if (hashtable[i])
            cout << *hashtable[i] << endl;
    cout << endl;
}
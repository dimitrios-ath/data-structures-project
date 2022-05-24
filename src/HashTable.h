#pragma once
#include <iostream>
#include "Pair.h"

using namespace std;

class HashTable{
    public:
        HashTable(long size);
        ~HashTable();
        unsigned long pair_hash(Pair* pair);
        Pair* get_pair(long index) { return hashtable[index]; }
        long search(Pair* pair);
        bool insert(Pair* pair);
        bool remove(Pair* pair);
		void print();
    private:
        Pair** hashtable;
        long size;
        long used_slots;
};
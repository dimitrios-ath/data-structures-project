#pragma once
#include "Pair.h"

class UnorderedArray{
    private:
        Pair** array;
        long size;
        long next_free_slot;
    public:
        UnorderedArray(long size);
        ~UnorderedArray();
        Pair* get_pair(long index) { return array[index]; }
        bool insert(Pair* pair);
        long search(Pair* pair);
        bool remove(Pair* pair);
        void print();
};
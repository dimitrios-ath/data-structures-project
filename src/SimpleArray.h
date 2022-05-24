#pragma once
#include "Pair.h"

class SimpleArray {
    public:
        Pair** array;
        long size;
        long next_free_slot;
        SimpleArray(long size);
        ~SimpleArray();
        bool insert(Pair* pair);
        void print();
};
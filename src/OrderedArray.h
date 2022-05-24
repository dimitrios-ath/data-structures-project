#pragma once
#include "Pair.h"

class OrderedArray{
	private:
        Pair** array;
        long size;
		long used_slots;
    public:
        OrderedArray(long size);
        ~OrderedArray();
        Pair* get_pair(long index) { return array[index]; }
        long get_used_slots() { return used_slots; } 
        long search(Pair* pair, long start, long end);
        bool insert(Pair* pair);
        bool remove(Pair* pair);
		void print();
};
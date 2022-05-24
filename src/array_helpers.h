#pragma once
#include "Pair.h"

/**
 * @brief           copy source array contents to destination
 * @param dst       destination array 
 * @param src       source array 
 * @param size      source array size
 */
static void clone_array(Pair** dst, Pair** src, long size) {
    for (long i=0; i < size; i++) {
        dst[i] = src[i];
    }
    delete[] src;
}
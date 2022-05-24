#include <iostream>
#include "Pair.h"

/**
 * @brief           constructor
 * @param word1     first word
 * @param word2     second word
 */
Pair::Pair(string word1, string word2) {
    this->word1 = word1;
    this->word2 = word2;
    occurrences = 1;
}

/**
 * @brief           getters and setters
 */
string Pair::getWord1() { return word1; }
string Pair::getWord2() { return word2; }
int Pair::get_occurrences() { return occurrences; }
void Pair::setWord1(string word1) { this->word1 = word1; }
void Pair::setWord2(string word2) { this->word2 = word2; }       
void Pair::increment_occurrences() { occurrences++; }

/**
 * @brief           operator to compare two pairs (equal)
 * @param pair      pair to compare to
 * @return true     equal to pair
 * @return false    not equal to pair
 */
bool Pair::operator==(Pair pair) {
    if (word1 == pair.getWord1() && word2 == pair.getWord2())
        return true;
    return false;
}

/**
 * @brief           operator to compare two pairs (greater)
 * @param pair      pair to compare to
 * @return true     greater than pair
 * @return false    not greater than pair
 */
bool Pair::operator>(Pair pair) {
    if (word1 > pair.getWord1() || (word1 == pair.getWord1() && word2 > pair.getWord2()))
        return true;
    return false;
}

// operators to compare two pairs (less)
/**
 * @brief           operator to compare two pairs (less)
 * @param pair      pair to compare to
 * @return true     less than pair
 * @return false    not less than pair
 */
bool Pair::operator<(Pair pair) {
    if (word1 < pair.getWord1() || (word1 == pair.getWord1() && word2 < pair.getWord2()))
        return true;
    return false;
}

/**
 * @brief           output stream operator for pair
 * @param os        output stream
 * @param pair      pair
 * @return ostream& 
 */
ostream & operator<<(ostream &os, Pair &pair) {
    os << pair.getWord1() << " " << pair.getWord2() << " [" << pair.get_occurrences() << "]"; // format: "word1, word2 [occurrences]"
    return os;
}
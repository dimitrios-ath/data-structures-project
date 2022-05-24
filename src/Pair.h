#pragma once
#include <string>

using namespace std;

class Pair{
    private:
        string word1;
        string word2;
        int occurrences;
  
    public:
        Pair(string word1, string word2);
        string getWord1();
        string getWord2();
        int get_occurrences();
        void setWord1(string word1);
        void setWord2(string word2);
        void increment_occurrences();
        bool operator==(Pair pair);
        bool operator>(Pair pair);
        bool operator<(Pair pair);
        friend ostream &operator<<(ostream &os, Pair &pair);
};
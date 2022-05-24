#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "SimpleArray.h"
#include "UnorderedArray.h"
#include "OrderedArray.h"
#include "BSTree.h"
#include "AVLTree.h"
#include "HashTable.h"

#define Q_SIZE 1000
#define OUTFILE "output.txt"

using namespace std;
using namespace std::chrono;

string format_word(string word) {
    word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return word;
}

int main(int argc, char *argv[]) {
    if (argc==2) {
        ifstream in_file;
        in_file.open(argv[1]);
        if (in_file.is_open()) {
            ofstream out_file;
            out_file.open(OUTFILE);
            out_file << "Data Structures Project" << endl;
            out_file.setf(ios::fixed, ios::floatfield);
            out_file.setf(ios::showpoint);

            time_point<high_resolution_clock> total_start = high_resolution_clock::now();
            string word1;
            string word2;
            
            // initialize a simple array to hold all pairs
            SimpleArray* simple_array = new SimpleArray(1000);

            // parse words from file
            in_file >> word1;
            word1 = format_word(word1);
            while (in_file >> word2) {
                word2 = format_word(word2);
                simple_array->insert(new Pair(word1, word2));
                word1 = word2;
            }

            // cout << "[+] reading pairs from file completed" << endl; // debug

            UnorderedArray* unordered_array = new UnorderedArray(simple_array->next_free_slot);
            OrderedArray* ordered_array = new OrderedArray(simple_array->next_free_slot);
            BSTree* bst = NULL;
            AVLTree* avl = NULL;
            HashTable* hashtable = new HashTable(simple_array->next_free_slot);
            
            time_point<high_resolution_clock> start, stop;

            // add pairs to data structures
            // cout << "[*] adding pairs to data structures" << endl; // debug

            start = high_resolution_clock::now();
            for (long i=0; i<simple_array->next_free_slot; i++)
                unordered_array->insert(new Pair(simple_array->array[i]->getWord1(), simple_array->array[i]->getWord2()));
            stop = high_resolution_clock::now();
            microseconds unordered_array_init_duration = duration_cast<microseconds>(stop-start);
            // cout << "[+] added pairs to unordered array" << endl; // debug
            
            start = high_resolution_clock::now();
            for (long i=0; i<simple_array->next_free_slot; i++)
                ordered_array->insert(new Pair(simple_array->array[i]->getWord1(), simple_array->array[i]->getWord2()));
            stop = high_resolution_clock::now();
            microseconds ordered_array_init_duration = duration_cast<microseconds>(stop-start);
            // cout << "[+] added pairs to ordered array" << endl; // debug

            start = high_resolution_clock::now();
            for (long i=0; i<simple_array->next_free_slot; i++)
                bst = bst->insert(bst, new Pair(simple_array->array[i]->getWord1(), simple_array->array[i]->getWord2()));
            stop = high_resolution_clock::now();
            microseconds bst_init_duration = duration_cast<microseconds>(stop-start);
            // cout << "[+] added pairs to binary search tree" << endl; // debug

            start = high_resolution_clock::now();
            for (long i=0; i<simple_array->next_free_slot; i++)
                avl = avl->insert(avl, new Pair(simple_array->array[i]->getWord1(), simple_array->array[i]->getWord2()));
            stop = high_resolution_clock::now();
            microseconds avl_init_duration = duration_cast<microseconds>(stop-start);
            // cout << "[+] added pairs to avl tree" << endl; // debug

            start = high_resolution_clock::now();
            for (long i=0; i<simple_array->next_free_slot; i++)
                hashtable->insert(new Pair(simple_array->array[i]->getWord1(), simple_array->array[i]->getWord2()));
            stop = high_resolution_clock::now();
            microseconds hashtable_init_duration = duration_cast<microseconds>(stop-start);
            // cout << "[+] added pairs to hash table" << endl; // debug

            // select Q_SIZE random pairs

            srand(time(NULL));
            SimpleArray* Q = new SimpleArray(Q_SIZE);
            for (int i=0; i<Q_SIZE; i++)
                Q->insert(simple_array->array[rand()%simple_array->next_free_slot]);
            simple_array->~SimpleArray();
            // cout << "[*] selected " << Q_SIZE << " random pairs" << endl; // debug

            // search Q_SIZE random pairs in data structures

            // unordered array
            out_file << "\n\nUnordered array:\n----------------" << endl;
            start = high_resolution_clock::now();
            for (int i=0; i<Q_SIZE; i++) {
                long pos = unordered_array->search(Q->array[i]);
                out_file << *unordered_array->get_pair(pos) << endl;
            }
            stop = high_resolution_clock::now();
            out_file << "\nUnordered array initialization time -> " << unordered_array_init_duration.count()/1000000.0 << " seconds" << endl;
            microseconds unordered_array_search_duration = duration_cast<microseconds>(stop-start);
            out_file << "Unordered array search time -> " << unordered_array_search_duration.count()/1000000.0 << " seconds" << endl;
            unordered_array->~UnorderedArray();
            // cout << "[+] search random pairs in unordered array completed" << endl; // debug

            // ordered array
            out_file << "\n\nOrdered array:\n--------------" << endl;
            start = high_resolution_clock::now();
            for (int i=0; i<Q_SIZE; i++) {
                long pos = ordered_array->search(Q->array[i], 0, ordered_array->get_used_slots()-1);
                out_file << *ordered_array->get_pair(pos) << endl;
            }
            stop = high_resolution_clock::now();
            microseconds ordered_array_search_duration = duration_cast<microseconds>(stop-start);
            out_file << "\nOrdered array initialization time -> " << ordered_array_init_duration.count()/1000000.0 << " seconds" << endl;
            out_file << "Ordered array search time -> " << ordered_array_search_duration.count()/1000000.0 << " seconds" << endl;
            ordered_array->~OrderedArray();
            // cout << "[+] search random pairs in ordered array completed" << endl; // debug

            // binary search tree
            out_file << "\n\nBinary Search Tree:\n-------------------" << endl;
            start = high_resolution_clock::now();
            for (int i=0; i<Q_SIZE; i++) {
                BSTree* node = bst->search(bst, Q->array[i]);
                out_file << *bst->get_pair(node) << endl;
            }
            stop = high_resolution_clock::now();
            microseconds bst_search_duration = duration_cast<microseconds>(stop-start);
            out_file << "\nBinary Search Tree initialization time -> " << bst_init_duration.count()/1000000.0 << " seconds" << endl;
            out_file << "Binary Search Tree search time -> " << bst_search_duration.count()/1000000.0 << " seconds" << endl;
            bst = NULL;
            // cout << "[+] search random pairs in binary search tree completed" << endl; // debug

            // avl tree
            out_file << "\n\nAVL Tree:\n-----------" << endl;
            start = high_resolution_clock::now();
            for (int i=0; i<Q_SIZE; i++) {
                AVLTree* node = avl->search(avl, Q->array[i]);
                out_file << *avl->get_pair(node) << endl;
            }
            stop = high_resolution_clock::now();
            microseconds avl_search_duration = duration_cast<microseconds>(stop-start);
            out_file << "\nAVL Tree initialization time -> " << avl_init_duration.count()/1000000.0 << " seconds" << endl;
            out_file << "AVL Tree search time -> " << avl_search_duration.count()/1000000.0 << " seconds" << endl;
            avl = NULL;
            // cout << "[+] search random pairs in avl tree completed" << endl; // debug

            // hash table
            out_file << "\n\nHash Table:\n------------" << endl;
            start = high_resolution_clock::now();
            for (int i=0; i<Q_SIZE; i++) {
                long pos = hashtable->search(Q->array[i]);
                out_file << *hashtable->get_pair(pos) << endl;
            }
            stop = high_resolution_clock::now();
            microseconds hashtable_search_duration = duration_cast<microseconds>(stop-start);
            out_file << "\nHashTable initialization time -> " << hashtable_init_duration.count()/1000000.0 << " seconds" << endl;
            out_file << "HashTable search time -> " << hashtable_search_duration.count()/1000000.0 << " seconds" << endl;
            hashtable->~HashTable();
            // cout << "[+] search random pairs in hash table completed" << endl; // debug

            out_file << "\n\n";

            time_point<high_resolution_clock> total_stop = high_resolution_clock::now();
            microseconds total_duration = duration_cast<microseconds>(total_stop-total_start);
            out_file << "\n\nTotal time:\n------------" << endl;
            out_file << "Total time elapsed -> " << total_duration.count()/1000000.0 << " seconds" << endl;
            out_file.close();
            // cout << "[*] terminating successfully" << endl; // debug
        }
        else { cout << "[-] error: couldn't open file" << endl; }
    }
    else { cout << "[*] usage: " << argv[0] << " [filename]" << endl; }
    return 0;
}
#ifndef __TRIE_NODE__
#define __TRIE_NODE__

#include <unordered_map>
#include <vector>
#include <string>
#include "honeycomb_util.hpp"
using namespace std;

class trieNode {
public:
    bool isEndofWord;
    char val;
    unordered_map<char,trieNode*> leaf;

    trieNode(const char& charac) {
        val=charac;
        isEndofWord=false;
    }
    ~trieNode() {
        for (auto mpelem : leaf) {
            if (mpelem.second) mpelem.second->~trieNode();
        }
    }
};

void constructTrie(const char *dictionary_file, trieNode *pfakehead);
void printTrie(trieNode *pfakehead, vector<string>& res, string tmp);

void searchForWord(const int& start, HoneycombClass& honeycomb, trieNode *ptrienode, vector<string>& res, string currString);

#endif
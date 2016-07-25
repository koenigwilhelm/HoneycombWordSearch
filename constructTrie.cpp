#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "trienode.hpp"

using namespace std;

void constructTrie(const char *dictionary_file, trieNode *pfakehead) {
    ifstream dictfile(dictionary_file, ios::in);
    string tmp;
    while (getline(dictfile,tmp)) {
        int wlngth=tmp.length();
        trieNode *ptr=pfakehead;
        for (int ix=0; ix<wlngth; ix++) {
            char charac=tmp[ix];
            if (ptr->leaf.find(charac)==ptr->leaf.end()) {
                ptr->leaf[charac]=new trieNode(charac);
            }
            ptr=ptr->leaf[charac];
            ptr->val=charac;
        }
        ptr->isEndofWord=true;
        //cout << tmp << ptr->val << endl;
    }
}

void printTrie(trieNode *pfakehead, vector<string>& res, string tmp) {
    trieNode *ptr=pfakehead;
    tmp=tmp+ptr->val;
    //cout << tmp << endl;
    if (ptr->isEndofWord) res.push_back(tmp);
    for (auto ix : ptr->leaf) {
        printTrie(ix.second, res, tmp);
    }
    return;
}
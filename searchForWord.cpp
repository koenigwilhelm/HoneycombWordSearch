#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "honeycomb_util.hpp"
#include "trienode.hpp"
using namespace std;

void searchForWord(const int& start, HoneycombClass& honeycomb, trieNode *ptrienode, vector<string>& res, string currString) {
    int totalNcells=honeycomb.visited.size();
    if (start<0 || start>=totalNcells || honeycomb.visited[start]) return;

    trieNode *ptr=ptrienode, *nexttrienode;
    char characCell=honeycomb.honeycombstr[start];
    if (ptr->leaf.find(characCell) == ptr->leaf.end()) return;
    nexttrienode=(ptr->leaf)[characCell];
    honeycomb.visited[start]=true;

    string newString=currString+characCell;
    if (nexttrienode->isEndofWord) {
        if ( find(res.begin(),res.end(),newString) == res.end() ) res.push_back(newString);
    }

    for (int ix=0; ix<6; ix++) {
        searchForWord(honeycomb.neighbors[start][ix], honeycomb, nexttrienode, res, newString);
    }
    honeycomb.visited[start]=false;
    return;
}
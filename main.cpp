#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "honeycomb_util.hpp"
#include "trienode.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc<3) {
        cerr << "Please make sure to provide 2 input files" << endl;
    }
    HoneycombClass honeycomb(argv[1]);

    /* verifying honeycomb structure
    cout << honeycomb.honeycombstr[21] << "-----" << endl;
    for (int ix=0; ix<6; ix++) {
        cout << honeycomb.honeycombstr[honeycomb.neighbors[21][ix]] << endl;
    }*/

    trieNode fakehead('#');
    constructTrie(argv[2],&fakehead);

    /* verifying trie structure
    vector<string> tst;
    printTrie(&fakehead, tst, "");
    for (auto ix : tst) {
        cout << ix << endl;
    }*/

    vector<string> res;
    int totalNcells=honeycomb.visited.size();
    for (int ix=0; ix<totalNcells; ix++) {
        searchForWord(ix,honeycomb,&fakehead,res,"");
    }

    //cout << res.size() << endl;
    sort(res.begin(), res.end());
    for (auto ix : res) {
        cout << ix << endl;
    }

    return 0;
}
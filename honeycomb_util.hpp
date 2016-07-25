#ifndef __HONEYCOMB_UTIL__
#define __HONEYCOMB_UTIL__

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

class HoneycombClass {
private:
    HoneycombClass() {};
    int globalnumber(const int& layer, const int& norder, const vector<int>& startpos) {
        return startpos[layer]+norder;
    }
public:
    string honeycombstr;
    vector<vector<int>> neighbors;
    vector<bool> visited;

    HoneycombClass(const char *honeycomb_file) {
        ifstream honeyinfile(honeycomb_file, ios::in);
        string tmp;
        getline(honeyinfile,tmp);
        int nlayers=atoi(tmp.c_str());

        vector<unsigned int> nElemInLayer(nlayers,1);
        //vector<int> edgelength(nlayers,1)
        for (int ix=1; ix<nlayers; ix++) nElemInLayer[ix]=6*ix;
        vector<int> startpos(nlayers,0);
        for (int ix=1; ix<=nlayers; ix++) startpos[ix]=startpos[ix-1]+nElemInLayer[ix-1];

        int ix=0;
        honeycombstr="";
        while (getline(honeyinfile,tmp)) {
            if (tmp.length()!=nElemInLayer[ix++]) cerr << "Errors in Honeycomb File!" << endl;
            honeycombstr+=tmp;
        }

        visited=vector<bool>(honeycombstr.length(),false);

        neighbors=vector<vector<int>>(honeycombstr.length(),vector<int>(6,-1));
        if (nlayers>1) {
            neighbors[0]={1,2,3,4,5,6};
        }
        for (int ix=1; ix<nlayers; ix++) {
            for (unsigned int jx=0; jx<nElemInLayer[ix]; jx++) {
                // global number = startpos[ix]+jx
                // neighbors in same layer
                neighbors[globalnumber(ix,jx,startpos)][0]=globalnumber(ix,(jx-1)%nElemInLayer[ix],startpos);
                neighbors[globalnumber(ix,jx,startpos)][1]=globalnumber(ix,(jx+1)%nElemInLayer[ix],startpos);
                if (jx%ix) { // NOT ON 6 CORNERS: 2 neighbors on inner and outer layers respectively
                    // neighbors on inner layer
                    neighbors[globalnumber(ix,jx,startpos)][2]=globalnumber(ix-1,((jx/ix)*(ix-1)+jx%ix-1)%nElemInLayer[ix-1],startpos);
                    neighbors[globalnumber(ix,jx,startpos)][3]=globalnumber(ix-1,((jx/ix)*(ix-1)+jx%ix)%nElemInLayer[ix-1],startpos);
                    if (ix<nlayers-1) {
                        // neighbors on outer layer
                        neighbors[globalnumber(ix,jx,startpos)][4]=globalnumber(ix+1,((jx/ix)*(ix+1)+jx%ix)%nElemInLayer[ix+1],startpos);
                        neighbors[globalnumber(ix,jx,startpos)][5]=globalnumber(ix+1,((jx/ix)*(ix+1)+jx%ix+1)%nElemInLayer[ix+1],startpos);
                    }
                }
                else { // ON 6 CORNERS: 1 neighbor on inner layer, 3 neighbors on outer layer
                    // neighbors on inner layer
                    neighbors[globalnumber(ix,jx,startpos)][2]=globalnumber(ix-1,(jx/ix)*(ix-1),startpos);
                    if (ix<nlayers-1) {
                        // neighbors on outer layer
                        neighbors[globalnumber(ix,jx,startpos)][3]=globalnumber(ix+1,(jx/ix)*(ix+1),startpos);
                        neighbors[globalnumber(ix,jx,startpos)][4]=globalnumber(ix+1,((jx/ix)*(ix+1)-1)%nElemInLayer[ix+1],startpos);
                        neighbors[globalnumber(ix,jx,startpos)][5]=globalnumber(ix+1,((jx/ix)*(ix+1)+1)%nElemInLayer[ix+1],startpos);
                    }
                }
            }
        }
    }
};

#endif
#include "Solution.h"

void Solution::Drop(int i) {

    phi[sol1[i]] = 2;

    sol2.emplace_back(sol1[i]);
    sol1.erase(sol1.begin() + i);

}

int Solution::EvaluateDrop(int i1) {

    int v1 = sol1[i1];

    int obj1aux = obj1 - Si[v1].size();
    int obj2aux = obj2 + So[v1].size();

    int objaux;
    if(obj1aux<obj2aux) objaux = obj1aux;
    else                objaux = obj2aux;

    return objaux - obj;
}

bool Solution::ExploreDropInc(int strategy) {

    bool improved = false;

    int  i1best;

    vecInt veci1;
    for(int i1=0; i1<sol1.size(); i1++) veci1.emplace_back(i1); rndShuffle(veci1);

    int hbest = 0;
    for(int& i1: veci1) {
        int h = EvaluateDrop(i1);
        if(h>hbest) {
            i1best   = i1;
            hbest    = h;
            improved = true;
        }
        if(improved && strategy<2) break;
    }

    if(improved) {
        int v1 = sol1[i1best];
        obj += hbest;
        obj1 = obj1 - Si[v1].size();
        obj2 = obj2 + So[v1].size();
        Drop(i1best);
        DataUpdate(v1);
    }

    return improved;
}


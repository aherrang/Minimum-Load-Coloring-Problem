#include "Solution.h"

void Solution::Add(int i) {

    phi[sol2[i]] = 1;

    sol1.emplace_back(sol2[i]);
    sol2.erase(sol2.begin() + i);

}

int Solution::EvaluateAdd(int i2) {

    int v2 = sol2[i2];

    int obj1aux = obj1 + So[v2].size();
    int obj2aux = obj2 - Si[v2].size();

    int objaux;
    if(obj1aux<obj2aux) objaux = obj1aux;
    else                objaux = obj2aux;

    return objaux - obj;
}

bool Solution::ExploreAddInc(int strategy) {

    bool improved = false;

    int  i2best;

    vecInt veci2;
    for(int i2=0; i2<sol2.size(); i2++) veci2.emplace_back(i2); rndShuffle(veci2);

    int hbest = 0;
    for(int& i2: veci2) {
        int h = EvaluateAdd(i2);
        if(h>hbest) {
            i2best   = i2;
            hbest    = h;
            improved = true;
        }
        if(improved && strategy<2) break;
    }

    if(improved) {
        int v2 = sol2[i2best];
        obj += hbest;
        obj1 = obj1 + So[v2].size();
        obj2 = obj2 - Si[v2].size();
        Add(i2best);
        DataUpdate(v2);
    }

    return improved;
}

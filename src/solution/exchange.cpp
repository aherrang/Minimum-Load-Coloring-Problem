#include "Solution.h"

void Solution::Exchange(int i1, int i2) {

 // Update colors
    phi[sol1[i1]] = 2;
    phi[sol2[i2]] = 1;

 // Exchange vertex
    int temp = sol1[i1];
    sol1[i1] = sol2[i2];
    sol2[i2] = temp;

}

int Solution::EvaluateExchange(int i1, int i2) {

    int v1 = sol1[i1];
    int v2 = sol2[i2];

    int obj1aux = obj1 - Si[v1].size() + So[v2].size() - data.W[v1][v2];
    int obj2aux = obj2 - Si[v2].size() + So[v1].size() - data.W[v1][v2];

    int objaux;
    if(obj1aux<obj2aux) objaux = obj1aux;
    else                objaux = obj2aux;

    return objaux - obj;
}

bool Solution::ExploreExchange(int strategy) {

    bool improved = false;

    int  i1best;
    int  i2best;

    vecInt veci1, veci2;
    for(int i1=0; i1<sol1.size(); i1++) veci1.emplace_back(i1); rndShuffle(veci1);
    for(int i2=0; i2<sol2.size(); i2++) veci2.emplace_back(i2); rndShuffle(veci2);

    int hbest = 0;
    for(int& i1: veci1) {
        for(int& i2: veci2) {
            Exchange(i1,i2);
            DataUpdate(sol1[i1]);
            DataUpdate(sol2[i2]);
            int h = EvaluateMove();
            Exchange(i1,i2);
            DataUpdate(sol1[i1]);
            DataUpdate(sol2[i2]);
            if(h>hbest) {
                i1best   = i1;
                i2best   = i2;
                hbest    = h;
                improved = true;
            }
            if(improved && strategy<1) break;
        }
        if(improved && strategy<2) break;
    }

    if(improved) {
        obj += hbest;
        Exchange(i1best,i2best);
        DataUpdate(sol1[i1best]);
        DataUpdate(sol2[i2best]);
    }

    return improved;
}

bool Solution::ExploreExchangeInc(int strategy) {

    bool improved = false;

    int  i1best;
    int  i2best;

    vecInt veci1, veci2;
    for(int i1=0; i1<sol1.size(); i1++) veci1.emplace_back(i1); rndShuffle(veci1);
    for(int i2=0; i2<sol2.size(); i2++) veci2.emplace_back(i2); rndShuffle(veci2);

    int hbest = 0;
    for(int& i1: veci1) {
        for(int& i2: veci2) {
            int h = EvaluateExchange(i1, i2);
            if(h>hbest) {
                i1best   = i1;
                i2best   = i2;
                hbest    = h;
                improved = true;
            }
            if(improved && strategy<1) break;
        }
        if(improved && strategy<2) break;
    }

    if(improved) {
        int v1 = sol1[i1best];
        int v2 = sol2[i2best];
        obj += hbest;
        obj1 = obj1 - Si[v1].size() + So[v2].size() - data.W[v1][v2];
        obj2 = obj2 - Si[v2].size() + So[v1].size() - data.W[v1][v2];
        Exchange(i1best,i2best);
        DataUpdate(v1);
        DataUpdate(v2);
    }

    return improved;
}

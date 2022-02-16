#include "Solution.h"

void Solution::Shake1(int ks) {

    vecInt vi1, vi2;
    for(int i1=0; i1<sol1.size(); i1++) vi1.emplace_back(i1);
    for(int i2=0; i2<sol2.size(); i2++) vi2.emplace_back(i2);
    rndShuffle(vi1);
    rndShuffle(vi2);
    for(int k=0; k<ks; k++) {
        int i1 = vi1[k];
        int i2 = vi2[k];
        int v1 = sol1[i1];
        int v2 = sol2[i2];
        obj += EvaluateExchange(i1, i2);
        obj1 = obj1 - Si[v1].size() + So[v2].size() - data.W[v1][v2];
        obj2 = obj2 - Si[v2].size() + So[v1].size() - data.W[v1][v2];
        Exchange(i1,i2);
        DataUpdate(v1);
        DataUpdate(v2);
    }

}

void Solution::Shake2(int ks) {

    for(int k=0; k<ks; k++) {
        int i1 = rndInt(0,sol1.size()-1);
        int v1 = sol1[i1];
        obj += EvaluateDrop(i1);
        obj1 = obj1 - Si[v1].size();
        obj2 = obj2 + So[v1].size();
        Drop(i1);
        DataUpdate(v1);
    }

}

void Solution::Shake3(int ks) {

    for(int k=0; k<ks; k++) {
        int i2 = rndInt(0,sol2.size()-1);
        int v2 = sol2[i2];
        obj += EvaluateAdd(i2);
        obj1 = obj1 + So[v2].size();
        obj2 = obj2 - Si[v2].size();
        Add(i2);
        DataUpdate(v2);
    }

}

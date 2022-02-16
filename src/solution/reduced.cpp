#include "Solution.h"

bool Solution::ExploreExchangeRedu1(int k) {

    bool improved = false;

    int  i1best;
    int  i2best;

    vecInt sol1_aux = sol1;
    vecInt sol2_aux = sol2;
    int    obj_aux  = obj;
    int    obj1_aux = obj1;
    int    obj2_aux = obj2;
    matInt Si_aux   = Si;
    matInt So_aux   = So;

    rndShuffle(sol1);
    for(int p=0; p<k; p++) {
        int hbest = std::numeric_limits<int>::min();
        for(int i1=0; i1<sol1.size(); i1++) {
            int h = EvaluateDrop(i1);
            if(h<hbest) {
                i1best = i1;
                hbest  = h;
            }
        }
        obj += hbest;
        int v1 = sol1[i1best];
        obj1 = obj1 - Si[v1].size();
        obj2 = obj2 + So[v1].size();
        Drop(i1best);
        DataUpdate(v1);
    }

    rndShuffle(sol2);
    for(int p=0; p<k; p++) {
        int hbest = std::numeric_limits<int>::min();
        for(int i2=0; i2<sol2.size(); i2++) {
            int h = EvaluateAdd(i2);
            if(h<hbest) {
                i2best = i2;
                hbest  = h;
            }
        }
        obj += hbest;
        int v2 = sol2[i2best];
        obj1 = obj1 + So[v2].size();
        obj2 = obj2 - Si[v2].size();
        Add(i2best);
        DataUpdate(v2);
    }

    if(obj>obj_aux) {
        improved = true;
    }
    else {
        sol1 = sol1_aux;
        sol2 = sol2_aux;
        obj  = obj_aux;
        obj1 = obj1_aux;
        obj2 = obj2_aux;
        Si   = Si_aux;
        So   = So_aux;
    }

    return improved;
}

bool Solution::ExploreExchangeRedu2(int k) {

    bool improved = false;

    int  i1best;
    int  i2best;

    vecInt sol1_aux = sol1;
    vecInt sol2_aux = sol2;
    int    obj_aux  = obj;
    int    obj1_aux = obj1;
    int    obj2_aux = obj2;
    matInt Si_aux   = Si;
    matInt So_aux   = So;

    rndShuffle(sol2);
    for(int p=0; p<k; p++) {
        int hbest = std::numeric_limits<int>::min();
        for(int i2=0; i2<sol2.size(); i2++) {
            int h = EvaluateAdd(i2);
            if(h>hbest) {
                i2best = i2;
                hbest  = h;
            }
        }
        obj += hbest;
        int v2 = sol2[i2best];
        obj1 = obj1 + So[v2].size();
        obj2 = obj2 - Si[v2].size();
        Add(i2best);
        DataUpdate(v2);
    }

    rndShuffle(sol1);
    for(int p=0; p<k; p++) {
        int hbest = std::numeric_limits<int>::min();
        for(int i1=0; i1<sol1.size(); i1++) {
            int h = EvaluateDrop(i1);
            if(h>hbest) {
                i1best = i1;
                hbest  = h;
            }
        }
        obj += hbest;
        int v1 = sol1[i1best];
        obj1 = obj1 - Si[v1].size();
        obj2 = obj2 + So[v1].size();
        Drop(i1best);
        DataUpdate(v1);
    }

    if(obj>obj_aux) {
        improved = true;
    }
    else {
        sol1 = sol1_aux;
        sol2 = sol2_aux;
        obj  = obj_aux;
        obj1 = obj1_aux;
        obj2 = obj2_aux;
        Si   = Si_aux;
        So   = So_aux;
    }

    return improved;
}

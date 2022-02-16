#include "Solution.h"

//******************************************************************************
// ConstructiveGreedy procedures
//******************************************************************************

void Solution::ConstructiveRandom() {

// // Generates a random ordering of vertex in Vb
//    phi = vecInt(data.nV,2);
//    sol1.clear();
//    sol2.clear();
//    for(int i=0; i<data.nV; i++) sol2.emplace_back(i);
//    rndShuffle(sol2);
//
// // Removes n/2 vertices from Vb and adds them to Vr
//    for(int i=0; i<data.nV/2; i++) Add(static_cast<int>(sol2.size()) - 1);
//    DataInit();
//    Evaluate();

    phi = vecInt(data.nV,0);
    sol1.clear();
    sol2.clear();
    for(int i=0; i<data.nV; i++) {
        int c = rndInt(1,2);
        if(c==1) sol1.emplace_back(i);
        else     sol2.emplace_back(i);
        phi[i] = c;
    }
    rndShuffle(sol1);
    rndShuffle(sol2);
    DataInit();
    Evaluate();

}


void Solution::ConstructiveGreedy(int constructive, double alpha) {

 // Generates a random ordering of vertex in Vb
    phi = vecInt(data.nV,2);
    sol1.clear();
    sol2.clear();
    for(int i=0; i<data.nV; i++) sol2.emplace_back(i);
    rndShuffle(sol2);

 // Adds one vertex from Vb to Vr at random
    for(int i=0; i<data.nV/5; i++) Add(static_cast<int>(sol2.size()) - 1);
    DataInit();
    Evaluate();

 // Removes vertices from Vb and adds them to Vr while obj1<obj2
    vecInt CL;
    for(int& v: sol2) CL.emplace_back(v);
    int c, v, objaux, obj1aux, obj2aux;
    while(!CL.empty()) {
        rndShuffle(CL);
        if(alpha==0.01) alpha = rndDbl(0.0,1.0);
        if     (constructive==0) c = static_cast<int>(CL.size()) - 1; //Random
        else if(constructive==1) c = getGreedy1(CL,alpha); //G-R
        else                     c = getGreedy2(CL,alpha); //R-G
        v = CL[c];
        CL.erase(CL.begin() + c);
        obj1aux = obj1 + static_cast<int>(So[v].size());
        obj2aux = obj2 - static_cast<int>(Si[v].size());
        if(obj1aux<obj2aux) objaux = obj1aux;
        else                objaux = obj2aux;
        if(objaux>obj) {
            vecInt::iterator it = find(sol2.begin(),sol2.end(),v);
            Add(it - sol2.begin());
            DataUpdate(v);
            obj  = objaux;
            obj1 = obj1aux;
            obj2 = obj2aux;
        }
    }

}

int Solution::getGreedy1(vecInt &CL, double alpha) {

    int candidate;

    int gmin = std::numeric_limits<int>::max();
    int gmax = std::numeric_limits<int>::min();

    vecInt g = vecInt(CL.size(), 0);
    for(int c=0; c < CL.size(); c++) {
        g[c] = static_cast<int>(So[CL[c]].size()) - static_cast<int>(Si[CL[c]].size());
        if(g[c]<gmin) gmin = g[c];
        if(g[c]>gmax) gmax = g[c];
    }
    double th = gmin + alpha*(gmax-gmin);
    for(int c=0; c < CL.size(); c++) if (g[c] >= th) { candidate = c; break; }

    return candidate;
}

int Solution::getGreedy2(vecInt &CL, double alpha){

    int candidate;

    int s    = (int)floor(alpha * static_cast<int>(CL.size())); if(s == 0) s = 1;
    int gmax = std::numeric_limits<int>::min();

    int g;
    for(int c=0; c<s; c++) {
        g = static_cast<int>(So[CL[c]].size()) - static_cast<int>(Si[CL[c]].size());
        if(g>gmax) {
            gmax      = g;
            candidate = c;
        }
    }

    return candidate;
}

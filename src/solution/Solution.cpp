/* 
 * File:   Source file for class Solution
 * Author: A. Herrán
 */

#include "Solution.h"

//------------------------
// Constructor/destructor
//------------------------
Solution::Solution() {

    obj  = 0;
    obj1 = 0;
    obj2 = 0;

}

Solution::Solution(const Solution &orig) {

    sol1 = orig.sol1;
    sol2 = orig.sol2;

    phi  = orig.phi;

    Si   = orig.Si;
    So   = orig.So;

    obj  = orig.obj;
    obj1 = orig.obj1;
    obj2 = orig.obj2;

}

Solution::~Solution() = default;

//******************************************************************************
// Construct Operators: Random, GreedyRandom, RandomGreedy
//******************************************************************************
void Solution::Construct() {

 // Constructs a new solution
    if     (data.MC=="random" ) ConstructiveRandom();
    else if(data.MC=="greedy1") ConstructiveGreedy(1, data.AG);
    else if(data.MC=="greedy2") ConstructiveGreedy(2, data.AG);
    else {
        cout << "\n Wrong construction method (x).";
        cin.get();
    }

}

//******************************************************************************
// Eval Operators: Full solution and full generic move
//******************************************************************************

void Solution::Evaluate() {

    obj1 = 0;
    obj2 = 0;

    for(auto &u: sol1) obj1 += static_cast<int>(Si[u].size()); obj1 /= 2;
    for(auto &u: sol2) obj2 += static_cast<int>(Si[u].size()); obj2 /= 2;

    if(obj1<obj2) obj = obj1;
    else          obj = obj2;

}

int Solution::EvaluateMove() {

    int obj1aux = 0;
    int obj2aux = 0;

    for(auto &u: sol1)  obj1aux += static_cast<int>(Si[u].size()); obj1aux /= 2;
    for(auto &u: sol2)  obj2aux += static_cast<int>(Si[u].size()); obj2aux /= 2;

    int objaux;
    if(obj1aux<obj2aux) objaux = obj1aux;
    else                objaux = obj2aux;

    return objaux - obj;
}

//------------------------------------------------------------------
// Initializes data structures needed for an incremental evaluation
//------------------------------------------------------------------
void Solution::DataInit() {

    vecInt vec;
    Si = matInt(data.nV,vec);
    So = matInt(data.nV,vec);

    for(int u: sol1) {
        for(int& up: sol1) if(data.W[u][up]) Si[u].emplace_back(up);
        for(int& vp: sol2) if(data.W[u][vp]) So[u].emplace_back(vp);
    }
    for(auto v: sol2) {
        for(int& vp: sol2) if(data.W[v][vp]) Si[v].emplace_back(vp);
        for(int& up: sol1) if(data.W[v][up]) So[v].emplace_back(up);
    }

}

void Solution::DataUpdate(int v) {

 // Update Si and So for all the in-adjacent to v
    for(auto &u: Si[v]) {
        So[u].emplace_back(v);
        vecInt::iterator j = find(Si[u].begin(),Si[u].end(),v);
        Si[u].erase(j);
    }

 // Update Si and So for all the out-adjacent to v
    for(auto &u: So[v]) {
        Si[u].emplace_back(v);
        vecInt::iterator j = find(So[u].begin(),So[u].end(),v);
        So[u].erase(j);
    }

 // Update Si and So for v
    vecInt vaux = Si[v];
    Si[v] = So[v];
    So[v] = vaux;

}

//******************************************************************************
// Neighborhood exploration strategies
//******************************************************************************

bool Solution::Explore(const string& ME, int k) {

    bool improved;

    if     (ME=="exc_b" ) improved = ExploreExchange(2);
    else if(ME=="exc_h" ) improved = ExploreExchange(1);
    else if(ME=="exc_f" ) improved = ExploreExchange(0);
    else if(ME=="exc_bi") improved = ExploreExchangeInc(2);
    else if(ME=="exc_hi") improved = ExploreExchangeInc(1);
    else if(ME=="exc_fi") improved = ExploreExchangeInc(0);
    else if(ME=="dro_bi") improved = ExploreDropInc(2);
    else if(ME=="dro_fi") improved = ExploreDropInc(0);
    else if(ME=="add_bi") improved = ExploreAddInc(2);
    else if(ME=="add_fi") improved = ExploreAddInc(0);
    else if(ME=="ext_bi") improved = ExploreExtendedBestInc();
    else {
        cout << "\n Wrong neighborhood exploration method.";
        cin.get();
    }

    return improved;
}

//******************************************************************************
// Shake Operators for VNS (Basic or General): Shake 1, 2, 3
//******************************************************************************

void Solution::Shake(int ks) {

    //data.SK = rndInt(1,3);
    if     (data.SK == 1) Shake1(ks); // Exchange
    else if(data.SK == 2) Shake2(ks); // Drop
    else if(data.SK == 3) Shake3(ks); // Add

    else {
        cout << "\n Wrong Shake method.";
        cin.get();
    }

}

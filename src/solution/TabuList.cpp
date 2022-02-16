#include <climits>
/*
 * File:   Source file for class Algorithm TabuList
 * Author: A. Herrán
 */

#include "TabuList.h"

//------------------------
// Constructor/destructor
//------------------------
TabuList::TabuList() {

    tabulist.clear();
    
}

TabuList::TabuList(const TabuList& orig) { }
TabuList::~TabuList() = default;

//----------------------------------
// Adds a solution to the tabu list
//----------------------------------
void TabuList::Add(vecInt &sol) {

    if(data.NT>0) {
        string strSol = ToString(sol);
        tabulist.push_back(strSol);
        if(tabulist.size()>data.NT) tabulist.pop_back();
    }
    
}

//------------------------------------------
// Checks if a solution is in the tabu list
//------------------------------------------
bool TabuList::Check(vecInt &sol) {
    
    bool isTabu = false;

    if(data.NT>0) {
        string strSol = ToString(sol);
        for(auto &s: tabulist) {
            if(strSol==s) {
                isTabu = true;
                break;
            }
        }
    }

    return isTabu;    
}

//----------------------------------------------
// Gets the string representation of a solution
//----------------------------------------------
string TabuList::ToString(vecInt sol) {

    sort(sol.begin(),sol.end());
    string strSol;
    for(int u: sol) strSol += to_string(u)+"-";

    return strSol;
}

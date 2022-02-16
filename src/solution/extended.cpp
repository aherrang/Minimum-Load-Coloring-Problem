#include "Solution.h"

bool Solution::ExploreExtendedBestInc() {

    bool improved = false;

    int  i1best_exc;
    int  i2best_exc;
    int  i1best_dro;
    int  i2best_add;

 // Exchange moves
    int hbest_exc = 0;
    for(int i1=0; i1<sol1.size(); i1++) {
        for(int i2=0; i2<sol2.size(); i2++) {
            int h = EvaluateExchange(i1, i2);
            if(h>hbest_exc || ((h==hbest_exc)&&(h>0)&&(rndInt(0,1)))) {
                i1best_exc = i1;
                i2best_exc = i2;
                hbest_exc  = h;
                improved   = true;
            }
        }
    }

 // Drop moves
    improved = false;
    int hbest_dro = 0;
    for(int i1=0; i1<sol1.size(); i1++) {
        int h = EvaluateDrop(i1);
        if(h>hbest_dro || ((h==hbest_dro)&&(h>0)&&(rndInt(0,1)))) {
            i1best_dro = i1;
            hbest_dro  = h;
            improved   = true;
        }
    }

 // Add moves
    improved = false;
    int hbest_add = 0;
    for(int i2=0; i2<sol2.size(); i2++) {
        int h = EvaluateAdd(i2);
        if(h>hbest_add || ((h==hbest_add)&&(h>0)&&(rndInt(0,1)))) {
            i2best_add = i2;
            hbest_add  = h;
            improved   = true;
        }
    }

 // Checks the extended move
    int move=1;
    if(hbest_exc>hbest_dro) {
        if(hbest_exc>hbest_add) move = 1;
        else                    move = 3;
    }
    else {
        if(hbest_dro>hbest_add) move = 2;
        else                    move = 3;
    }
    improved = false;
    if(move==1) {
        if (hbest_exc > 0) {
            improved = true;
            int v1 = sol1[i1best_exc];
            int v2 = sol2[i2best_exc];
            obj += hbest_exc;
            obj1 = obj1 - Si[v1].size() + So[v2].size() - data.W[v1][v2];
            obj2 = obj2 - Si[v2].size() + So[v1].size() - data.W[v1][v2];
            Exchange(i1best_exc, i2best_exc);
            DataUpdate(v1);
            DataUpdate(v2);
        }
    }
    else if(move==2) {
        if (hbest_dro > 0) {
            improved = true;
            int v1 = sol1[i1best_dro];
            obj += hbest_dro;
            obj1 = obj1 - Si[v1].size();
            obj2 = obj2 + So[v1].size();
            Drop(i1best_dro);
            DataUpdate(v1);
        }
    }
    else {
        if(hbest_add>0) {
            improved = true;
            int v2 = sol2[i2best_add];
            obj += hbest_add;
            obj1 = obj1 + So[v2].size();
            obj2 = obj2 - Si[v2].size();
            Add(i2best_add);
            DataUpdate(v2);
        }
    }

    return improved;
}

/* 
 * File:   Source file for class BVNS
 * Author: A. Herrán
 */

#include "BVNS.h"

//------------------------
// Constructor/destructor
//------------------------
BVNS::BVNS(): Metaheuristic() {

 // Sets kmax for the Shake procedure
    kmax = static_cast<int>(data.BT * data.nV / 2);
    
}

BVNS::~BVNS() = default;

//----------------------------------------------
// Performs one iteration of the meta-heuristic
//----------------------------------------------
bool BVNS::Iterate() {

    if(data.MU==1) {
        Construct();
        k = 0;
    }

    while(k<=kmax) {

     // Shake to a non-tabu neighbor
        if(k>0) {
            do {
                solutiona = solutione;
                solutiona.Shake(k);
            } while (tabulist.Check(solutiona.sol1));
        }

     // Local Search
        while(solutiona.Explore(data.ME,1)) continue;

     // Update incumbent solution
        if(solutiona<solutione) {
            solutione = solutiona;
            tabulist.Add(solutiona.sol1);
            k = 1;
        }
        else k++;

    }

    k = 1;

    return true;
}


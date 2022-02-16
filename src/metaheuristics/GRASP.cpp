/* 
 * File:   Source file for class GRASP
 * Author: A. Herrán
 */

#include "../metaheuristics/GRASP.h"

//------------------------
// Constructor/destructor
//------------------------
GRASP::GRASP(): Metaheuristic() { }

GRASP::~GRASP() = default;

//----------------------------------------------
// Performs one iteration of the meta-heuristic
//----------------------------------------------
bool GRASP::Iterate() {

 // Construct
    if(k>0) {
        Tengine &engine = vengine[omp_get_thread_num()];
        engine.seed(k);
        Construct();
    }
    k++;

 // Local Search
    while(solutiona.Explore(data.ME,1)) continue;

 // Update incumbent solution
    //if(solutiona<solutione) solutione = solutiona;
    solutione = solutiona;

    return true;
}

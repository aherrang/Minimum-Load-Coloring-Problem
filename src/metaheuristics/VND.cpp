/* 
 * File:   Source file for class VND
 * Author: A. Herrán
 */

#include "VND.h"

//------------------------
// Constructor/destructor
//------------------------
VND::VND(): Metaheuristic() {

 // Sequence of neighborhoods for different VND versions
    switch(data.VD) {

        case 0: Sn.emplace_back(data.ME); break;

        case 1: Sn.emplace_back(data.ME);  Sn.emplace_back("add_bi"); Sn.emplace_back("dro_bi"); break;
        case 2: Sn.emplace_back(data.ME);  Sn.emplace_back("dro_bi"); Sn.emplace_back("add_bi"); break;

        case 3: Sn.emplace_back("add_bi"); Sn.emplace_back(data.ME);  Sn.emplace_back("dro_bi"); break;
        case 4: Sn.emplace_back("dro_bi"); Sn.emplace_back(data.ME);  Sn.emplace_back("add_bi"); break;

        case 5: Sn.emplace_back("add_bi"); Sn.emplace_back("dro_bi"); Sn.emplace_back(data.ME);  break;
        case 6: Sn.emplace_back("dro_bi"); Sn.emplace_back("add_bi"); Sn.emplace_back(data.ME);  break;

//        case 1: Sn.emplace_back(data.ME);  Sn.emplace_back("add_fi"); Sn.emplace_back("dro_fi"); break;
//        case 2: Sn.emplace_back(data.ME);  Sn.emplace_back("dro_fi"); Sn.emplace_back("add_fi"); break;
//
//        case 3: Sn.emplace_back("add_fi"); Sn.emplace_back(data.ME);  Sn.emplace_back("dro_fi"); break;
//        case 4: Sn.emplace_back("dro_fi"); Sn.emplace_back(data.ME);  Sn.emplace_back("add_fi"); break;
//
//        case 5: Sn.emplace_back("add_fi"); Sn.emplace_back("dro_fi"); Sn.emplace_back(data.ME);  break;
//        case 6: Sn.emplace_back("dro_fi"); Sn.emplace_back("add_fi"); Sn.emplace_back(data.ME);  break;

        default:
            cout << "\n Wrong VND version.";
            cin.get();

    }

}

VND::~VND() = default;

//----------------------------------------------
// Performs one iteration of the meta-heuristic
//----------------------------------------------
bool VND::Iterate() {

 // Construct
    if(k>0) {
        Tengine &engine = vengine[omp_get_thread_num()];
        engine.seed(k);
        Construct();
    }
    k++;

 // VND
    int kp = 0;
    while(kp<Sn.size()) {
        if(solutiona.Explore(Sn[kp],1)) kp = -1;
        //while(solutiona.Explore(Sn[kp],1)) kp = 0;
        kp++;
    }
 // Update incumbent solution
    //if(solutiona<solutione) solutione = solutiona;
    solutione = solutiona;

    return true;
}

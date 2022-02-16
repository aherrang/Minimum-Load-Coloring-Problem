/* 
 * File:   Source file for class GVNS
 * Author: A. Herrán
 */

#include "GVNS.h"

//------------------------
// Constructor/destructor
//------------------------
GVNS::GVNS(): Metaheuristic() {

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
    
 // Sets kmax for the Shake procedure
    kmax = static_cast<int>(data.BT * data.nV / 2);

}

GVNS::~GVNS() = default;

//----------------------------------------------
// Performs one iteration of the meta-heuristic
//----------------------------------------------
bool GVNS::Iterate() {

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

     // VND
        int kp = 0;
        while(kp<Sn.size()) {
            if(solutiona.Explore(Sn[kp],1)) kp = -1;
            //while(solutiona.Explore(Sn[kp],1)) kp = 0;
            kp++;
        }

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

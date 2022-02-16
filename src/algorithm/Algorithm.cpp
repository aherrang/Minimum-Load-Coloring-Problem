/* 
 * File:   Source file for class Algorithm
 * Author: A. Herrán
 */

#include "Algorithm.h"

//------------------------
// Constructor/destructor
//------------------------
Algorithm::Algorithm(const string& pathInstance, int ne) {
       
    islands = new Island *[data.NI];
    for(int i=0; i<data.NI; i++) islands[i] = new Island();
    
    vector<string> tokens = split(pathInstance+"/","/");   
    tokens = split(tokens.back(),".");
    string instance = tokens[0];
    
    fileEvol.open("logs/evol_"+instance+"_"+to_string(ne)+".txt");
    if(!fileEvol) {
        cout << "\n The fileEvol file can not be opened.";
        exit(1);
    }
  
    fileCost.open("logs/cost_"+instance+"_"+to_string(ne)+".txt");
    if(!fileEvol) {
        cout << "\n The fileCost file can not be opened.";
        exit(1);
    }
        
    fileSolu.open("logs/solu_"+instance+"_"+to_string(ne)+".txt");
    if(!fileEvol) {
        cout << "\n The fileSolu file can not be opened.";
        exit(1);
    }
    
}

//Algorithm::Algorithm(const Algorithm &orig) { }

Algorithm::~Algorithm() {
    
    for(int i=0; i<data.NI; i++) delete islands[i];
    delete[] islands;
    
    fileEvol.close();
    fileCost.close();
    fileSolu.close();

}

//---------------------------------------
// Performs one iteration of each island
//---------------------------------------
bool Algorithm::Iterate() {
   
    bool finish = false;

    #pragma omp parallel for if(parallel_enabled)
    for(int i=0; i<data.NI; i++) if(islands[i]->Iterate()) finish = true;
            
    return finish;
}

void Algorithm::Construct() {
   
    #pragma omp parallel for if(parallel_enabled)
    for(int i=0; i<data.NI; i++) islands[i]->Construct();
            
}

//-----------------------------
// Communication among islands
//-----------------------------
void Algorithm::Migrate() {

    if(data.NI>1) {
        if     (data.MM=="none"  ) ;
        else if(data.MM=="ring"  ) Ring();
        else if(data.MM=="fully" ) Fully();
        else if(data.MM=="master") Master();
        else {
            cout <<"\n Wrong migration method.";
            cin.get();
        }
        if(data.MM!="none"  ) cout << "*";
    }
   
}

void Algorithm::Ring() {
   
    Solution vsolution[data.NI];
    for(int i=0; i<data.NI; i++) vsolution[i] = GetBest(i);

    islands[0]->Add(vsolution[data.NI-1]);
    islands[0]->Add(vsolution[1]);
    for(int i=1; i<(data.NI-1); i++) {
        islands[i]->Add(vsolution[i-1]);
        islands[i]->Add(vsolution[i+1]);
    }
    islands[data.NI-1]->Add(vsolution[data.NI-2]);
    islands[data.NI-1]->Add(vsolution[0]);
                    
}

void Algorithm::Fully() {

    Solution vsolution[data.NI];
    for(int i=0; i<data.NI; i++) vsolution[i] = GetBest(i);
    
    for(int i1=0; i1<data.NI; i1++)
        for(int i2=0; i2<data.NI; i2++)
            if(i2!=i1) islands[i2]->Add(vsolution[i1]);
                        
}

void Algorithm::Master() {

    Solution vsolution[data.NI];
    for(int i=0; i<data.NI; i++) vsolution[i] = GetBest(i);

    int ibest = 0;
    for(int i=1; i<data.NI; i++) if(vsolution[i] < vsolution[ibest]) ibest = i;
    
    for(int i=0; i<data.NI; i++) if(i!=ibest) islands[i]->Add(vsolution[ibest]);
    if(data.NM > 1) for(int i=0; i < data.NI; i++) if(i != ibest) islands[ibest]->Add(vsolution[i]);
    
}

//-------------------------------------
// Gets the best solution ini island i
//-------------------------------------
Solution Algorithm::GetBest(int i) {

    return islands[i]->GetBest();

}

//---------------------------------------------
// Gets the best solution among the NI islands
//---------------------------------------------
Solution Algorithm::GetBest() {

    Solution vsolution[data.NI];
    for(int i=0; i<data.NI; i++) vsolution[i] = GetBest(i);
    
    int ibest = 0;
    for(int i=1; i<data.NI; i++)
        if(vsolution[i]<vsolution[ibest]) ibest = i;
    
    return vsolution[ibest];
    
}

//-------------------------------------------
// Prints the algorithm evolution to console
//-------------------------------------------
void Algorithm::PrintLogs(double tcpu, int it) {

 // Prints the algorithm evolution to console
    if(it%data.S==0) {
        cout << " Iteration" << setw(12) << it << "     Cost";
        for(int i=0; i<data.NI; i++) cout << setw(12) << fixed << setprecision(0) << GetBest(i).obj;
        cout << endl << setprecision(6);
    }

 // Saves the algorithm evolution to a file
    vtcpu.emplace_back(tcpu);
    vecInt vcost = vecInt(data.NI,0);
    for(int i=0; i<data.NI; i++) vcost[i] = GetBest(i).obj;
    mcost.emplace_back(vcost);

}

//--------------------------------------------------------------------
// Saves the algorithm evolution and best cost and solution to a file
//--------------------------------------------------------------------
void Algorithm::SaveLogs() {

 // Saves the algorithm evolution to a file
    for(int it=0; it< vtcpu.size(); it++) {
        fileEvol << setw(10) << fixed << setprecision(4) << vtcpu[it];
        for (int i = 0; i < data.NI; i++) fileEvol << setw(12) << fixed << setprecision(0) << mcost[it][i];
        fileEvol << endl;
    }

 // Saves the best objs and res to a file
    fileCost << fixed << setprecision(0) << GetBest().obj;

 // Saves the best solution to a file
    Solution solution = GetBest();
    sort(solution.sol1.begin(), solution.sol1.end());
    for(int u: solution.sol1) fileSolu << u + 1 << endl;

}

//--------------------------------
// Splits a string by a separator 
//--------------------------------
vector<string> Algorithm::split(string line, const string& separator) {
    vector<string> list;
    size_t pos;
    string token;
    while((pos=line.find(separator)) != string::npos) {
        token = line.substr(0,pos);       
        if(!token.empty()) list.push_back(token);
        line.erase(0,pos+1);
    }
    return list;
}

/* 
 * File:   Algorithm.cpp
 * Author: A. Herrán
 */

#include <iostream>
#include "algorithm/Algorithm.h"

// Global data and random engines
bool            parallel_enabled = true;
Data            data;
vector<Tengine> vengine;

void LoadProperties(const string& pathProperties);
void LoadInstance  (const string& pathInstance);
   
int main(int argc, const char *argv[]) {  

 // Console inputs
    LoadInstance(argv[1]);
    int ne  = stoi(argv[2]);
    data.TC = stod(argv[3]);
    data.S  = stoi(argv[4]);
    if(data.S==0) data.S = numeric_limits<int>::max();
    if(argc==6) LoadProperties(argv[5]);
            
 // Seed for random number generation
    random_device rd;
    for(int p=0; p<omp_get_max_threads(); p++) {
        vengine.emplace_back(rd());
        if(ne!=0) vengine[p].seed((p+1)*ne);
        else      vengine[p].seed(random_device{}());
    }

 // Stopping condition
    int    i     = 0;
    double tcpu  = 0.0;
    int    imax  = static_cast<int>(data.TC);
    double tmax  = data.TC;
    //int    imax  = data.TC*data.nV;
    //double tmax  = data.TC*data.nV;

 // Algorithm
    Algorithm algorithm(argv[1],ne);
    auto start = clk::now();
    //while(i<imax) {
    while(tcpu<tmax) {

     // Algorithm iteration
        bool iteration = algorithm.Iterate();
        tcpu = (double)(duration_cast<microseconds>(clk::now()-start)).count()/1e6;

     // Logs and communication at every R iterations
        if(iteration) {
            i++;
            algorithm.PrintLogs(tcpu,i);
            if(i%data.R==0) algorithm.Migrate();
        }

        //if(tcpu>30.0) break;

    }

 // Save results to a file
    algorithm.SaveLogs();

 // End message
    cout << "\n Optimization completed in " << tcpu << " seconds.\n\n";

//    Solution solu = algorithm.GetBest();
//    solu.Evaluate();
//    cout << solu.obj << endl;
//    solu.EvaluateMove();

    return 0;
}

void LoadProperties(const string& pathProperties) {
   
    ifstream file;
    string   line;
    
    file.open(pathProperties);
    if(!file) {
        cout << "\n The properties file can not be opened.";
        exit(1);
    }
       
    while(getline(file,line)) { 
        if(line[0]=='#' || line.size()==1) continue;
        vector<string> tokens = Algorithm::split(line," ");
        if     (tokens[0]=="NI") data.NI = stoi(tokens[2]);
        else if(tokens[0]=="NM") data.NM = stoi(tokens[2]);
        else if(tokens[0]=="MM") data.MM =      tokens[2];
        else if(tokens[0]=="R" ) data.R  = stoi(tokens[2]);
        else if(tokens[0]=="T" ) data.TC = stod(tokens[2]);
        else if(tokens[0]=="MC") data.MC =      tokens[2];
        else if(tokens[0]=="AG") data.AG = stod(tokens[2]);
        else if(tokens[0]=="ME") data.ME =      tokens[2];
        else if(tokens[0]=="MS") data.MS =      tokens[2];
        else if(tokens[0]=="MU") data.MU = stoi(tokens[2]);
        else if(tokens[0]=="VD") data.VD = stoi(tokens[2]);
        else if(tokens[0]=="PT") data.PT = stoi(tokens[2]);
        else if(tokens[0]=="SK") data.SK = stoi(tokens[2]);
        else if(tokens[0]=="NT") data.NT = stoi(tokens[2]);
        else if(tokens[0]=="KW") data.KW = stoi(tokens[2]);
        else if(tokens[0]=="Q" ) data.Q  = stoi(tokens[2]);
        else if(tokens[0]=="BT") data.BT = stod(tokens[2]);
        else if(tokens[0]=="NL") data.NL = stoi(tokens[2]);
        else if(tokens[0]=="AL") data.AL = stod(tokens[2]);
        else {
            cout << "\n Parameter " << tokens[0] << " does not exists.";
            exit(1);
        }  
    }
    
    file.close();
    
}

void LoadInstance(const string& pathInstance) {
    
 // Opens the instance file 
    ifstream file;
    file.open(pathInstance);
    if(!file) {
        cout << "\n The instance file can not be opened.";
        cin.get();
    }

 // Loads the Problem dimensions    
    string text;
    do { file >> text; } while(text!="p");
    file >> text >> data.nV >> text;

 // Loads the Costs matrix
    data.W = matInt(data.nV,vecInt(data.nV,0));
    int i, j;
    while(!file.eof()) {
        file >> text >> i >> j;
        data.W[i-1][j-1] = 1;
        data.W[j-1][i-1] = 1;
    }
    data.nE = 0;
    for(i=0; i<data.nV; i++) {
        for(j=i+1; j<data.nV; j++) {
            if(data.W[i][j]==1) data.nE++;
        }
    }

 // Closes the instance file 
    file.close();   
    
}

/* 
 * File:   includes.h
 * Author: A. Herrán
 */

#ifndef INCLUDES_H
#define INCLUDES_H

 // Libraries
    #include <iostream>     // cin()/cout()
    #include <fstream>      // file streams
    #include <iomanip>      // io manipulators
    #include <stdio.h>      // printf(), fprintf(), fopen()
    #include <math.h>       // exp(), pow(), sqrt()
    #include <vector>       // vector class
    #include <limits>       // std::numeric_limits<double>::infinity()
    #include <algorithm>    // sort(), random_shuffle()
    #include <omp.h>        // oparallel execution
    #include <random>       // engines for random number generation
    #include <chrono>       // timer

    //#include <bits/stdc++.h> // All

 // Type definitions
    using namespace std;
    using namespace std::chrono;
    
    using Tengine = mt19937_64;
    using clk     = std::chrono::high_resolution_clock;
    
    using vecInt  = vector<int>;
    using matInt  = vector<vecInt>;
            
    struct Data {
     // Problem parameters
        int     nV;
        int     nE;
        matInt  W;
     // Algorithm parameters
        int     NI = 1;             // Number of Islands
        int     NM = 1;             // Number of Algorithms in each Island
        string  MM = "none";        // Migration Strategy: none, ring, fully, master
        int     R  = 1;             // Best solutions migrates at every N·R iterations 
        int     S  = -1;            // Logs are saved at every S iterations
        double  TC = 0.01;          // Termination Criteria
     // Meta-heuristic parameters
        int     NC = 2;             // Number of constructions
        string  MC = "greedy1";     // Construction: random, equal, balanced, greedy1, greedy2 (A, D)
        double  AG = 0.50;          // Alpha coefficient controlling the greediness: 0-purely random, 1-purely greedy
        string  ME = "best";        // Exploration: best, hybrid, first, reduced
        string  MS = "gvns";        // Search: grasp, ils, vnd, bvns, gvns, sa
        int     MU = 0;             // Multi-start: no (0), yes (1)
        int     VD = 3;             // Exploration sequence of LS's in VND
        int     PT = 1;             // Perturbation procedure for ILS
        int     SK = 3;             // Shake procedure for VNS (Basic or General)
     // Tabu List specific parameters
        int     NT = 0;             // Maximum number of elements in the Tabu list
     // GRASP specific parameters
        int     KW = 20;            // Number of iterations of the warming phase
        int     Q  = 2;             // Maximum number of dev away from the best
     // VNS specific parameters
        double  BT = 0.2;           // Beta coefficient for VNS (Basic or General)
     // SA specific parameters
        int     NL = 100;           // Number of iterations in each cycle
        double  AL = 0.99;          // Cooling speed
    };
    
 // Problem data (global variables)
    extern bool            parallel_enabled;
    extern vector<Tengine> vengine;
    extern Data            data;
    
#endif /* INCLUDES_H */

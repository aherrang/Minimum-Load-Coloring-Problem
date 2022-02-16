/* 
 * File:   Header file for class Solution
 * Author: A. Herrán
 */

#ifndef SOLUTION_H
#define	SOLUTION_H

#include "includes.h"

class Solution {
        
    public:
                
     // Public atributes
        vecInt  sol1;   // Set Vr
        vecInt  sol2;   // Set Vb
        int     obj;    // Objective function value
        int     obj1;   // |Er|
        int     obj2;   // |Eb|
        vecInt  phi;    // Vertex coloring
        matInt  Si;     // Degree in
        matInt  So;     // Degree out

     // Constructor/destructor
        Solution();
        Solution(const Solution &orig);
        virtual ~Solution();

     // Operators redefinition
        bool operator<(const Solution &solution) const { return obj>solution.obj; }
        bool operator>(const Solution &solution) const { return obj<solution.obj; }

     // Public functions
        void    Construct();
        void    Evaluate ();
        bool    Explore  (const string& ME, int k);
        void    Shake    (int ks);

    private:

     // Random numbers
        template <class T>
        void rndShuffle(T &vec) {
            Tengine &engine = vengine[omp_get_thread_num()];
            shuffle(vec.begin(),vec.end(),engine);
        }

        static int rndInt(int from, int upto) {
            Tengine &engine = vengine[omp_get_thread_num()];
            uniform_int_distribution<int> rndDist(from,upto);
            return rndDist(engine);
        }

        static double rndDbl(double from, double upto) {
            Tengine &engine = vengine[omp_get_thread_num()];
            uniform_real_distribution<double> rndDist(from,upto);
            return rndDist(engine);
        }

     // Construction methods
        void    ConstructiveRandom();
        void    ConstructiveGreedy(int constructive, double alpha);
        int     getGreedy1(vecInt &CL, double alpha);
        int     getGreedy2(vecInt &CL, double alpha);

     // Evaluation of a move
        int     EvaluateMove();
        void    DataInit();
        void    DataUpdate(int v);

     // Exchange move
        void    Exchange          (int i1, int i2);
        int     EvaluateExchange  (int i1, int i2);
        bool    ExploreExchange   (int strategy);
        bool    ExploreExchangeInc(int strategy);
        bool    ExploreExchangeRedu1(int k);
        bool    ExploreExchangeRedu2(int k);

     // Drop move
        void    Drop(int i1);
        int     EvaluateDrop(int i1);
        bool    ExploreDropInc(int strategy);

     // Add move
        void    Add (int i2);
        int     EvaluateAdd (int i2);
        bool    ExploreAddInc(int strategy);

     // Extended
        bool    ExploreExtendedBestInc();

     // Shake procedures for VNS
        void    Shake1(int ks);
        void    Shake2(int ks);
        void    Shake3(int ks);

};

#endif	/* SOLUTION_H */

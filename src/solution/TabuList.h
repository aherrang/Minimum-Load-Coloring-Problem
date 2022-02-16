/* 
 * File:   Header file for class TabuList
 * Author: A. Herrán
 */

#ifndef TABULIST_H
#define TABULIST_H

#include "includes.h"

class TabuList {
    
    public:
    
     // Constructor/destructor   
        TabuList();

        TabuList(const TabuList& orig);
        virtual ~TabuList();
        
     // Public functions
        void Add  (vecInt &sol);
        bool Check(vecInt &sol);
        
    private:

     // Private attributes
        vector<string> tabulist;
        
     // Private functions 
        static string ToString(vecInt sol);
        
};

#endif /* TABULIST_H */

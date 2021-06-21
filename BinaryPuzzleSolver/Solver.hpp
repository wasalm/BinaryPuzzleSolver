//
//  Solver.hpp
//  BinaryPuzzleSolver
//
//  Created by Andries Salm on 06-06-17.
//  Copyright © 2017 Andries Salm. All rights reserved.
//

#ifndef Solver_hpp
#define Solver_hpp

#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Solver {
private:
    
    int size = 0;
    
    vector<vector<int> > sum; //row 0, row 1, col 0, col 1
    string game;
    
    void setField(int i, int j, char val);
    
    void basicFill();
    void completeRow();
    void testAllPosibilities();
    
    void testAllPosibilitiesRow(int i);
    void testAllPosibilitiesCol(int j);
    void getPosibilitiesStep(string input, list<string>* result, int zeroLeft, int oneLeft);

    
public:
    
    void setGame(string _game);
    void solveGame();
    string getGame();
    void printGame();
    void printGameWithSums();
};


#endif /* Solver_hpp */

//
//  main.cpp
//  BinaryPuzzleSolver
//
//  Created by Andries Salm on 06-06-17.
//  Copyright © 2017 Andries Salm. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "Solver.hpp"


int main(int argc, const char * argv[]) {
    clock_t tStart = clock();
    
    string game = "";
//    game = "...........00.0.....0.1.0.......0......0...0.0..10..1........0.."; //heel moeilijk 04-06-17
//    game = ".1.0..1.0..0.0......0..1.00..1........1..0...0.....1.......1...1"; //heel moeilijk 25-05-17
//    game = ".1....0...1100..1...1..0...1..1...0."; // makkelijk 6x6 1 oke
    game = "......00..0...0....1..1.1..11......."; // gemiddeld 6x6 1 oke
//    game = "...1.1..1..00.............0......11."; // moeilijk 6x6 1
//    game = "1.1..1....0..0........0.1..1....0..."; // heel moeilijk 6x6 1
//    game = ".00..0..1..00.1..1.........1..0..............0..0....11...1..1......1...11...00..........0................0.......0......1...1....0.......0.1...........0........11.....0.....0.00.00..1.0.........."; //Denksport 80.59
//    game = "...00..0...1....1........0...10.....0...0....1...1....0.0......0...0.0.1.0..1..00....0.......0..0.0.";
    game = "..0..........11..1.........1..001...0.....0...1.1....0...0....1.";

    Solver solver;
    
    solver.setGame(game);
    cout << "Before: " << endl;
//    solver.printGame();
    solver.printGameWithSums();
    solver.solveGame();
    cout << "After: " << endl;
//    solver.printGame();
    solver.printGameWithSums();
    cout << endl;
    
    printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}

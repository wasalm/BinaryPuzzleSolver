//
//  Solver.cpp
//  BinaryPuzzleSolver
//
//  Created by Andries Salm on 06-06-17.
//  Copyright © 2017 Andries Salm. All rights reserved.
//

#include "Solver.hpp"
#include <math.h>

using namespace std;

void Solver::setGame(string _game) {
    double len = _game.length();
    
    
    /*
     *  Check size;
     */
    if(floor(sqrt(len)) != sqrt(len)) {
        throw invalid_argument("Given game is not square");
    }
    
    size = (int) sqrt(len);
    
    if(size % 2 == 1) {
        throw invalid_argument("The game has an odd number of rows");
    }
    
    sum.clear();
    //prefill sum fields;
    for(int i=0; i<size; i++) {
        vector<int> item(4,0);
        sum.push_back(item);
    }
    
    /*
     *  Check elements and fill summation;
     */
    for(int i=0; i< size; i++) {
        for(int j = 0; j< size; j++)
        {
            if(_game[i * size + j] != '.' && _game[i * size + j] != '0' && _game[i * size + j] != '1')
            {
                string msg = "Invalid symbol ";
                msg += _game[i * size + j];
                throw invalid_argument(msg);
            }
            
            if(_game[i * size + j] == '0') {
                sum[i][0] ++;
                sum[j][2] ++;
            } else if(_game[i * size + j] == '1') {
                sum[i][1] ++;
                sum[j][3] ++;
            }
            

        }
    }
    
    game = _game;
    
}

string Solver::getGame() {
    return game;
}

void Solver::printGame() {
    for(int i=0; i< size; i++) {
        for(int j=0; j< size; j++) {
            cout << game[i * size + j];
        }
        cout << endl;
    }
    cout << endl;
}

void Solver::printGameWithSums(){
    for(int i=0; i< size; i++) {
        for(int j=0; j< size; j++) {
            cout << game[i * size + j] << " ";
        }
        cout << "  " << sum[i][0] << " " << sum[i][1];
        cout << endl;
    }
    
    cout << endl;
    for(int j=0; j< size; j++) {
        cout << sum[j][2] << " ";
    }
    cout << endl;
    for(int j=0; j< size; j++) {
        cout << sum[j][3] << " ";
    }
    cout << endl;
    
    
    cout << endl;
}

void Solver::solveGame() {
    string prevGame;
    
    //Do the basic fill
    prevGame = game;
    basicFill();
    
    if(prevGame != game) {
        //Basicfill does work, hence do it again.
        solveGame();
    } else {
        //Basicfill doesn't work, hence do complete rows
        prevGame = game;
        completeRow();
        if(prevGame != game) {
            //completeRow does work, hence repeat again with basicfill
            solveGame();
        } else {
            //completeRow doesn't work, hence do testAllPosibilities()
            prevGame = game;
            testAllPosibilities();
            if(prevGame != game) {
                //testAllPosibilities does work, hence repeat again with basicfill
                solveGame();
            } else {
                //testAllPosibilities doesn't work, so we are out of options and return;
                return;
            }

        }
    }
}

void Solver::setField(int i, int j, char val) {
    if(game[i * size + j] == '.') {
        game[i * size + j] = val;
        if(val == '1') {
            sum[i][1] ++;
            sum[j][3] ++;
        } else {
            sum[i][0] ++;
            sum[j][2] ++;
        }
    }
}

void Solver::basicFill() {
    for(int i=0; i< size; i++ )
    {
        for(int j=0; j< size; j++) {
            if(game[i* size + j] == '.')
            {
                // Row: .XX
                if(j < size-2) {
                    if (game[i* size + j +1] == game[i* size + j +2] && game[i* size + j +1] != '.') {
                        setField(i, j, (game[i* size + j+1] == '1') ? '0' : '1');
                    }
                }
            
                // Row: X.X
                if(j > 0 && j < size - 1) {
                    if (game[i* size + j -1] == game[i* size + j +1] && game[i* size + j -1] != '.') {
                        setField(i, j, (game[i* size + j-1] == '1') ? '0' : '1');
                    }
                }
                // Row: .XX
                if(j > 1) {
                    if (game[i* size + j -2] == game[i* size + j -1] && game[i* size + j -1] != '.') {
                        setField(i, j, (game[i* size + j-1] == '1') ? '0' : '1');
                    }
                }
                
                // Col: .XX
                if(i < size-2) {
                    if (game[(i+1)* size + j] == game[(i+2)* size + j] && game[(i+1)* size + j] != '.') {
                        setField(i, j, (game[(i+1)* size + j] == '1') ? '0' : '1');
                    }
                }
                
                // Col: X.X
                if(i > 0 && i < size-2) {
                    if (game[(i-1)* size + j] == game[(i+1)* size + j] && game[(i+1)* size + j] != '.') {
                        setField(i, j, (game[(i+1)* size + j] == '1') ? '0' : '1');
                    }
                }
                
                // Col: .XX
                if(i > 1) {
                    if (game[(i-1)* size + j] == game[(i-2)* size + j] && game[(i-1)* size + j] != '.') {
                        setField(i, j, (game[(i-1)* size + j] == '1') ? '0' : '1');
                    }
                }
            }
        }
    }
}

void Solver::completeRow() {
    for(int i=0; i< size; i++) {
        if(sum[i][0] == size/2 && sum[i][1] != size/2) {
            for(int j=0; j<size; j++) {
                if(game[i*size + j] == '.'){
                    setField(i, j, '1');
                }
            }
        }
        
        if(sum[i][0] != size/2 && sum[i][1] == size/2) {
            for(int j=0; j<size; j++) {
                if(game[i*size + j] == '.'){
                    setField(i, j, '0');
                }
            }
        }
        
        if(sum[i][2] == size/2 && sum[i][3] != size/2) {
            for(int j=0; j<size; j++) {
                if(game[j*size + i] == '.'){
                    setField(j, i, '1');
                }
            }
        }
        
        if(sum[i][2] != size/2 && sum[i][3] == size/2) {
            for(int j=0; j<size; j++) {
                if(game[j*size + i] == '.'){
                    setField(j, i, '0');
                }
            }
        }
    }
}

void Solver::testAllPosibilities() {
    for(int i = 0; i < size; i++) {
        testAllPosibilitiesRow(i);
        testAllPosibilitiesCol(i);
    }
    
}

void Solver::testAllPosibilitiesRow(int i) {
    if(sum[i][0] + sum[i][1] == size) {
        return;
    }
    
    string row = game.substr(i * size, size);
    list<string> result;

    getPosibilitiesStep(row, &result, size/2 - sum[i][0], size/2 - sum[i][1]);
    
    //Compare with other rows
    for(list<string>::const_iterator k = result.begin(); k != result.end(); k++) {
        for(int n = 0; n < size; n++) {
            bool equal = true;
            for(int m = 0; m < size && equal; m++) {
                if(game[n * size + m] != (*k)[m]) {
                    equal = false;
                }
            }
            if(equal) {
                result.erase(k++);
                break;
            }
        }
    }
    
    //analyse result
    for(int j = 0; j < size; j++) {
        if(row[j] == '.') {
            bool canBeZero = false;
            bool canBeOne = false;
            for(list<string>::const_iterator k = result.begin(); k != result.end(); k++) {
                if((*k)[j] == '0') {
                    canBeZero = true;
                } else {
                    canBeOne = true;
                }
            }
            
            if(canBeZero && ! canBeOne) {
                setField(i, j, '0');
            }
            
            if(!canBeZero && canBeOne) {
                setField(i,j, '1');
            }
        }
    }
}

void Solver::testAllPosibilitiesCol(int j) {
    if(sum[j][2] + sum[j][3] == size) {
        return;
    }
    
    string row = "";
    for(int i = 0; i< size; i++) {
        row += game[i * size + j];
    }

    list<string> result;

    getPosibilitiesStep(row, &result, size/2 - sum[j][2], size/2 - sum[j][3]);

    //Compare with other cols
    for(list<string>::const_iterator k = result.begin(); k != result.end(); k++) {
        for(int n = 0; n < size; n++) {
            bool equal = true;
            for(int m = 0; m < size && equal; m++) {
                if(game[m * size + n] != (*k)[m]) {
                    equal = false;
                }
            }
            if(equal) {
                result.erase(k++);
                break;
            }
        }
    }
    
    //analyse result
    for(int i = 0; i < size; i++) {
        if(row[i] == '.') {
            bool canBeZero = false;
            bool canBeOne = false;
            
            for(list<string>::const_iterator k = result.begin(); k != result.end(); k++) {
                if((*k)[i] == '0') {
                    canBeZero = true;
                } else {
                    canBeOne = true;
                }
            }
            
            if(canBeZero && ! canBeOne) {
                setField(i, j, '0');
            }

            if(!canBeZero && canBeOne) {
                setField(i,j, '1');
            }
        }
    }
}

void Solver::getPosibilitiesStep(string input, list<string> *result, int zeroLeft, int oneLeft) {
    
    size_t pos = input.find('.');
    
    if(pos != string::npos) {
        // We have found something
        if(zeroLeft > 0) {
            input[pos] = '0';
            getPosibilitiesStep(input, result, zeroLeft -1, oneLeft);
        }
        
        if(oneLeft > 0) {
            input[pos] = '1';
            getPosibilitiesStep(input, result, zeroLeft, oneLeft-1);
        }
    } else {
        size_t pos0 = input.find("000");
        size_t pos1 = input.find("111");
        
        if(pos0 == string::npos && pos1 == string::npos) {
           result -> push_back(input);
        }

    }
}

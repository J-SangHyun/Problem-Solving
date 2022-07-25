#include <iostream>
#include <vector>

#define SIZE 9

using namespace std;
typedef vector<int> vint;

bool backtracking(vector<vint> &sudoku, vector<vint> &empty, int idx);

int main(void) {
    vector<vint> sudoku(SIZE, vint(SIZE));
    vector<vint> empty;
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cin >> sudoku[i][j];
            if(sudoku[i][j] == 0) {
                vint pos(2);
                pos[0] = i;
                pos[1] = j;
                empty.push_back(pos);
            }
        }
    }
    
    backtracking(sudoku, empty, 0);
    
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

bool backtracking(vector<vint> &sudoku, vector<vint> &empty, int idx) {
    bool valid;
    if(idx >= empty.size()) {
        return true;
    }
    int pos_i = empty[idx][0], pos_j = empty[idx][1];
    int neighbor_i, neighbor_j;
    
    for(int n = 1; n <= SIZE; n++) {
        valid = true;
        sudoku[pos_i][pos_j] = n;
        
        for(int i = 0; i < SIZE; i++) {
            if(sudoku[i][pos_j] == n && i != pos_i) {
                valid = false;
            }
            if(sudoku[pos_i][i] == n && i != pos_j) {
                valid = false;
            }
        }
        
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                neighbor_i = (pos_i / 3) * 3 + i;
                neighbor_j = (pos_j / 3) * 3 + j;
                if(pos_i != neighbor_i || pos_j != neighbor_j) {
                    if(sudoku[neighbor_i][neighbor_j] == n) {
                        valid = false;
                    }
                }
            }
        }
        if(!valid) {
            continue;
        }
        
        if(backtracking(sudoku, empty, idx+1)) {
            return true;
        }
    }
    sudoku[pos_i][pos_j] = 0;
    return false;
}


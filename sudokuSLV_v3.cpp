#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>
#include <algorithm> // shuffle
#include <random> // mt19937
#include <chrono> // time based seeding
using namespace std;

class Puzzle {
    int grid[81], rows[9], cols[9], boxes[9];
    mt19937 rng; // yea we store the rng as an object property

    void toggle(int i, int n, bool changeGrid){
        int digit = 1 << (n - 1);
        int bi = 3*(i / 27) + (i % 9)/3; //box index lol

        if(changeGrid) grid[i] = (grid[i] == 0)? n : 0 ;
        rows[i / 9] ^= digit;
        cols[i % 9] ^= digit;
        boxes[bi] ^= digit;
    }

public:
    bool solve(int i = 0){
        if(i == 81) return true;
        
        if(grid[i] == 0){
            for(int j = 1; j <= 9; j++){

                int digit = 1 << (j - 1);
                if(!((rows[i / 9] & digit) || (cols[i % 9] & digit) || (boxes[3*(i / 27) + (i % 9)/3] & digit))){
                    toggle(i, j, true);
                    if(solve(i + 1)) return true;
                    toggle(i, j, true);
                }
            }
            return false;
        }
        return solve(i + 1);
    }

    void display(){
        for(int i = 0; i < 81 ; i++){
            if(i % 27 == 0) cout<<"+-------+-------+-------+\n";
            if(i % 3 == 0) cout<<"| ";

            if(grid[i]) cout << grid[i] << " ";
            else cout<<". ";
            if ((i + 1) % 9 == 0) cout<<"|\n";
        }
        cout<<"+-------+-------+-------+\n";
    }

    Puzzle(int puzzle[81]) {
        memcpy(grid, puzzle, sizeof(grid));
        memset(rows, 0, sizeof(rows));
        memset(cols, 0, sizeof(cols));
        memset(boxes, 0, sizeof(boxes));

        for(int i = 0; i < 81; i++) if(grid[i]) toggle(i, grid[i], false);
        
        auto seed = chrono::system_clock::now().time_since_epoch().count(); // bullshit
        rng.seed(seed); //the fuckin seeding
    }
};

int main(){
    int grid[81] = {
        1, 0, 0, 0, 2, 0, 0, 0, 0,
        0, 0, 0, 0, 8, 0, 6, 0, 0,
        0, 6, 0, 4, 0, 0, 8, 1, 2,
        0, 8, 0, 0, 0, 0, 2, 0, 5,
        0, 0, 0, 9, 1, 2, 0, 0, 0,
        3, 0, 9, 0, 0, 0, 0, 4, 0,
        6, 7, 2, 0, 0, 8, 0, 3, 0,
        0, 0, 5, 0, 6, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 0, 8,
    };
    Puzzle puzzle01(grid);

    cout<<"Unsolved Puzzle :\n";
    puzzle01.display();

    if(puzzle01.solve()){
        cout<<"The solved Sudoku puzzle is:\n";
        puzzle01.display();
    } else cout<<"The sudoku puzzle can't be solved";
}
#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>
#include <algorithm> // shuffle
#include <random> // mt19937
#include <chrono> // time based seeding
using namespace std;

/*----------------------------[FUNCTIONS INVOLVED IN THE SUDOKUGEN V3 ENGINE]------------------------------+
+ void toggle(index, number) : If index square is empty, then index is filled with number in the grid[] and 
the other 3 bitmapped arrays (rows, columns and boxes). Conversely, if index square is full, the index is 
emptied in all 4 arrays.                                                                     

+ int solve(index, count, limit, isRandom) : The penultimate solver, generator and counter function. If       
limit = 1, then no counting involved and grid is altered, if limit = 2 then we count solutions and
don't alter the grid. isRandom = True for generating, False for solving and counting. Returns count value.                    
                                                                                                          
+ void removeNums(df) : Removes numbers from randomized squares and checks number of solutions 
at each step. Number of holes is set to be exactly equal to df value (difficulty factor). 
The loop runs again and again, through a randomized array of indices till the required number of holes
is achieved.                                          
----------------------------------------------------------------------------------------------------------*/

class SudokuEngine {
    int grid[81], rows[9], cols[9], boxes[9];
    mt19937 rng; // yea we store the rng as an object property

    void toggle(int i, int n){
        int digit = 1 << (n - 1);
        int bi = 3*(i / 27) + (i % 9)/3; //box index lol

        grid[i] = (grid[i] == 0)? n : 0 ;
        rows[i / 9] ^= digit;
        cols[i % 9] ^= digit;
        boxes[bi] ^= digit;
    }

    int solve(int i, int count, int limit, bool isRandom){
        if(count >= limit) return count;
        if(i == 81) return count + 1;

        if(grid[i] != 0) return solve(i + 1, count, limit, isRandom);

        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        if(isRandom) shuffle(numbers.begin(), numbers.end(), rng);

        for(int num : numbers){
            int digit = 1 << (num - 1);
            int bi = 3*(i / 27) + (i % 9)/3; //box index lol
            if(!((rows[i / 9] & digit) || (cols[i % 9] & digit) || (boxes[bi] & digit))){
                toggle(i, num);
                count = solve(i + 1, count, limit, isRandom);

                if(limit > 1) toggle(i, num); //this activates when we are counting solutions

                if(count >= limit) return count;

                if(limit == 1) toggle(i, num); //this activates when we are generating or solving puzzles
            }
        }
        return count;
    }

    void removeNums(int df = 35){
        vector<int> cells(81);
        iota(cells.begin(), cells.end(), 0); //fills the vector array with 0 - 80
        shuffle(cells.begin(), cells.end(), rng);

        int holes = 0, i = 0;

        while(holes < df){
            if(i > 80){
                i = 0;
                shuffle(cells.begin(), cells.end(), rng);
            }

            int idx = cells[i];
            int temp = grid[idx];
            if(temp == 0){
                i++;
                continue;
            }
            toggle(idx, temp);

            int count = solve(0, 0, 2, false);

            if (count != 1) toggle(idx, temp);
            else holes++;
            i++;
        }

        cout << "Missing Squares: "<< holes << endl;
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

public:
    SudokuEngine() {
        memset(grid, 0, sizeof(grid));
        memset(rows, 0, sizeof(rows));
        memset(cols, 0, sizeof(cols));
        memset(boxes, 0, sizeof(boxes));
        
        auto seed = chrono::system_clock::now().time_since_epoch().count(); // bullshit
        rng.seed(seed); //the fuckin seeding
    }

    void generate(int difficulty = 35) { // I expect a fuckin empty grid here okay?
        solve(0, 0, 1, true);
        removeNums(difficulty);

        display();
    }

    void solvePuzzle(){
        solve(0, 0, 1, false);
        display();
    }
};

int main(){
    SudokuEngine grid01;
    grid01.generate(50);

    int res;
    cout << "Press 0 to get the solution (any other number to quit): ";
    cin >> res;
    if(res == 0) grid01.solvePuzzle();
}
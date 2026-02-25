#include <iostream>
#include <vector>
#include <cstring>
#include <numeric>
#include <algorithm> // shuffle
#include <random> // mt19937
#include <chrono> // time based seeding
using namespace std;

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
                
                if(count >= limit) return count;
                toggle(i, num);
            }
        }
        return count;
    }

    void removeNums(int df = 35){
        vector<int> cells(81);
        iota(cells.begin(), cells.end(), 0);
        shuffle(cells.begin(), cells.end(), rng);

        int holes = 0, i = 0;

        while(holes < df){
            // cout << i << " ";
            if(i > 80){
                i = 0;
                shuffle(cells.begin(), cells.end(), rng);
            }

            int idx = cells[i];
            int temp = grid[idx];
            toggle(idx, temp);

            int count = solve(0, 0, 2, false);
            if (count != 1) toggle(idx, temp);
            else holes++;
            // cout << i << " ";
            i++;
        }

        cout << "Missing Squares: "<< holes << endl;
    }

    void display(){
        for(int i = 0; i < 81 ; i++){
            if(i % 27 == 0) cout<<"+-------+-------+-------+\n";
            if(i % 3 == 0) cout<<"| ";

            if(grid[i]) cout << grid[i] << " ";
            else cout<<"  ";
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
        display();
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
    grid01.generate();

    grid01.solvePuzzle();
}
#include <iostream>
#include <vector>
#include <algorithm> // shuffle
#include <random> // mt19937
#include <chrono> // time based seeding
using namespace std;

/*--------------------------[FUNCTIONS INVOLVED IN THE SUDOKU GENERATION ENGINE]---------------------------+
|bool isOk() : Checks sudoku rules, and decides if a number can be placed in the empty cell. (Returns bool)|
|                                                                                                          |
|bool generate() : Generates a full board out of an empty board. Well randomized. Recursive function.      |
|                  (Returns true when the board's full)                                                    |
|                                                                                                          |
|int solveCount() : Solves the board once and then tries again, to find a second solve.                    |
|                  (Returns the number of solutions, if its > 1 then it's 2).                              |
|                                                                                                          |
|void removeNums() : Removes numbers from randomized squares and checks number of solutions at each step.  |
|                    If solution count > 1, then it's conventionally unsolvable by humans,                 |
|                    and so we restart with another random order.                                          |
+---------------------------------------------------------------------------------------------------------*/

bool isOk(vector<vector<int>>& grid, int num, int i, int j){
    for (int x = 0; x < 9; x++){
        if (grid[i][x] == num) return false;
        if (grid[x][j] == num) return false;
    }

    int boxr = i - i % 3;
    int boxc = j - j % 3;

    for (int x = boxr; x < boxr + 3; x++){
        for (int y = boxc; y < boxc + 3; y++){
            if (grid[x][y] == num) return false;
        }
    }

    return true;
}

bool generate(vector<vector<int>>& grid){
    bool isEmpty = false;
    int i, j;

    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            if (grid[i][j] == 0){
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }
    if (!isEmpty) return true;

    vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    shuffle(candidates.begin(), candidates.end(), gen);

    for (int num : candidates){
        if (isOk(grid, num, i, j)){
            grid[i][j] = num;
            if (generate(grid)) return true;

            grid[i][j] = 0;
        }
    }

    return false;
}

void display(vector<vector<int>>& grid){
    for (int i = 0; i < 9; i++){
        if (i % 3 == 0) cout << "+-------+-------+-------+\n";
        for (int j = 0; j < 9; j++){
            if (j % 3 == 0) cout << "| ";
            if(grid[i][j]) cout << grid[i][j] << " ";
            else cout << "  ";
        }
        cout << "|\n";
    }
    cout << "+-------+-------+-------+\n";
}

int solveCount(vector<vector<int>>& grid, int count){
    bool isEmpty = false;
    int i, j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(grid[i][j] == 0){
                isEmpty = true;
                break;
            }
        }
        if(isEmpty) break;
    }
    if (!isEmpty) return count + 1;

    for(int num = 1; num <= 9; num++){
        if(isOk(grid, num, i, j)){
            grid[i][j] = num;
            count = solveCount(grid, count);
            grid[i][j] = 0;

            if (count > 1) return count;
        }
    }

    return count;
}

void removeNums(vector<vector<int>>& grid, int df){
    vector<pair<int,int>> coordList;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            coordList.push_back({i, j});
        }
    }
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    shuffle(coordList.begin(), coordList.end(), gen);
    
    int i = 0, holes = 0;

    while(holes < df){
        if(i >= 81){
            i = 0;
            shuffle(coordList.begin(), coordList.end(), gen);
        }
        int r = coordList[i].first;
        int c = coordList[i].second;
        int count = 0;

        int temp = grid[r][c];
        if (temp == 0) {
            i++;
            continue;
        }
        grid[r][c] = 0;

        count = solveCount(grid, count);
        if (count != 1) {
            grid[r][c] = temp;
            shuffle(coordList.begin(), coordList.end(), gen);
        } else holes++;
        i++;
    }
    cout << "Removed "<< holes << " numbers.\n";
}

int main(){

    vector<vector<int>> grid0 = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int difficultyFactor = 50;
    // Maximum value of df = 50

    if (generate(grid0)) display(grid0);
    removeNums(grid0, difficultyFactor);
    display(grid0);

}
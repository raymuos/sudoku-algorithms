#include <iostream>
#include <vector>
#include <algorithm> // shuffle
#include <random> // mt19937
#include <chrono> // time based seeding

using namespace std;

const int SIZE = 9;
vector<int> ORDER = {1, 2, 3, 4, 5, 6, 7, 8, 9};

bool isOk(vector<vector<int>>& grid, int num, int i, int j){
    for (int x = 0; x < SIZE; x++){
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

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    shuffle(ORDER.begin(), ORDER.end(), gen);

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

    for (int num : ORDER){
        if (isOk(grid, num, i, j)){
            grid[i][j] = num;
            if (generate(grid)) return true;

            grid[i][j] = 0;
        }
    }

    return false;
}

void display(vector<vector<int>>& grid){
    for (int i = 0; i < SIZE; i++){
        if (i % 3 == 0) cout << "+-------+-------+-------+\n";
        for (int j = 0; j < SIZE; j++){
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
            if (count > 1) return count;
            
            grid[i][j] = 0;
        }
    }

    return count;
}

void removeNums(vector<vector<int>>& grid, int df){
    vector<pair<int,int>> coordList;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            coordList.push_back({i, j});
        }
    }
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    shuffle(coordList.begin(), coordList.end(), gen);
    
    int lc = 0;

    for( auto p : coordList ){
        int r = p.first;
        int c = p.second;
        int count = 0;

        int temp = grid[r][c];
        grid[r][c] = 0;
        count = solveCount(grid, count);
        if(count != 1) grid[r][c] = temp;
        else lc++;

        if(lc >= df) break;
    }
    cout << "Removed "<< lc << " numbers.\n";
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
    int difficultyFactor = 30;

    if (generate(grid0)) display(grid0);
    removeNums(grid0, difficultyFactor);
    display(grid0);

}
#include<iostream>
using namespace std;

bool isOk(int grid[9][9], int num, int i, int j){

    for(int x = 0; x < 9; x++){
        if(grid[i][x] == num) return false;
        if(grid[x][j] == num) return false;
    }

    int boxr = i - i % 3;
    int boxc = j - j % 3;

    for(int x = boxr; x < boxr + 3; x++){
        for(int y = boxc; y < boxc + 3; y++){
            if (grid[x][y] == num) return false;
        }
    }

    return true;
}

bool solve(int grid[9][9]){
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
    if (!isEmpty) return true;

    for(int num = 1; num <= 9; num++){
        if(isOk(grid, num, i, j)){
            grid[i][j] = num;

            if(solve(grid)) return true;
            grid[i][j] = 0;
        }
    }

    return false;
}

void display(int grid[9][9]){
    for(int i = 0; i < 9 ; i++){
        if(i%3==0) cout<<"+-------+-------+-------+\n";
        for(int j = 0; j < 9; j++){
            if(j % 3 == 0) cout<<"| ";

            if(grid[i][j]) cout<<grid[i][j]<<" ";
            else cout<<"  ";
        }
        cout<<"|\n";
    }
    cout<<"+-------+-------+-------+\n";
}

int main(){
    int grid0[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    cout<<"Unsolved Puzzle :\n";
    display(grid0);

    if(solve(grid0)){
        cout<<"The solved Sudoku puzzle is:\n";
        display(grid0);
    } else {
        cout<<"The sudoku puzzle can't be solved";
    }
}
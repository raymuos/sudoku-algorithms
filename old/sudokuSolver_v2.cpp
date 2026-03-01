#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

bool solverec(int i, vector<int>& grid, int rows[9], int columns[9], int boxes[9]){
    if(i == 81) return true;
    if(grid[i] == 0){
        for(int j = 1; j <= 9; j++){
            int digit = 1 << (j - 1);
            if(!((rows[i / 9] & digit) || (columns[i % 9] & digit) || (boxes[3*(i / 27) + (i % 9)/3] & digit))){
                grid[i] = j;
                rows[i / 9] |= digit;
                columns[i % 9] |= digit;
                boxes[3*(i / 27) + (i % 9)/3] |= digit;

                if(solverec(i + 1, grid, rows, columns, boxes)) return true;
                
                grid[i] = 0;
                rows[i / 9] &= ~digit;
                columns[i % 9] &= ~digit;
                boxes[3*(i / 27) + (i % 9)/3] &= ~digit;
            }
        }
        return false;
    }
    return solverec(i + 1, grid, rows, columns, boxes);
}

bool solve(vector<int>& grid){
    int rows[9], columns[9], boxes[9];

    memset(rows, 0, sizeof(rows));
    memset(columns, 0, sizeof(columns));
    memset(boxes, 0, sizeof(boxes));

    for(int i = 0; i < 81; i++){
        if(grid[i]){
            int digit = 1 << (grid[i]-1);
            rows[i / 9] |= digit;
            columns[i % 9] |= digit;
            boxes[3*(i / 27) + (i % 9)/3] |= digit;
        }
    }
    if (solverec(0, grid, rows, columns, boxes)) return true;
    else return false;
}

void display(vector<int>& grid){
    for(int i = 0; i < 81 ; i++){
        if(i % 27 == 0) cout<<"+-------+-------+-------+\n";
        if(i % 3 == 0) cout<<"| ";

        if(grid[i]) cout << grid[i] << " ";
        else cout<<"  ";
        if ((i + 1) % 9 == 0) cout<<"|\n";
    }
    cout<<"+-------+-------+-------+\n";
}

int main(){
    vector<int> grid = {
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

    cout<<"Unsolved Puzzle :\n";
    display(grid);

    if(solve(grid)){
        cout<<"The solved Sudoku puzzle is:\n";
        display(grid);
    } else {
        cout<<"The sudoku puzzle can't be solved";
    }
}
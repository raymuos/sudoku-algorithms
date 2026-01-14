# sudoku-algorithms
Sudoku Solver and Puzzle Generator built in C++

## Sudoku Solver
Uses Backtracking and Recursive algorithms to find empty squares and fill them with valid numbers.

## Sudoku Puzzle Generator
1. Uses a full puzzle generated using purely non-deterministic randomness by time-seeding the Mersenne Twister engine, according to the modern C++ standards.

2. The full puzzle is then subjected to a "hole-digging" algorithm, thant removes a number randomly and checks the solvability of the puzzle at every iteration, so that there's only one solution to the puzzle

3. The number of "holes" can be controlled by changing the difficulty factor variable value. 
<img width="304" height="697" alt="image" src="https://github.com/user-attachments/assets/3c4e5823-5602-4c83-9bb1-f151b2f7e500" />

#ifndef SUDOKU_H
#define SUDOKU_H
#include "include/header.h"

/****************************
Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.


A sudoku puzzle...


...and its solution numbers marked in red.
*********************************************************/
class SudoKu
{
    public:
        SudoKu();
        virtual ~SudoKu();
        void solveSudoku(vector<vector<char> > &board);
    protected:
    private:
};

void test_sudo();
#endif // SUDOKU_H

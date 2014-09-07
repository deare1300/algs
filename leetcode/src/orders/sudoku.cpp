#include "include/sudoku.h"

SudoKu::SudoKu()
{
    //ctor
}

SudoKu::~SudoKu()
{
    //dtor
}

bool row_col_judge(vector<vector<char> > &board, int row, int col, char num)
{
    for(int i = 0; i < 9; ++i)
    {
        if(num == board[row][i])
        {
            return false;
        }
        if(num == board[i][col])
        {
            return false;

        }
    }

    return true;
}

bool square_judge(vector<vector<char> > &board, int row, int col, char num)
{
    int r = row/3 * 3;
    int c = col/3 * 3;
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(board[r+i][c+j] == num)
                return false;
        }
    }
    return true;
}

bool addNum(vector<vector<char> > &board, int row, int col)
{
    //cout<<"addNum:"<<row<<'\t'<<col<<endl;
    if(row == 9)
        return true;
    if(board[row][col] != '.')
    {
        if(col < 8)
           return addNum(board, row, col+1);
        else
           return addNum(board, row+1, 0);
    }
    for(char i = '1'; i <= '9'; ++i)
    {
        if(square_judge(board, row, col, i) && row_col_judge(board, row, col, i))
        {
           // printf("modify num %c\n", i);
            board[row][col] = i;
            if(col < 8)
            {
                if(addNum(board, row, col+1))
                    return true;

            }
            else
            {
                if(addNum(board, row+1, 0))
                    return true;
            }
            board[row][col] = '.';
        }
    }

   // printTVector(board);
    return false;
}


void SudoKu::solveSudoku(vector<vector<char> > &board)
{
    int row = board.size();
    int col = row == 0 ? 0 : board[0].size();
    addNum(board, 0, 0);
}


void test_sudo()
{
    string str[] ={"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."};
    vector<vector<char> > board;
    for(int i = 0; i < 9; ++i)
    {
        board.push_back(vector<char>(&str[i][0], &str[i][9]));
    }
   // printTVector(board);
    SudoKu sudo;
    sudo.solveSudoku(board);
    printTVector(board);

}



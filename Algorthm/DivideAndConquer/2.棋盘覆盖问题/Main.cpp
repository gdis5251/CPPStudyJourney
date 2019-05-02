#include <iostream>
#include <vector>

static const int size = 16;
int chess_board[size][size] = { 0 };
int t = 0;

class Solution
{
public:
    static void ChessBoard(int tr, int tc, int dr, int dc, int size)
    {
        if (size == 1)
            return;
        
        int count;
        count = ++t;
        int s = size / 2;

        if (dr < tr + s && dc < tc + s)
        {
            ChessBoard(tr, tc, dr, dc, s);
        }
        else
        {
            chess_board[tr + s - 1][tc + s - 1] = count;
            ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
        }

        if (dr < tr + s && dc >= tc + s)
        {
            ChessBoard(tr, tc + s, dr, dc, s);
        }
        else
        {
            chess_board[tr + s - 1][tc + s] = count;
            ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
        }

        if (dr >= tr + s && dc < tc + s)
        {
            ChessBoard(tr + s, tc, dr, dc, s);
        }
        else
        {
            chess_board[tr + s][tc + s - 1] = count;
            ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
        }

        if (dr >= tr + s && dc >= tc + s)
        {
            ChessBoard(tr + s, tc + s, dr, dc, s);
        }
        else
        {
            chess_board[tr + s][tc + s] = count;
            ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
        }
    }

    static void Print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%3d", chess_board[i][j]);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


};

int main()
{
    Solution::ChessBoard(0, 0, 1, 2, size);
    Solution::Print();

    return 0;
}


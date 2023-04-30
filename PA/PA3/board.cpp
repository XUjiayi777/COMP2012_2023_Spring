#include "board.h"

Board::Board(const int score[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cells[i][j] = EMPTY;
            this->score[i][j] = score[i][j];
        }
    }
    curPlayer = X;
    id = 0;
}

bool Board::isFull() const
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (cells[i][j] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

bool Board::isFinished() const
{
    bool player_gotten_match = false;
    int now_score = getBoardScore();
    if ((now_score == WIN_SCORE) || now_score == -WIN_SCORE)
    {
        player_gotten_match = true;
    }
    if (isFull() == true || player_gotten_match == true)
    {
        return true;
    }
    return false;
}

int Board::getBoardScore() const
{
    // check if any player has gotten a match
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        int row_count = 0;
        int column_count = 0;
        int j = 0;
        int k = 0;
        while (j < BOARD_SIZE - 1)
        {
            if (cells[i][j] == cells[i][j + 1])
            {
                ++row_count;
                j++;
            }
            else
            {
                break;
            }
        }
        if (row_count == BOARD_SIZE - 1)
        {
            if (cells[i][j] == X)
            {
                return WIN_SCORE;
            }
            else if (cells[i][j] == O)
            {
                return -WIN_SCORE;
            }
        } // check row
        while (k < BOARD_SIZE - 1)
        {
            if (cells[k][i] == cells[k + 1][i])
            {
                ++column_count;
                k++;
            }
            else
            {
                break;
            }
        }
        if (column_count == BOARD_SIZE - 1)
        {
            if (cells[k][i] == X)
            {
                return WIN_SCORE;
            }
            else if (cells[k][i] == O)
            {
                return -WIN_SCORE;
            }
        } // check column
    }
    int dia_count = 0;
    int dia_count_1 = 0;
    for (int p = 0; p < BOARD_SIZE - 1; ++p)
    {
        if (cells[p][p] == cells[p + 1][p + 1])
        {
            ++dia_count;
        }
        if (cells[p][BOARD_SIZE - 1 - p] == cells[p + 1][BOARD_SIZE - 2 - p])
        {
            ++dia_count_1;
        }
        if (dia_count == BOARD_SIZE - 1)
        {
            if (cells[p][p] == X)
            {
                return WIN_SCORE;
            }
            else if (cells[p][p] == O)
            {
                return -WIN_SCORE;
            }
        }
        else if (dia_count_1 == BOARD_SIZE - 1)
        {
            if (cells[p][BOARD_SIZE - 1 - p] == X)
            {
                return WIN_SCORE;
            }
            else if (cells[p][BOARD_SIZE - 1 - p] == O)
            {
                return -WIN_SCORE;
            }
        }
    }

    // calculate the score based on the current cells on the board.
    int X_score = 0;
    int O_score = 0;
    int total_score = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (cells[i][j] == X)
            {
                X_score += score[i][j] * getCellWeight(cells[i][j]);
            }
            else if (cells[i][j] == O)
            {
                O_score += score[i][j] * getCellWeight(cells[i][j]);
            }
        }
    }
    total_score = X_score - O_score;
    return total_score;
}

bool Board::play(const BoardCoordinate &coords)
{
    if (coords.isValid())
    {
        int cellvalue = 0;
        if (cells[coords.row][coords.col] == EMPTY)
        {
            cells[coords.row][coords.col] = curPlayer;
        }
        else{
            return false;
        }
        if (curPlayer == X)
        {
            cellvalue = 1;
            curPlayer = O;
        }
        else if (curPlayer == O)
        {
            cellvalue = 2;
            curPlayer = X;
        }
        else
        {
            cellvalue = 0;
        }
        id += cellvalue * pow(3, (coords.row * BOARD_SIZE + coords.col));
        return true;
    }
    return false;
}

#include "boardtree.h"
#include <iostream>
using namespace std; // remove before assignment

BoardTree::BoardTree(const Board &board)
{
    root = new BoardNode(board);
}

BoardTree::~BoardTree()
{
    delete root;
}

BoardTree *BoardTree::getSubTree(const BoardCoordinate &coords)
{
    if (isEmpty())
    {
        return nullptr;
    }
    if (root->subTree[coords.row][coords.col].root == nullptr)
    {
        Board temp = root->board;
        if (temp.play(coords) == true)
        {
            root->subTree[coords.row][coords.col].root = new BoardNode(temp);
        }
    }
    return &(root->subTree[coords.row][coords.col]);
}

BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth)
{
    if (isEmpty())
    {
        return BoardOptimalMove();
    }

    if (depth == 0 || root->board.isFinished())
    {
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate(-1, -1));
    }
    int estimatedScore = 0;
    if (root->board.getCurPlayer() == X)
    {
        estimatedScore = -WIN_SCORE;
    }
    else if (root->board.getCurPlayer() == O)
    {
        estimatedScore = WIN_SCORE;
    }
    BoardOptimalMove bestMove;
    int first = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            BoardCoordinate coordinate = BoardCoordinate(i, j);
            if (root->subTree[i][j].isEmpty())
            {
                getSubTree(coordinate);
            }
            BoardOptimalMove childMove = root->subTree[i][j].getOptimalMove(depth - 1);
            if (childMove.score == ILLEGAL)
            {
                continue;
            }
            // cout << "i" << i << "j" << j << endl;
            // cout << childMove.score << endl;
            // cout << estimatedScore << endl;
            // cout << root->board.getCurPlayer() << endl;
            if (root->board.getCurPlayer() == X)
            {
                if (childMove.score > estimatedScore)
                {
                    first = 0;
                    estimatedScore = childMove.score;
                    bestMove = BoardOptimalMove(estimatedScore, coordinate);
                }
                if (childMove.score = estimatedScore && first == 0)
                {
                    bestMove = BoardOptimalMove(estimatedScore, coordinate);
                    first++;
                }
            }
            else
            {
                if (childMove.score < estimatedScore)
                {
                    first = 0;
                    estimatedScore = childMove.score;
                    bestMove = BoardOptimalMove(estimatedScore, coordinate);
                }
                if (childMove.score = estimatedScore && first == 0)
                {
                    bestMove = BoardOptimalMove(estimatedScore, coordinate);
                    first++;
                }
            }
        }
    }
    return bestMove;
}
#include "hashtable.h"
BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth)
{
    int index = id % TABLE_SIZE;
    if (table[index] != nullptr)
    {
        BoardHashNode *cur = table[index];
        while (cur != nullptr)
        {
            if (cur->id != id)
            {
                cur = cur->next;
            }
            else
            {
                if (cur->depth < depth)
                {
                    return BoardOptimalMove();
                }
                else
                {
                    return cur->optimalMove;
                }
            }
        }
    }
    return BoardOptimalMove();
}

void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove &optimalMove)
{
    int index = id % TABLE_SIZE;
    int flag = 0;
    if (table[index] == nullptr)
    {
        table[index] = new BoardHashNode(id, depth, optimalMove);
        return;
    }
    else
    {
        BoardHashNode *cur = table[index];
        while (cur != nullptr)
        {
            if (cur->id != id)
            {
                cur = cur->next;
            }
            else
            {
                if (cur->depth < depth)
                {
                    cur->depth = depth;
                    cur->optimalMove = optimalMove;
                    flag = 1;
                    return;
                }
            }
        }
        if (flag == 1)
        {
            return;
        }
        cur = table[index];
        table[index]=new BoardHashNode(id, depth, optimalMove);
        table[index]->next=cur;
        cur = nullptr;
    }
}

void BoardHashTable::clearTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != nullptr)
        {
            BoardHashNode *cur = table[i];
            while (cur != nullptr)
            {
                BoardHashNode *temp = cur;
                cur = cur->next;
                delete temp;
                temp = nullptr;
            }
            table[i] = nullptr;
        }
    }
}
#include "player.h"
#include <cstring>

Player::Player(const char *const name, const int elo)
{
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this->elo = elo;
    this->score = 0;
}

Player::~Player()
{
    delete[] name;
    elo = 0;
    score = 0;
} // task1 finished

PlayerList::PlayerList()
{
    numPlayers = 0;
    players = nullptr;
}

PlayerList::PlayerList(const PlayerList &list)
{
    numPlayers = list.getNumPlayers();
    players = new Player *[numPlayers];
    for (int i = 0; i < numPlayers; i++)
    {
        players[i] = list.getPlayer(i);
    }
}

PlayerList::~PlayerList()
{
    delete[] players;
    numPlayers = 0;
} // task 2 finished

void PlayerList::addPlayer(Player *const player)
{
    Player **new_players = new Player *[numPlayers + 1];
    for (int j = 0; j < numPlayers; j++)
    {
        new_players[j] = players[j];
    }
    new_players[numPlayers] = player;
    delete [] players;
    players = new_players;
    numPlayers++;
}

void PlayerList::sort()
{
    // using insertion sort
    for (int i = 1; i < numPlayers; i++)
    {
        int j = i - 1;
        while (j >= 0)
        {
            if ((*players[j]).getScore() < (*players[j + 1]).getScore())
            {
                Player *temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
            else if ((*players[j]).getScore() == (*players[j + 1]).getScore())
            {
                if ((*players[j]).getELO() < (*players[j + 1]).getELO())
                {
                    Player *temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
            j--;
        }
    }
}

PlayerList *PlayerList::splice(const int startIndex, const int endIndex) const
{
    PlayerList *newone = new PlayerList();
    if (startIndex < 0 || endIndex > numPlayers || startIndex >= endIndex)
    {
        return newone;
    }
    newone->numPlayers = endIndex - startIndex;
    newone->players = new Player *[newone->numPlayers];
    for (int i = 0; i < newone->numPlayers; i++)
    {
        newone->players[i] = players[i + startIndex];
    }
    return newone;
} // finish task3 but memory leak?

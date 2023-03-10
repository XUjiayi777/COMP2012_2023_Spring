#include "player.h"
#include "swiss.h"
#include "match.h"

// list is a static-allocated data member of Swiss, so you should not use new
// or delete for this data member
Swiss::Swiss(const int numRounds, const PlayerList &list)
{
    this->numRounds = numRounds;
    curRound = 0;
    this->list = list;
    this->list.sort();
}

Swiss::~Swiss() {} // finish task5

void Swiss::play()
{
    for (curRound = 1; curRound <= numRounds; curRound++)
    {
        int num_scores = 2 * curRound - 1;
        PlayerList *required_list = new PlayerList[num_scores];
        int i = 0;

        for (int j = 0; j < list.getNumPlayers(); j++)
        {
            required_list[num_scores - 1 - (list.getPlayer(j))->getScore()].addPlayer(list.getPlayer(j));
        }
        for (int k = 0; k < num_scores; k++)
        {
            if (required_list[k].getNumPlayers() != 0)
            {
                required_list[k].sort();

                int mid_index = required_list[k].getNumPlayers() / 2;
                for (int l = 0; l < mid_index; l++)
                {
                    Match match = Match(required_list[k].getPlayer(l), required_list[k].getPlayer(l + mid_index));
                    match.play();
                }
                if (required_list[k].getNumPlayers() % 2 == 1)
                {
                    if (k != num_scores - 1)
                    {
                        required_list[k + 1].addPlayer(required_list[k].getPlayer(required_list[k].getNumPlayers() - 1));
                        required_list[k + 1].sort();
                    }
                    else
                    {
                        required_list[k].getPlayer(required_list[k].getNumPlayers() - 1)->addScore(2);
                    }
                }
            }
        }
        delete[] required_list;
        list.sort();
        printLeaderboard();
    }
}

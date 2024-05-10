#pragma once
#include <vector>
#include <unordered_map>
#include "../brain/brain.h"
#include "../game/game.h"

class Tournament {
    private:
    // Variables
    std::vector<Brain*> players;
    int number_rounds;
    int games_per_match = 3;

    // Methods
    bool match(Brain* player1, Brain* player2);

    public:
    // Constructors and Destructor
    Tournament(std::vector<Brain*> t_players);
    ~Tournament() {
        for(long unsigned int i = 0; i < players.size(); i++) {
            /* This implementations may have issues due to the copying of the player vector.
            It shouldn't, though, because the players themselves are by reference, so they should remember score resets.
            */
            players[i]->reset_score();
        }
    }

    // Methods
    void runTournament();
    std::vector<Brain*> getPlayers() { return players; }
};

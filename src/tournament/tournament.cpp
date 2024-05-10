#include "tournament.h"
#include <algorithm>

Tournament::Tournament(std::vector<Brain*> t_players) {
    players = t_players; // Get the roster
    number_rounds = 9; // This number was chosen arbitrarily and can be changed
    std::cout << "New tournament started." << std::endl;
}

bool Tournament::match(Brain* player1, Brain* player2) {
    // std::cout << "New match started between " << player1->getName() << " and " << player2->getName() << "." << std::endl;
    int score = 0;
    for(int i = 0; i < games_per_match; i++) {
        Game* game = new Game(player1, player2);
        if(game->playGame()) {
            ++score;
        }
        else {
            --score;
        }
        delete game;
    }
    // std::cout << ((score >= 0) ? player1->getName() : player2->getName()) << " won the match!" << std::endl;
    return score >= 0;
}

/* This method implements a Swiss tournament and returns the final podium positions
This is not technically a Swiss, because you can have the same opponent twice
*/
void Tournament::runTournament() {
    for(int i = 0; i < number_rounds; i++) { // Each round of the tournament
        for(long unsigned int j = 0; j < players.size(); j += 2) { // Each game of the tournament
            if(match(players[j], players[j+1])) {
                players[j]->increment_score();
            }
            else {
                players[j+1]->increment_score();
            }
        }
        // Re-sort the vector of players for the new round (or for the final standings)
        std::sort(players.begin(), players.end(), [this](const Brain *player1, const Brain *player2) {return player1->getScore() > player2->getScore();});
    }
}

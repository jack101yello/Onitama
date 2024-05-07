#include <iostream>
#include <algorithm>
#include "game/game.h"
#include "brain/brain.h"
#include "card/card.h"

struct match {
    inline bool operator() (Brain *player1, Brain *player2) {
        std::cout << "New match started between " << player1->getName() << " and " << player2->getName() << "." << std::endl;
        int score = 0;
        int rounds = 5;
        for(int i = 0; i < rounds; i++) {
            Game* game = new Game(player1, player2);
            if(game->playGame()) {
                ++score;
            }
            else {
                --score;
            }
            delete game;
            std::cout << "The score is: " << score << std::endl;
        }
        std::cout << ((score >= 0) ? player1->getName() : player2->getName()) << " won the match!" << std::endl;
        return score >= 0;
    }
};

int main() {
    srand(time(0));
    std::vector<Brain*> players;
    players.push_back(new Brain("Jack"));
    players.push_back(new Brain("Nate"));
    // players.push_back(new Brain("Roman J. Israel, Esquire."));
    // players.push_back(new Brain("Bobby Tables"));

    std::sort(players.begin(), players.end(), match());

    std::cout << "The winners are: " << std::endl;
    for(long unsigned int i = 0; i < players.size(); i++) {
        std::cout << i+1 << ". " << players[i]->getName() << std::endl;
    }

    for(int i = players.size(); i >= 0; i--) {
        delete players[i];
    }

    return 0;
}

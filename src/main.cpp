#include <iostream>
#include <algorithm>
#include "game/game.h"
#include "brain/brain.h"
#include "card/card.h"

struct match {
    inline bool operator() (Brain *player1, Brain *player2) {
        int score = 0;
        int rounds = 3;
        for(int i = 0; i < rounds; i++) {
            Game* game = new Game(player1, player2);
            (game->playGame()) ? ++score : --score; // Insane syntax
            delete game;
        }
        return score >= 0;
    }
};


int main() {
    std::vector<Brain*> players;
    players.push_back(new Brain("Jack"));
    players.push_back(new Brain("Nate"));
    players.push_back(new Brain("Roman J. Israel, Esquire."));
    players.push_back(new Brain("Bobby Tables"));

    std::sort(players.begin(), players.end(), match());

    std::cout << "The winners are: " << std::endl;
    for(long unsigned int i = 0; i < players.size(); i++) {
        std::cout << i << ". " << players[i]->getName() << std::endl;
    }

    for(int i = players.size(); i >= 0; i--) {
        delete players[i];
    }

    return 0;
}

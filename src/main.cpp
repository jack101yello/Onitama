#include <iostream>
#include <algorithm>
#include "game/game.h"
#include "brain/brain.h"
#include "card/card.h"
#include "tournament/tournament.h"

std::string getNameFromIndex(int index) {
    std::string name = "";
    do {
        name += (char) (index%26 + 97);
        index /= 26;
    }
    while(index != 0);
    return name;
}

int main() {
    srand(time(0));
    std::vector<Brain*> players;
    for(int i = 0; i < 100; i++) {
        players.push_back(new Brain(getNameFromIndex(i)));
    }

    Tournament *swiss = new Tournament(players);

    swiss->runTournament();
    std::vector<Brain*> winners = swiss->getPlayers();

    std::cout << "The final rankings are: " << std::endl;
    for(long unsigned int i = 0; i < winners.size(); i++) {
        std::cout << i+1 << ". " << winners[i]->getName() << std::endl;
    }

    for(int i = players.size(); i >= 0; i--) {
        delete players[i];
    }

    delete swiss;

    return 0;
}

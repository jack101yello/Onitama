#include <iostream>
#include "game/game.h"
#include "brain/brain.h"

int main() {

    Brain *Jack = new Brain();
    Brain *Nate = new Brain();

    Game game(Jack, Nate);

    game.playGame();

    delete Jack;
    delete Nate;

    return 0;
}
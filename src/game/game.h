#pragma once

#include "../brain/brain.h"
#include "../board/board.h"
#include "../card/card.h"

class Game {
    private:
    // Variables
    Board *board;
    Brain *player1;
    Brain *player2;

    const int maximum_turns = 40;

    // Methods
    bool checkGameOver();
    bool playRound(bool turn, int turn_number); // Constituent for playGame()

    public:
    // Constructors and Destructor
    Game(Brain *t_player1, Brain *t_player2);
    ~Game() {
        delete board;
        player1->reset();
        player2->reset();
    }

    // Methods
    bool playGame(); // Return winner (true for 1, false for 2)
};
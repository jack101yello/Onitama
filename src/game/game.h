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

    // Methods
    bool checkGameOver();
    bool playRound(bool turn); // Constituent for playGame()

    public:
    // Constructors and Destructor
    Game(Brain *t_player1, Brain *t_player2): player1(t_player1), player2(t_player2) { board = new Board(t_player1, t_player2); }
    ~Game() { delete board; }
    bool playGame(); // Return winner (true for 1, false for 2)

    // Methods
};
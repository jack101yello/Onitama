#pragma once

#include "../brain/brain.h"
#include "../card/card.h"

class Game {
    private:
    // Variables
    Brain *player1;
    Brain *player2;
    std::pair<Card*, Card*> p1cards;
    std::pair<Card*, Card*> p2cards;
    Card* neutralcard;
    const int maximum_turns = 100;

    // Methods
    bool checkGameOver();
    bool playRound(bool turn, int turn_number); // Constituent for playGame()
    void generate_deck(std::vector<Card*> deck);

    public:
    // Constructors and Destructor
    Game(Brain *t_player1, Brain *t_player2);
    ~Game() {
        player1->reset();
        player2->reset();
    }

    // Methods
    bool playGame(); // Return winner (true for 1, false for 2)
    void show(); // Display the board
};
#pragma once

#include "../piece/piece.h"
#include "../card/card.h"
#include <vector>
#include <array>
#include <utility>

class Board {
    private:
    // Variables
    std::vector<Piece> p1pieces;
    std::vector<Piece> p2pieces;
    std::vector<Card> p1cards;
    std::vector<Card> p2cards;
    Card neutralcard;
    char **boardstate;
    std::vector<Card> deck;
    void generate_deck();

    // Methods
    void drawcards();

    public:
    // Constructor and Destructor
    Board();
    ~Board() {
        if(boardstate != nullptr) {
            for(int i = 0; i < 5; i++) {
                delete[] boardstate[i];
            }
            delete[] boardstate;
        }
    }

    // Methods
    void show();
    void updateboard(std::pair<int, int> start, std::pair<int, int> end);
};
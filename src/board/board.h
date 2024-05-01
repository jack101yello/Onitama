#pragma once

#include "../card/card.h"
#include <vector>
#include <array>
#include <utility>

class Board {
    private:
    // Variables
    std::pair<Card,Card> p1cards;
    std::pair<Card,Card> p2cards;
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
    std::pair<Card,Card> getP1Cards() const { return p1cards; }
    std::pair<Card,Card> getP2cards() const { return p2cards; }
    Card getNeutralCard() const { return neutralcard; }
};
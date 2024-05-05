#pragma once

#include "../card/card.h"
#include <vector>
#include <array>
#include <utility>
#include "../brain/brain.h"

class Board {
    private:
    // Variables
    std::pair<Card*,Card*> p1cards;
    std::pair<Card*,Card*> p2cards;
    Card* neutralcard;
    char **boardstate;
    std::vector<Card*> deck;
    void generate_deck();
    void shuffle_deck();
    Brain *player1;
    Brain *player2;

    // Methods
    void drawcards();

    public:
    // Constructor and Destructor
    Board(Brain *player1, Brain *player2);
    ~Board() {
        if(boardstate != nullptr) {
            for(int i = 0; i < 5; i++) {
                delete[] boardstate[i];
            }
            delete[] boardstate;
        }
        for(int i = deck.size()-1; i >= 0; i--) {
            delete deck.at(i);
        }
    }

    // Methods
    void show();
    void updateboard();
    std::pair<Card*,Card*> getP1Cards() const { return p1cards; }
    std::pair<Card*,Card*> getP2cards() const { return p2cards; }
    Card* getNeutralCard() const { return neutralcard; }
    void setP1Cards(Card* card1, Card* card2) {
        p1cards.first = card1;
        p1cards.second = card2;
    }
    void setP2Cards(Card* card1, Card* card2) {
        p2cards.first = card1;
        p2cards.second = card2;
    }
    void setNeutralCard(Card* card) {
        neutralcard = card;
    }

    char getBoardstateAt(int x, int y) { return boardstate[x][y]; }
};
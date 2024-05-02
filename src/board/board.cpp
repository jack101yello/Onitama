#include "board.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Start a new game
Board::Board() {
    std::cout << "//> Creating new board." << std::endl;
    // Initial board layout
    boardstate = new char*[5];
    boardstate[0] = new char[5] {'o', 'o', 'O', 'o', 'o'};
    boardstate[1] = new char[5] {' ', ' ', ' ', ' ', ' '};
    boardstate[2] = new char[5] {' ', ' ', ' ', ' ', ' '};
    boardstate[3] = new char[5] {' ', ' ', ' ', ' ', ' '};
    boardstate[4] = new char[5] {'x', 'x', 'X', 'x', 'x'};

    generate_deck(); // Instantiate all of the cards in the deck
    drawcards(); // Draw the cards for the game
}

// Print the current board state
void Board::show() {
    for(int i = 0; i < 5; i++) {
        std::cout << "|";
        for(int j = 0; j < 5; j++) {
            std::cout << boardstate[i][j] << "|";
        }
        std::cout << std::endl;
    }
}

bool randsort(const Card &a, const Card &b) {
    (void)a;
    (void)b;
    srand(time(NULL));
    return rand() % 2 == 0;
}

// Draw cards from the deck to initiate the game
void Board::drawcards() {
    std::cout << "//> Shuffling the deck and dealing the cards." << std::endl;
    std::sort(deck.begin(), deck.end(), randsort);

    p1cards.first = deck.at(0);
    p2cards.first = deck.at(1);
    p1cards.second = deck.at(2);
    p2cards.second = deck.at(3);
    neutralcard = deck.at(4);
}

// Move a piece from start to end
void Board::updateboard(std::pair<int,int> start, std::pair<int,int> end) {
    boardstate[end.first][end.second] = boardstate[start.first][start.second];
    boardstate[start.first][start.second] = ' ';
}

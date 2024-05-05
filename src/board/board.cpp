#include "board.h"
#include <algorithm>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Start a new game
Board::Board(Brain *t_player1, Brain *t_player2) {
    player1 = t_player1;
    player2 = t_player2;

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
    std::cout << "-----------" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "|";
        for(int j = 0; j < 5; j++) {
            std::cout << boardstate[i][j] << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

void Board::shuffle_deck() {
    srand(time(0));
    for(long unsigned int i = 0; i < deck.size(); i++) {
        long unsigned int r = i + (rand() % (deck.size() - i));
        iter_swap(deck.begin() + i, deck.begin() + r);
    }
}

// Draw cards from the deck to initiate the game
void Board::drawcards() {
    std::cout << "//> Shuffling the deck and dealing the cards." << std::endl;
    shuffle_deck();

    p1cards.first = deck.at(0);
    p2cards.first = deck.at(1);
    p1cards.second = deck.at(2);
    p2cards.second = deck.at(3);
    neutralcard = deck.at(4);
}

// Move a piece from start to end
void Board::updateboard() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            boardstate[i][j] = ' ';
        }
    }
    boardstate[4 - player1->getPiecePosition(0).second][4 - player1->getPiecePosition(0).first] = 'X';
    boardstate[player2->getPiecePosition(0).second][player2->getPiecePosition(0).first] = 'O';
    for(int i = 1; i < 5; i++) {
        boardstate[4 - player1->getPiecePosition(i).second][4 - player1->getPiecePosition(i).first] = 'x';
        boardstate[player2->getPiecePosition(i).second][player2->getPiecePosition(i).first] = 'o';
    }
}

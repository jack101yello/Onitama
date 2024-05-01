#include <iostream>
#include "board/board.h"
#include "brain/brain.h"

int main() {

    Board board;
    Brain opponent;

    opponent.setCardStates(board.getP1Cards(), board.getP2cards(), board.getNeutralCard());

    std::cout << "You have: " << board.getP2cards().first.getName() << " and " << 
        board.getP2cards().second.getName() << std::endl;
    std::cout << "The computer has: " << board.getP1Cards().first.getName() << " and " <<
        board.getP1Cards().second.getName() << std::endl;
    std::cout << "The neutral card is: " << board.getNeutralCard().getName() << std::endl;

    std::cout << "Your opponent will now make a move:" << std::endl;

    opponent.getMove();

    return 0;
}
#include "game.h"
#include <vector>

Game::Game(Brain *t_player1, Brain *t_player2) {
    player1 = t_player1;
    player2 = t_player2;
    board = new Board(t_player1, t_player2);
    std::cout << "New game started between " << player1->getName() << " and " << player2->getName() << "." << std::endl;
}

bool Game::playGame() {
    board->show();

    // Tell the players what cards they have
    player1->setCardStates(board->getP1Cards(), board->getP2cards(), board->getNeutralCard());
    player2->setCardStates(board->getP2cards(), board->getP1Cards(), board->getNeutralCard());

    // return playRound(board->getNeutralCard()->getBoxColor());
    return playRound(true, 1);
}

bool Game::playRound(bool turn, int turn_number) {
    // This redefinition prevents us from making too many if statements
    Brain *currentplayer;
    Brain *otherplayer;
    if(turn) { // Player 1's turn
        currentplayer = player1;
        otherplayer = player2;
    }
    else { // Player 2's turn
        currentplayer = player2;
        otherplayer = player1;
    }
    
    // Decide what move to make
    std::vector<int> move_formatted = currentplayer->getMove();

    std::pair<int,int> delta = (std::pair<int,int>) {move_formatted.at(1) - currentplayer->getPiecePosition(move_formatted.at(0)).first, move_formatted.at(2) - currentplayer->getPiecePosition(move_formatted.at(0)).second};


    currentplayer->move(true, move_formatted.at(0), delta);
    otherplayer->move(false, move_formatted.at(0), delta);
    
    // Update cards
    // We need to find which card was played
    Card* chosencard;
    Card* othercard;
    if(currentplayer->getCards().first->getIndex() == move_formatted.at(3)) { // Check if the left card was played
        chosencard = currentplayer->getCards().first;
        othercard = currentplayer->getCards().second;
    }
    else { // The right card was played
        chosencard = currentplayer->getCards().second;
        othercard = currentplayer->getCards().first;
    }
    currentplayer->setCardStates((std::pair<Card*,Card*>) {othercard, board->getNeutralCard()}, otherplayer->getCards(), chosencard);
    currentplayer->setCards(othercard, board->getNeutralCard());
    otherplayer->setCardStates(otherplayer->getCards(), (std::pair<Card*,Card*>) {othercard, board->getNeutralCard()}, chosencard);

    // Update board
    if(turn) {
        board->setP1Cards(othercard, board->getNeutralCard());
    }
    else {
        board->setP2Cards(othercard, board->getNeutralCard());
    }
    board->setNeutralCard(chosencard);

    // Handle captures
    for(int i = 0; i <= 4; i++) {
        /* We have to subtract from four to take into account the fact that the two brains see inverted coordinates
        */
        if(4 - otherplayer->getPiecePosition(i).first == currentplayer->getPiecePosition(move_formatted.at(0)).first
        && 4 - otherplayer->getPiecePosition(i).second == currentplayer->getPiecePosition(move_formatted.at(0)).second) {
            otherplayer->kill_piece(i);
            break; // No need to check the other pieces
        }
    }

    board->updateboard();
    board->show();

    std::cout << "Player 1 says that the pieces have positions:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "(" << player1->getPiecePosition(i).first << ", " << player1->getPiecePosition(i).second << ")" << std::endl;
    }
    std::cout << "Player 2 says that the pieces have positions:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "(" << player2->getPiecePosition(i).first << ", " << player2->getPiecePosition(i).second << ")" << std::endl;
    }

    // See if the game is over
    if(checkGameOver()) {
        if(turn) {
            std::cout << player1->getName() << " won!" << std::endl;
        }
        else {
            std::cout << player2->getName() << " won!" << std::endl;
        }
        return turn; // You can only win on your own turn, so we know who won if there's a winning position
    }
    else if(turn_number >= maximum_turns) {
        return true; // The game has lasted too long, so we're just calling a winner to end it, preventing an infinite game. Inelegant, but necessary.
    }
    else {
        /* If the game isn't over, then we continue with the other player's turn.
        I agree that it's insane to make this recursive, but why not? I think this
        is a clever little piece of code.
        */
        return !playRound(!turn, turn_number+1);
    }
}

bool Game::checkGameOver() {
    // Check the gates
    if(player1->getPiecePosition(0).first == 2 && player1->getPiecePosition(0).second == 4) {
        return true;
    }
    if(player2->getPiecePosition(0).first == 2 && player1->getPiecePosition(0).second == 4) {
        return true;
    }

    // Check the big guys
    if(player1->getPiecePosition(0).first == -1 || player2->getPiecePosition(0).second == -1) {
        return true;
    }
    
    return false; // Neither win condition is currently met.
}

#include "game.h"
#include <vector>

Game::Game(Brain *t_player1, Brain *t_player2) {
    // Create the players
    player1 = t_player1;
    player2 = t_player2;

    // Create deck
    std::vector<Card*> deck;
    std::vector<std::pair<int,int>> ox_moves = {{0,1},{1,0},{0,-1}};
    deck.push_back(new Card("Ox", ox_moves, false, 0));
    
    std::vector<std::pair<int,int>> crab_moves = {{2,0},{0,1},{-2,0}};
    deck.push_back(new Card("Crab", crab_moves, false, 1));
    
    std::vector<std::pair<int,int>> horse_moves = {{-1,0},{0,1},{0,-1}};
    deck.push_back(new Card("Horse", horse_moves, true, 2));
    
    std::vector<std::pair<int,int>> cobra_moves = {{-1,0},{1,1},{1,-1}};
    deck.push_back(new Card("Cobra", cobra_moves, true, 3));
    
    std::vector<std::pair<int,int>> rabbit_moves = {{-1,-1},{1,1},{2,0}};
    deck.push_back(new Card("Rabbit", rabbit_moves, false, 4));
    
    std::vector<std::pair<int,int>> dragon_moves = {{-2,1},{2,1},{-1,-1},{1,-1}};
    deck.push_back(new Card("Dragon", dragon_moves, true, 5));
    
    std::vector<std::pair<int,int>> elephant_moves = {{-1,0},{-1,1},{1,0},{1,1}};
    deck.push_back(new Card("Elephant", elephant_moves, true, 6));
    
    std::vector<std::pair<int,int>> eel_moves = {{-1,1},{-1,-1},{1,0}};
    deck.push_back(new Card("Eel", eel_moves, false, 7));
    
    std::vector<std::pair<int,int>> rooster_moves = {{-1,-1},{-1,0},{1,1},{1,0}};
    deck.push_back(new Card("Rooster", rooster_moves, true, 8));
    
    std::vector<std::pair<int,int>> goose_moves = {{-1,1},{-1,0},{1,0},{1,-1}};
    deck.push_back(new Card("Goose", goose_moves, false, 9));
    
    std::vector<std::pair<int,int>> crane_moves = {{-1,-1},{0,1},{1,-1}};
    deck.push_back(new Card("Crane", crane_moves, false, 10));
    
    std::vector<std::pair<int,int>> boar_moves = {{-1,0},{0,1},{1,0}};
    deck.push_back(new Card("Boar", boar_moves, true, 11));
    
    std::vector<std::pair<int,int>> ant_moves = {{-1,1},{1,1},{0,-1}};
    deck.push_back(new Card("Ant", ant_moves, true, 12));
    
    std::vector<std::pair<int,int>> monkey_moves = {{-1,-1},{1,-1},{-1,1},{1,1}};
    deck.push_back(new Card("Monkey", monkey_moves, false, 13));
    
    std::vector<std::pair<int,int>> frog_moves = {{-2,0},{-1,1},{1,-1}};
    deck.push_back(new Card("Frog", frog_moves, true, 14));
    
    std::vector<std::pair<int,int>> tiger_moves = {{0,2},{0,-1}};
    deck.push_back(new Card("Tiger", tiger_moves, false, 15));
    for(long unsigned int i = 0; i < deck.size(); i++) { // Shuffle
        long unsigned int r = i + (rand() % (deck.size() - i));
        iter_swap(deck.begin() + i, deck.begin() + r);
    }
    // Deal cards
    p1cards.first = deck[0];
    p2cards.first = deck[1];
    p1cards.second = deck[2];
    p2cards.second = deck[3];
    neutralcard = deck[4];

    std::cout << "New game started between " << player1->getName() << " and " << player2->getName() << "." << std::endl;
}

void Game::show() {
    char boardstate[5][5] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };
    boardstate[4 - player1->getPiecePosition(0).first][4 - player1->getPiecePosition(0).second] = 'X';
    boardstate[player2->getPiecePosition(0).first][player2->getPiecePosition(0).second] = 'O';
    for(int i = 1; i < 5; i++) {
        if(player1->getPiecePosition(i).first != -1) { // The piece is living
            boardstate[4 - player1->getPiecePosition(i).first][4 - player1->getPiecePosition(i).second] = 'x';
        }
        if(player2->getPiecePosition(i).first != -1) { // The piece is living
            boardstate[player2->getPiecePosition(i).first][player2->getPiecePosition(i).second] = 'o';
        }
    }
    std::cout << "-----------" << std::endl;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            std::cout << "|" << boardstate[j][i];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

bool Game::playGame() {
    // show();

    // Tell the players what cards they have
    player1->setCardStates(p1cards, p2cards, neutralcard);
    player2->setCardStates(p2cards, p1cards, neutralcard);

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
    currentplayer->setCardStates((std::pair<Card*,Card*>) {othercard, neutralcard}, otherplayer->getCards(), chosencard);
    currentplayer->setCards(othercard, neutralcard);
    otherplayer->setCardStates(otherplayer->getCards(), (std::pair<Card*,Card*>) {othercard, neutralcard}, chosencard);

    // Update cards
    if(turn) {
        p1cards.first = othercard;
        p1cards.second = neutralcard;
    }
    else {
        p2cards.first = othercard;
        p2cards.second = neutralcard;
    }
    neutralcard = chosencard;

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

    // show();

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
    else if(turn_number >= maximum_turns) { // The game has lasted too long, so we're just calling a winner to end it, preventing an infinite game. Inelegant, but necessary.
        std::cout << "Time out!" << std::endl;
        if(rand()%2 == 0) {
            std::cout << player1->getName() << " won by virtue of coin toss." << std::endl;
            return true;
        }
        else {
            std::cout << player2->getName() << " won by virtue of coin toss." << std::endl;
            return false;
        }
    }
    else {
        /* If the game isn't over, then we continue with the other player's turn.
        I agree that it's insane to make this recursive, but why not? I think this
        is a clever little piece of code.
        */
        return playRound(!turn, turn_number+1);
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

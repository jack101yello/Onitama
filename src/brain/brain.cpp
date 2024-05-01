#include "brain.h"

// This is the default constructor, for the first generation
Brain::Brain() {
    cardstates = new bool[80];
    for(int i = 0; i < 80; i++) {
        cardstates[i] = false;
    }
    mypiecepositions = {{2, 0}, {0, 0}, {1, 0}, {3, 0}, {4, 0}};
    theirpiecepositions = {{2, 4}, {0, 4}, {1, 4}, {3, 4}, {4, 4}};

    // Create the transition matrices
    transition_matrix1 = new int*[input_size];
    for(int i = 0; i < input_size; i++) {
        transition_matrix1[i] = new int[internal_layer_size];
    }
    transition_matrix2 = new int*[150];
    for(int i = 0; i < internal_layer_size; i++) {
        transition_matrix2[i] = new int[output_size];
    }

    // Populate the transition matrices
    for(int i = 0; i < input_size; i++) {
        for(int j = 0; j < internal_layer_size; j++) {
            transition_matrix1[i][j] = 0.5; // In future, make random
        }
    }
    for(int i = 0; i < internal_layer_size; i++) {
        for(int j = 0; j < output_size; j++) {
            transition_matrix2[i][j] = 0.5; // In future, make random
        }
    }
}

// This is for asexual reproduction of new brains
Brain::Brain(const Brain &parent) {
    cardstates = new bool[80];
    for(int i = 0; i < 80; i++) {
        cardstates[i] = false;
    }
    mypiecepositions = {{2, 0}, {0, 0}, {1, 0}, {3, 0}, {4, 0}};
    theirpiecepositions = {{2, 4}, {0, 4}, {1, 4}, {3, 4}, {4, 4}};

    // Create the transition matrices
    transition_matrix1 = new int*[input_size];
    for(int i = 0; i < input_size; i++) {
        transition_matrix1[i] = new int[internal_layer_size];
    }
    transition_matrix2 = new int*[150];
    for(int i = 0; i < internal_layer_size; i++) {
        transition_matrix2[i] = new int[output_size];
    }

    // Populate the transition matrices
    for(int i = 0; i < input_size; i++) {
        for(int j = 0; j < internal_layer_size; j++) {
            transition_matrix1[i][j] = 0.5; // In future, get from parent
        }
    }
    for(int i = 0; i < internal_layer_size; i++) {
        for(int j = 0; j < output_size; j++) {
            transition_matrix2[i][j] = 0.5; // In future, get from parent
        }
    }
}

void Brain::setCardStates(const std::pair<Card,Card> &t_myCards, const std::pair<Card,Card> &theirCards, const Card &neutralCard) {
    cardstates[t_myCards.first.getIndex()] = true;
    cardstates[t_myCards.second.getIndex() + 16] = true;
    cardstates[theirCards.first.getIndex() + 32] = true;
    cardstates[theirCards.second.getIndex() + 48] = true;
    cardstates[neutralCard.getIndex() + 64] = true;
    MyCards.first = t_myCards.first;
    MyCards.second = t_myCards.second;
}

/*
Returns the best legal move in the format:
{Piece number, x change, y change}
*/
std::vector<int> Brain::getMove() {
    std::cout << "/// Finding optimal move..." << std::endl;
    int *input_layer = new int[input_size]; // A vector codifying the board state

    // Populate the input_layer vector
    const int card_input_size = 80;
    for(int i = 0; i < card_input_size; i++) { // Consider the card states
        input_layer[i] = (cardstates[i]) ? 1 : 0;
    }
    for(int i = 0; i < mypiecepositions.size(); i++) { // Consider my pieces
        /* Adding 1 here is in order to avoid the issues of pieces with position 0
        being removed on account of the input counting as a 0, causing it not to
        be included in the computation, when in reality it should be counted equally
        as the rest.
        There is fear of rightward bias in this, as a position of 3 is counted as
        triple the input of a position of 1, in this implementation. Further testing
        is required in order to determine if this is an issue, but it should be
        looked into in future.
        */
        input_layer[card_input_size + i*2] = mypiecepositions.at(i).first + 1;
        input_layer[card_input_size + i*2 + 1] = mypiecepositions.at(i).second + 1;
    }
    for(int i = 0; i < theirpiecepositions.size(); i++) { // Consider their pieces
        input_layer[card_input_size + mypiecepositions.size() + i*2] = theirpiecepositions.at(i).first + 1;
        input_layer[card_input_size + mypiecepositions.size() + i*2 + 1] = theirpiecepositions.at(i).second + 1;
    }

    // Compute the internal layer
    /* There is a question of whether to include more internal layers. This is something
     to be looked into in future. At the moment only one is used, but most models would
     likely suggest at least two. This should be looked into in future.
    */
    int *internal_layer = new int[internal_layer_size];
    for(int i = 0; i < internal_layer_size; i++) {
        int count = 0;
        for(int j = 0; j < input_size; j++) {
            count += input_layer[j] * transition_matrix1[j][i]; // Is this the correct index ordering? If segfault, no.
        }
        internal_layer[i] = count;
    }

    // Compute the output layer
    int *output_layer = new int[output_size];
    for(int i = 0; i < output_size; i++) {
        int count = 0;
        for(int j = 0; j < internal_layer_size; j++) {
            count += internal_layer[j] * transition_matrix2[j][i];
        }
        output_layer[i] = count;
    }

    // Find the optimal legal move
    int optimal_move = 0;
    int max_weight = 0;
    for(int i = 0; i < output_size; i++) {
        if(output_layer[i] < max_weight) {
            continue;
        }
        if(isLegalMove(getPieceFromIndex(i), getMoveFromIndex(i))) {
            optimal_move = i;
            max_weight = output_layer[i];
        }
    }

    // Clean up the memory usage
    delete[] input_layer;
    delete[] internal_layer;
    delete[] output_layer;

    // Convert the data to the proper output format
    std::vector<int> output = (std::vector<int>) {getPieceFromIndex(optimal_move), getMoveFromIndex(optimal_move).first, getMoveFromIndex(optimal_move).second};
    
    std::cout << "/// I want to move piece #" << output[0] << " " << output[1] <<
        " spaces right and " << output[2] << " spaces up." << std::endl;

    return output;
}

// Returns the move corresponding to a given output index
std::pair<int,int> Brain::getMoveFromIndex(int index) {
    int comp = index%11;
    switch(comp) {
        case 0: return (std::pair<int,int>) {-1,1};
        case 1: return (std::pair<int,int>) {0,1};
        case 2: return (std::pair<int,int>) {1,1};
        case 3: return (std::pair<int,int>) {1,0};
        case 4: return (std::pair<int,int>) {1,-1};
        case 5: return (std::pair<int,int>) {0,-1};
        case 6: return (std::pair<int,int>) {-1,-1};
        case 7: return (std::pair<int,int>) {-1,0};
        case 8: return (std::pair<int,int>) {-2,0};
        case 9: return (std::pair<int,int>) {2,0};
        case 10: return (std::pair<int,int>) {0,2};
        default: return (std::pair<int,int>) {0,0}; // This should never happen
    }
}

bool Brain::isLegalMove(int piecenumber, std::pair<int,int> move) {
    std::cout << "/// can I move piece #" << piecenumber << " " << move.first <<
        " spaces right and " << move.second << " spaces up?" << std::endl;

    int newx = mypiecepositions.at(piecenumber).first + move.first;
    int newy = mypiecepositions.at(piecenumber).second + move.second;

    // Check if the move is on the board
    if(newx < 0 || newx > 4 || newy < 0 || newy > 4) {
        std::cout << "/// No, because it would leave the board." << std::endl;
        return false;
    }

    // Check if the move intersects a piece of ours
    for(int i = 0; i < mypiecepositions.size(); i++) {
        if(i == piecenumber) { // We don't care about intersecting ourselves
            continue;
        }

        if(mypiecepositions.at(i).first == newx && mypiecepositions.at(i).second == newy) {
            std::cout << "/// No, because it would intersect piece #" << i << std::endl;
            return false;
        }
    }

    // Check if the move is on a card that we hold
    for(int i = 0; i < MyCards.first.getMoves().size(); i++) { // Check first card
        if(move.first == MyCards.first.getMoves().at(i).first &&
        move.second == MyCards.first.getMoves().at(i).second) {
            std::cout << "/// Yes, because I have the " << MyCards.first.getName() << std::endl;
            return true; // We found that move on the first card!
        }
    }
    for(int i = 0; i < MyCards.second.getMoves().size(); i++) {
        if(move.first == MyCards.second.getMoves().at(i).first &&
        move.second == MyCards.second.getMoves().at(i).second) {
            std::cout << "/// Yes, because I have the " << MyCards.second.getName() << std::endl;
            return true; // We found that move on the second card!
        }
    }
    std::cout << "/// No, because I do not have any cards with that move." << std::endl;
    return false; // We don't have a card with that move
}

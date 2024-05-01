#include <vector>
#include <utility>
#include "../card/card.h"

class Brain {
    private:
    // Variables
    bool *cardstates; // Nodes for each card state
    std::pair<Card,Card> MyCards;
    std::vector<std::pair<int,int>> mypiecepositions;
    std::vector<std::pair<int,int>> theirpiecepositions;
    int **transition_matrix1;
    int **transition_matrix2;
    static const int input_size = 100;
    static const int internal_layer_size = 150;
    static const int output_size = 55;

    // Methods
    bool isLegalMove(int piecenumber, std::pair<int,int> move);
    int getPieceFromIndex(int index) { return index/11; }
    std::pair<int,int> getMoveFromIndex(int index);

    public:
    // Constructors and Descructor
    Brain();
    Brain(const Brain &parent);
    ~Brain() {
        for(int i = 0; i < input_size; i++) {
            delete[] transition_matrix1[i];
        }
        delete[] transition_matrix1;
        for(int i = 0; i < internal_layer_size; i++) {
            delete[] transition_matrix2[i];
        }
        delete[] transition_matrix2;
    }

    // Methods
    void setCardStates(const Card &myfirst, const Card &mysecond, const Card &theirfirst, const Card &theirsecond);
    std::vector<int> getMove();
};
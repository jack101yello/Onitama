#include "card.h"
#include "../board/board.h"

void Board::generate_deck() {
    std::vector<std::pair<int,int>> ox_moves = {{0,1},{1,0},{0,-1}};
    deck.push_back(Card("Ox", ox_moves, false));
    
    std::vector<std::pair<int,int>> crab_moves = {{2,0},{0,1},{-2,0}};
    deck.push_back(Card("Crab", crab_moves, false));
    
    std::vector<std::pair<int,int>> horse_moves = {{-1,0},{0,1},{0,-1}};
    deck.push_back(Card("Horse", horse_moves, true));
    
    std::vector<std::pair<int,int>> cobra_moves = {{-1,0},{1,1},{1,-1}};
    deck.push_back(Card("Corba", cobra_moves, true));
    
    std::vector<std::pair<int,int>> rabbit_moves = {{-1,-1},{1,1},{2,0}};
    deck.push_back(Card("Rabbit", rabbit_moves, false));
    
    std::vector<std::pair<int,int>> dragon_moves = {{-2,1},{2,1},{-1,-1},{1,-1}};
    deck.push_back(Card("Dragon", dragon_moves, true));
    
    std::vector<std::pair<int,int>> elephant_moves = {{-1,0},{-1,1},{1,0},{1,1}};
    deck.push_back(Card("Elephant", elephant_moves, true));
    
    std::vector<std::pair<int,int>> eel_moves = {{-1,1},{-1,-1},{1,0}};
    deck.push_back(Card("Eel", eel_moves, false));
    
    std::vector<std::pair<int,int>> rooster_moves = {{-1,-1},{-1,0},{1,1},{1,0}};
    deck.push_back(Card("Rooster", rooster_moves, true));
    
    std::vector<std::pair<int,int>> goose_moves = {{-1,1},{-1,0},{1,0},{1,-1}};
    deck.push_back(Card("Goose", goose_moves, false));
    
    std::vector<std::pair<int,int>> crane_moves = {{-1,-1},{0,1},{1,-1}};
    deck.push_back(Card("Crane", crane_moves, false));
    
    std::vector<std::pair<int,int>> boar_moves = {{-1,0},{0,1},{1,0}};
    deck.push_back(Card("Boar", boar_moves, true));
    
    std::vector<std::pair<int,int>> ant_moves = {{-1,1},{1,1},{0,-1}};
    deck.push_back(Card("Ant", ant_moves, true));
    
    std::vector<std::pair<int,int>> monkey_moves = {{-1,-1},{1,-1},{-1,1},{1,1}};
    deck.push_back(Card("Monkey", monkey_moves, false));
    
    std::vector<std::pair<int,int>> frog_moves = {{-2,0},{-1,1},{1,-1}};
    deck.push_back(Card("Frog", frog_moves, true));
    
    std::vector<std::pair<int,int>> tiger_moves = {{0,2},{0,-1}};
    deck.push_back(Card("Tiger", tiger_moves, false));
}

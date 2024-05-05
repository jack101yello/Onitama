#include "card.h"
#include "../board/board.h"

void Board::generate_deck() {
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
}

std::string CardNameFromIndex(int index) {
    switch(index) {
        case 0: return "Ox";
        case 1: return "Crab";
        case 2: return "Horse";
        case 3: return "Cobra";
        case 4: return "Rabbit";
        case 5: return "Dragon";
        case 6: return "Elephant";
        case 7: return "Eel";
        case 8: return "Rooster";
        case 9: return "Goose";
        case 10: return "Crane";
        case 11: return "Boar";
        case 12: return "Ant";
        case 13: return "Monkey";
        case 14: return "Frog";
        case 15: return "Tiger";
        default: return "No Card Found";
    }
}

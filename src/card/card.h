#pragma once

#include <iostream>
#include <vector>
#include <utility>

class Card {
    private:
    std::string name;
    bool boxcolor;
    std::vector<std::pair<int,int>> moves;

    public:
    Card() {};
    Card(std::string t_name, std::vector<std::pair<int,int>> t_moves, bool t_boxcolor): 
        name(t_name), moves(t_moves), boxcolor(t_boxcolor) {};
    
    std::string getName() { return name; }
    bool getBoxColor() { return boxcolor; }
    std::vector<std::pair<int,int>> getMoves() { return moves; }
};

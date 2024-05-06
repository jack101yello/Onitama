#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <iostream>

class Card {
    private:
    // Variables
    std::string name;
    bool boxcolor;
    std::vector<std::pair<int,int>> moves;
    int index;

    public:
    // Constructors and Destructor
    Card() {};
    Card(std::string t_name, std::vector<std::pair<int,int>> t_moves, bool t_boxcolor, int t_index): 
        name(t_name), boxcolor(t_boxcolor), moves(t_moves), index(t_index) {};
    
    // Methods
    std::string getName() const { return name; }
    bool getBoxColor() const { return boxcolor; }
    std::vector<std::pair<int,int>> getMoves() const { return moves; }
    int getIndex() const { return index; }
    void show();
};

std::string CardNameFromIndex(int index);

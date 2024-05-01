#pragma once

class Piece {
    private:
    int *pos;
    bool side;

    public:
    Piece(int *t_pos = nullptr, bool t_side = false): pos(t_pos), side(t_side) {}
    int getX() { return pos[0]; }
    int getY() { return pos[1]; }
    bool getSide() { return side; }
};
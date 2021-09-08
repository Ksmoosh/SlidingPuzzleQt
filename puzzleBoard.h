#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <iostream>
#include <vector>
#include "square.h"

class Square;

class PuzzleBoard
{
public:
    PuzzleBoard();
    ~PuzzleBoard();

    PuzzleBoard(int size);

    std::vector<int> get_movables() const;
    int get_position_of_blank();
    int get_size();
    int get_dim_size();

    void set_position_of_blank(int const &newBlank);
    void set_movables(std::vector<int> movables);

    bool is_movable(int &position);
    std::vector<Square> randomBoard;
private:
    std::vector<int> movables;
    int blank_position;
    int size;
    int dim_size;
};

#endif // PUZZLEBOARD_H

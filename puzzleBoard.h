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

    explicit PuzzleBoard(int size);

    int const get_row_of_blank(std::vector<int> &randomBoard);
    int const get_position_of_blank();
    int const get_size();
    bool is_movable(int &position);
    std::vector<int> get_movables() const;
    void set_position_of_blank(int const &newBlank);
    void set_movables();

    std::vector<int> movables;
    int blank_position;
    int size;
    int dim_size;


    std::vector<Square> randomBoard;
};

#endif // PUZZLEBOARD_H

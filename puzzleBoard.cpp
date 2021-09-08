#include "puzzleBoard.h"

#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <stdexcept>

using namespace std;

PuzzleBoard::PuzzleBoard() {};

PuzzleBoard::~PuzzleBoard() {};

PuzzleBoard::PuzzleBoard(int side) : size(side * side), dim_size(side)
{
    this->randomBoard = vector<Square>(this->size);
};

int PuzzleBoard::get_dim_size()
{
    return this->dim_size;
}

int PuzzleBoard::get_size()
{
    return this->size;
}

int PuzzleBoard::get_position_of_blank()
{
    for(int i = 0; i < this->size; i++)
    {
        if(this->randomBoard[i].get_id() == 0)
        {
            return i;
        }
    }
    throw domain_error("Blank square not found!");
}

std::vector<int> PuzzleBoard::get_movables() const
{
    return this->movables;
}

void PuzzleBoard::set_position_of_blank(int const &newBlank)
{
    this->blank_position = newBlank;
}

bool PuzzleBoard::is_movable(int &position)
{
    for(int i=0; i<this->movables.size(); i++)
    {
        if(position == this->movables[i])
            return true;
    }
    return false;
}

void PuzzleBoard::set_movables(std::vector<int> movables)
{
    this->movables = movables;
}

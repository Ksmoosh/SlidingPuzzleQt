#include "puzzle.h"

#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <stdexcept>

using namespace std;

Puzzle::Puzzle(int size) : size(size)
{
    this->puzzleBoard = PuzzleBoard(size);
    this->num_moves = 0;
};

/**
 * Count the number of linear inversions in the vector
*/
int Puzzle::number_of_inversions(vector<int> &puzzleIntBoard)
{
    int inversions = 0;
    for(int i = 0; i < puzzleIntBoard.size() - 1; i++)
    {
        for(int j = i + 1; j < puzzleIntBoard.size(); j++)
        {
            if(puzzleIntBoard[i] && puzzleIntBoard[j] && puzzleIntBoard[i] > puzzleIntBoard[j])
                inversions++;
        }
    }
    return inversions;
}

/**
 * Get the row where the blank square is, counted from the bottom row up
*/
int const Puzzle::get_row_of_blank(vector<int> &puzzleIntBoard)
{
    int size = sqrt(puzzleIntBoard.size());
    int row = size;
    for(int i = 0; i < puzzleIntBoard.size(); i++)
    {
        if(!puzzleIntBoard[i])
            return row;
        if((i + 1) % size == 0) {
            row--;
        }
    }
    return row;
}

/**
 * A randomly generated board is valid only under some conditions
*/
bool Puzzle::valid_board(vector<int> &puzzleIntBoard)
{
    if(puzzleIntBoard.size() % 2 == 1)
        return number_of_inversions(puzzleIntBoard) % 2 == 0;
    else
        return (get_row_of_blank(puzzleIntBoard) % 2 == 0 && number_of_inversions(puzzleIntBoard) % 2 == 1) ||
                (get_row_of_blank(puzzleIntBoard) % 2 == 1 && number_of_inversions(puzzleIntBoard) % 2 == 0);
}

void Puzzle::create_random_int_board(vector<int> &puzzleIntBoard)
{
    srand(time(NULL));
    unsigned seed = rand() % 1000;

    int count = 0;
    for(int i = 0; i < puzzleIntBoard.size(); i++)
    {
        puzzleIntBoard[i] = i;
    }

    do{
        count++;
        shuffle(puzzleIntBoard.begin(), puzzleIntBoard.end(), default_random_engine(seed));
    } while(!valid_board(puzzleIntBoard));
}

void Puzzle::random_board_to_squares(PuzzleBoard &puzzleBoard, vector<int> &puzzleIntBoard)
{
    int size = puzzleBoard.get_size();
    for(int i = 0; i < size; i++)
    {
        puzzleBoard.randomBoard[i] = Square(puzzleIntBoard[i], i, size);
    }
}

void Puzzle::setup_board()
{
    vector<int> randomInts(this->puzzleBoard.get_size());

    create_random_int_board(randomInts);
    random_board_to_squares(this->puzzleBoard, randomInts);
    set_position_of_blank(get_position_of_blank());
    set_movables();
    print_board(this->puzzleBoard);
}

void Puzzle::print_board(PuzzleBoard &puzzleBoard)
{
    cout << "Current board:\n";
    for(int i = 0; i < puzzleBoard.get_size(); i++)
    {
        Square square = puzzleBoard.randomBoard[i];
        cout << left << setw(4) << square.get_id();
        if((i + 1) % puzzleBoard.get_dim_size() == 0) {
            cout << "\n";
        }
    }
    cout << "Solved? " << puzzleSolved(puzzleBoard);
}

int const Puzzle::get_position_of_blank(PuzzleBoard &puzzleBoard)
{
    for(int i = 0; i < puzzleBoard.get_size(); i++)
    {
        if(puzzleBoard.randomBoard[i].get_id() == 0)
        {
            return i;
        }
    }
    throw domain_error("Blank square not found!");
}

int const Puzzle::get_position_of_blank()
{
    return get_position_of_blank(this->puzzleBoard);
}

PuzzleBoard Puzzle::get_puzzleBoard() const
{
    return this->puzzleBoard;
}

std::vector<int> const Puzzle::get_movables()
{
    return this->puzzleBoard.get_movables();
}

void Puzzle::set_position_of_blank(PuzzleBoard &puzzleBoard, int const &newBlank)
{
    puzzleBoard.set_position_of_blank(newBlank);
}

void Puzzle::set_position_of_blank(int const &newBlank)
{
    set_position_of_blank(this->puzzleBoard, newBlank);
}

void Puzzle::set_movables(PuzzleBoard &puzzleBoard)
{
    std::vector<int> movables;
    for(int i = 0; i < puzzleBoard.get_size(); i++)
    {
        if(is_neighbouring_blank(puzzleBoard, i))
        {
            movables.push_back(i);
        }
    }
    puzzleBoard.set_movables(movables);
}

void Puzzle::set_movables()
{
    set_movables(this->puzzleBoard);
}

bool Puzzle::is_neighbouring_blank(PuzzleBoard &puzzleBoard, int const &position)
{
    /*
    This function checks if the square is neighbouring a blank square,
    which means, that this square can be swapped with the blank square.
    A square can be called a neighbour, if it is either directly above
    or below the blank square, or is right next to it, while on the same row.
    */
    if (abs(position - puzzleBoard.get_position_of_blank()) == puzzleBoard.get_dim_size()) return true;
    else if (abs(position - puzzleBoard.get_position_of_blank()) == 1 && position / puzzleBoard.get_dim_size() == puzzleBoard.get_position_of_blank() / puzzleBoard.get_dim_size()) return true;
    return false;
}

bool Puzzle::switchSquares(PuzzleBoard &puzzleBoard, int &squarePosition)
{
    if(is_neighbouring_blank(puzzleBoard, squarePosition))
    {
        puzzleBoard.randomBoard[puzzleBoard.get_position_of_blank()].set_id(puzzleBoard.randomBoard[squarePosition].get_id());
        puzzleBoard.randomBoard[squarePosition].set_id(0);
        set_position_of_blank(puzzleBoard, squarePosition);
        return true;
    }
    return false;
};

bool Puzzle::puzzleSolved(PuzzleBoard puzzleBoard)
{
    for(int i = 0; i < puzzleBoard.get_size(); i++)
    {
        if(!puzzleBoard.randomBoard[i].goal_position())
            return false;
    }
    return true;
}

int Puzzle::get_num_moves()
{
    return this->num_moves;
}

void Puzzle::increaseNumMoves()
{
    this->num_moves += 1;
}

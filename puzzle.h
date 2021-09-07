#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <vector>
#include "square.h"
#include "puzzleBoard.h"


class Puzzle
{
public:
    explicit Puzzle(int size);

    void set_position_of_blank(PuzzleBoard &puzzleBoard, int const &newBlank);
    void set_position_of_blank(int const &newBlank);
    void set_movables(PuzzleBoard &puzzleBoard);
    void set_movables();
    void setup_board();

    int const get_row_of_blank(std::vector<int> &puzzleIntBoard);
    int const get_position_of_blank();
    int const get_position_of_blank(PuzzleBoard const &puzzleBoard);
    PuzzleBoard get_puzzleBoard() const;
    std::vector<int> const get_movables();
    std::vector<int> const get_movables(PuzzleBoard &puzzleBoard);

    int number_of_inversions(std::vector<int> &puzzleIntBoard);
    bool is_neighbouring_blank(PuzzleBoard &puzzleBoard, int const &position);
    bool is_movable(PuzzleBoard &puzzleBoard, int &position);
    bool valid_board(std::vector<int> &puzzleIntBoard);
    bool switchSquares(PuzzleBoard &puzzleBoard, int &squarePosition);
    bool puzzleSolved(PuzzleBoard puzzleBoard);
    void create_random_int_board(std::vector<int> &puzzleIntBoard);
    void random_board_to_squares(PuzzleBoard &puzzleBoard, std::vector<int> &puzzleIntBoard);

    //test
    void print_board(PuzzleBoard const &puzzleBoard);
    PuzzleBoard puzzleBoard;

private:
    int size;
    int num_elems;
    int blank_position;
    std::vector<int> movables;
};

#endif // PUZZLE_H

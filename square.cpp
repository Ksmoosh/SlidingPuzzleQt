
#include "square.h"

Square::Square() {};

Square::~Square() {};

Square::Square(int id, int position, int num_squares) : id(id), position(position), num_squares(num_squares) {};

int Square::get_id() const
{
    return this->id;
}

int Square::get_position()
{
    return this->position;
}

bool Square::goal_position()
{
    if(this->id == 0)
        return this->position == this->num_squares - 1;
    return this->position + 1 == this->id;
}

void Square::set_position(int position)
{
    this->position = position;
}

void Square::set_id(int id)
{
    this->id = id;
}

#ifndef SQUARE_H
#define SQUARE_H

class Square
{
public:
    Square();
    ~Square();

    explicit Square(int id, int position, int num_squares);

    int get_id() const;
    int get_position();
    bool goal_position();
    void set_position(int position);
    void set_id(int id);

private:
    int id;
    int position;
    int num_squares;
};

#endif // SQUARE_H

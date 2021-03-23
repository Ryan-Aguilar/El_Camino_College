#ifndef ROBOT_H
#define ROBOT_H
class Arena;

class Robot
{
public:
    // Constructor
    Robot(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;

    // Mutators
    void move();
    bool takeDamageAndLive();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    // TODO: You'll probably find that a robot object needs an additional
    // data member to support your implementation of the behavior affected
    // by being hit and taking damage.
    int Strikes = 0;
    bool iswall(int Row, int Col, Arena* m_arena);
};
#endif
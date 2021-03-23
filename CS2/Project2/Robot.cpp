#include "Robot.h"
#include "Arena.h"
#include <iostream>
using namespace std;


Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const //done
{
    // TODO: TRIVIAL:  Return what column the robot is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

void Robot::move() // done
{
    // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
    case UP:
        if (m_row > 1)
        {
            m_row = m_row - 1;
        }
        // TODO:  Move the robot up one row if possible.
        break;
    case DOWN:
        if (m_row < m_arena->rows())
        {
            m_row = m_row + 1;
        }
        break;
    case LEFT:
        if (m_col > 1)
        {
            m_col = m_col - 1;
        }
        break;
    case RIGHT:
        if (m_col < m_arena->cols())
        {
            m_col = m_col + 1;
        }
        break;
        // TODO:  Implement the other movements.
    }
}

bool Robot::takeDamageAndLive() // done 
{

    // TODO:  If the robot has been hit once before, return false (since a
    // second hit kills a robot).  Otherwise, return true (since the robot
    // survived the damage).
    Strikes = Strikes + 1;
    return Strikes < 2;
}
bool Robot::iswall(int Row, int Col, Arena* m_arena)
{
    if (Row > m_arena->rows() || Col < 0 || Row < 0 || Col > m_arena->cols())
    {
        return true;
    }

    return false;
}
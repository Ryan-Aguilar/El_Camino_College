#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Arena.h"


using namespace std;

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const // done
{
    // TODO: TRIVIAL:  Return what row the player is at.
    // Delete the following line and replace it with the correct code.
    return m_row;  // This implementation compiles, but is incorrect.
}

int Player::col() const // done
{
    // TODO: TRIVIAL:  Return what column the player is at.
    // Delete the following line and replace it with the correct code.
    return m_col;  // This implementation compiles, but is incorrect.
}

int Player::age() const // done
{
    // TODO:  TRIVIAL:  Return the player's age.
    // Delete the following line and replace it with the correct code.
    return m_age;  // This implementation compiles, but is incorrect.
}

string Player::takeComputerChosenTurn()
{
    // TODO:  Replace this implementation:
    // Your replacement implementation should do something intelligent
    // and return a string that describes what happened.  When you've
    // decided what action to take, take it by calling move, shoot, or stand.
    // This function must return one of the following four strings:
    //     "Moved."
    //     "Shot and hit!"
    //     "Shot and missed!"
    //     "Stood."

    // the way we determine the danger level is that we first realize that the player and robot move at the same time. so we then started to take into consideration about the
    // robots positions. we looked at where they were standing and if the robot was right next to me. then believe it or not, it is the safest option for me to move to because there is no walls near us. 
    // so we know if there is a wall and if a robot attempts to move to a wall, then it stands. but we are saying there is no wall and we are right next to a robot. 
    // well we can determine which direction where to run into because the computer should choose the direction with the spot that has the least robots. so it has less robots to catch the player.
     // danger lv is determined by how many robots are around the position in terms of up down left and right.

    int RunningLowestDangerLV = DangerLvCount(m_row, m_col, m_arena); // this is for the current position of where the player is at.


    string Direction = "Current";

    if (!iswall(m_row, m_col - 1, m_arena) && DangerLvCount(m_row, m_col - 1, m_arena) < RunningLowestDangerLV)
    {
        RunningLowestDangerLV = DangerLvCount(m_row, m_col - 1, m_arena);
        Direction = "LEFT";
    }
    if (!iswall(m_row, m_col + 1, m_arena) && DangerLvCount(m_row, m_col + 1, m_arena) < RunningLowestDangerLV)
    {
        RunningLowestDangerLV = DangerLvCount(m_row, m_col + 1, m_arena);
        Direction = "RIGHT";
    }
    if (!iswall(m_row - 1, m_col, m_arena) && DangerLvCount(m_row - 1, m_col, m_arena) < RunningLowestDangerLV)
    {
        RunningLowestDangerLV = DangerLvCount(m_row - 1, m_col, m_arena);
        Direction = "UP";
    }
    if (!iswall(m_row + 1, m_col, m_arena) && DangerLvCount(m_row + 1, m_col, m_arena) < RunningLowestDangerLV)
    {
        RunningLowestDangerLV = DangerLvCount(m_row + 1, m_col, m_arena);
        Direction = "DOWN";
    }
    if (Direction == "LEFT")
    {
        move(LEFT);
        return "Moved.";
    }
    if (Direction == "RIGHT")
    {
        move(RIGHT);
        return "Moved.";
    }
    if (Direction == "UP")
    {
        move(UP);
        return "Moved.";
    }
    if (Direction == "DOWN")
    {
        move(DOWN);
        return "Moved.";
    }
    // need to do bounderies for movement
    // need to do something if a robot is at a wall. the edge case.
    int shootDirection = -1;
    int Maxrobots = 0;
    int RobotCounter = 0;

    if (Direction == "Current")
    {
        for (int i = 2; i < 6; i++)
        {

            /*if (m_row + i == m_arena->rows())
            {

            }*/
            if (!iswall(m_row - i, m_col, m_arena))
            {
                RobotCounter = m_arena->nRobotsAt(m_row - i, m_col);
                if (RobotCounter > Maxrobots)
                {
                    shootDirection = UP;
                }
            }

            if (!iswall(m_row + i, m_col, m_arena))
            {
                RobotCounter = m_arena->nRobotsAt(m_row + i, m_col);
                if (RobotCounter > Maxrobots)
                {
                    shootDirection = DOWN;
                }
            }
            if (!iswall(m_row, m_col + i, m_arena))
            {
                RobotCounter = m_arena->nRobotsAt(m_row, m_col + i);
                if (RobotCounter > Maxrobots)
                {
                    shootDirection = RIGHT;
                }
            }
            if (!iswall(m_row, m_col - i, m_arena))
            {
                RobotCounter = m_arena->nRobotsAt(m_row, m_col - i);
                if (RobotCounter > Maxrobots)
                {
                    shootDirection = LEFT;
                }
            }
            if (shootDirection != -1)
            {
                if (shoot(shootDirection) == true)
                {
                    return "Shot and hit!";
                }
                else
                {
                    return "Shot and missed!";
                }
                break;
            }




        }

    }
    // these 4 if statements compare the danger levels up, down, left and right of the players direction. We also made a string variable so It can hold the direction. I assume
    // I assume that this string variable we just made called direction is doing to play essential...  Come back to this train of thought.
    // we call the move function now with the newly added direction variable and pass that into parameters as it too is also





    // Here's one possible strategy:
    //   If moving in some direction would put me in less immediate danger
    //     than standing, then move in that direction.
    //   else shoot in the direction of the nearest robot I can hit.

    // A more aggressive strategy is possible, where you hunt down robots.
    stand();
    return "Stood";
}


// here in this function I need to know the rows and colums in term of position, so I can detect the amount of robots around that spot.
// so to aproach this is that we look at the spot we are given and onlt look at spots around it. 
int Player::DangerLvCount(int row, int col, Arena* m_arena)
{
    int count = m_arena->nRobotsAt(row - 1, col) + // up
        m_arena->nRobotsAt(row + 1, col) + // down
        m_arena->nRobotsAt(row, col - 1) + // left
        m_arena->nRobotsAt(row, col + 1); // right

    return count;

}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir) // done
{
    m_age++;
    switch (dir)
    {

    case UP:
        if (m_row > 1)
        {
            m_row = m_row - 1;
        }
        /*if (m_row < 0)
        {
            m_row = 0;
        }*/
        break;

    case DOWN:
        if (m_row < m_arena->rows()) // m arenrow is arena size. I make the arean size minus one in this condition so I never go out of bounds.
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
    }
}

bool Player::shoot(int dir) // DONE
{
    m_age++;

    if (rand() % 3 == 0)// miss with 1/3 probability
        return false;
    switch (dir)
    {
        // R EQUALS MY PLAYERS CURRENT ROW. IF SAY 25X25 IS THE SIZE GIVEN. THEN IN THE MIDDLE CONDITION OF THE FOR LOOP. IS 24 < 24? NO.
        // BUT SAY THE PLAYER FOR SOME REASON STILL WANT TO SHOOT UP. THEN WE CAN AVOID THAT BY PUTIING AN EQUALS SIGN.
    case UP: // works
        for (int r = m_row - 1; r >= 0 && r >= m_row - 5; r--)
        {
            // IF MY PLAYERS CURRENT ROW HAS A ROBOT INFRONT OF HIM AND IT IS WITHIN 5 SPACES AHEAD FROM WHERE THE PLAYER IS, THEN WE LET THE PLAYER SHOOT.
            // BUT THE PLAYERS bullet can only travel 5 spaces.

            // I WANT TO CHECK IF THERE IS A ROBOT WITH IN THE RANGE I JUST MADE IN MY FOR LOOP FOR THE PLAYER TO DETECT. SO HOW CAN YOU ACCESS A ROBOTS ROWS? 

                    // m_arena->nRobotsAt(r, m_col) >= 1 && m_arena->nRobotsAt(r, m_col) <= 5
         // I want to call my nRobots at function and see if the robot is 5 spaces with in that function. 
            // I call my nRobotsAt function passing my r because I am looking to see if it is there and my colums stay the same. so then from the nRobotsAt computation retuns a 0 then I
            // do not even bother to shoot. 
            // but if there is more than 0 robots, then I do shoot.

            if (m_arena->nRobotsAt(r, m_col) == 0)
            {

            }
            else
            {
                m_arena->damageRobotAt(r, m_col);
                return true;
            }
        }
        return false;
        break;
    case DOWN:
        for (int r = m_row + 1; r < m_arena->rows() && r <= m_row + 5; r++)
        {

            if (m_arena->nRobotsAt(r, m_col) == 0)
            {

            }
            else
            {
                m_arena->damageRobotAt(r, m_col);
                return true;

            }
        }
        return false;
        break;
    case RIGHT:
        for (int r = m_col + 1; r < m_arena->cols() && r <= m_col + 5; r++)
        {

            if (m_arena->nRobotsAt(m_row, r) == 0)
            {

            }
            else
            {
                m_arena->damageRobotAt(m_row, r);
                return true;
            }
        }
        return false;
        break;
    case LEFT:
        for (int r = m_col - 1; r >= 0 && r >= m_col - 5; r--)
        {

            if (m_arena->nRobotsAt(m_row, r) == 0)
            {

            }
            else
            {
                m_arena->damageRobotAt(m_row, r);
                return true;
            }
        }
        return false;
        break;


    }
    // TODO:  Damage the nearest robot in direction dir, returning
    // true if a robot is hit and damaged, false if not hit.
    return false;  // This implementation compiles, but is incorrect.
}


bool Player::isDead() const // done
{

    // TODO:  TRIVIAL:  Return whether the player is dead.
    // This implementation compiles, but is incorrect.

    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

bool Player::iswall(int Row, int Col, Arena* m_arena)
{
    if (Row > m_arena->rows() || Col < 1 || Row < 1 || Col > m_arena->cols())
    {
        return true;
    }

    return false;
}

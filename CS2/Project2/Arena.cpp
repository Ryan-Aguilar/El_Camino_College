#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Arena.h"
#include "Player.h"
#include "Robot.h"

using namespace std;



Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
    m_robots[MAXROBOTS];
}

Arena::~Arena() // done, but may need to revisit.
{
    for (int g = 0; g < MAXROBOTS; g++)
    {
        if (m_robots[g] != nullptr)
        {
            delete m_robots[g];
        }
    }
    delete m_player;
    // TODO:  Delete the player and all remaining dynamically allocated robots.
}

int Arena::rows() const // done
{
    // TODO:  TRIVIAL:  Return the number of rows in the arena.
    // Delete the following line and replace it with the correct code.
    return m_rows;  // This implementation compiles, but is incorrect.
}

int Arena::cols() const // done
{
    // TODO:  TRIVIAL:  Return the number of columns in the arena.
    // Delete the following line and replace it with the correct code.
    return m_cols;  // This implementation compiles, but is incorrect.
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const // done
{
    // TODO:  Return the number of robots at row r, column c.
    int n = 0;
    for (int z = 0; z < m_nRobots; z++)
    {
        if (m_robots[z]->row() == r && m_robots[z]->col() == c)
        {
            n++;
        }
    }
    return n;  // This implementation compiles, but is incorrect.
}

void Arena::display(string msg) const // Done
{
    // Position (row,col) in the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';


    // done. Have someone review to verify the logic and you Ryan have to explain it to them.
    // Indicate each robot's position

  // TODO:  If one robot is at some grid point, set the char to 'R'.
  //        If it's 2 though 8, set it to '2' through '8'.
  //        For 9 or more, set it to '9'.

    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
        {
            if (nRobotsAt(r + 1, c + 1) == 1)
            {
                grid[r][c] = 'R';
            }

            if (nRobotsAt(r + 1, c + 1) >= 2 && nRobotsAt(r + 1, c + 1) <= 8)
            {
                grid[r][c] = static_cast <char> (48 + (nRobotsAt(r + 1, c + 1))); // ask the professor.
            }

            if (nRobotsAt(r + 1, c + 1) >= 9)
            {
                grid[r][c] = '9';
            }
        }
    }

    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a robot there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c) // done
{
    if (m_nRobots == MAXROBOTS)
    {
        return false;
    }

    Robot* R = new Robot(this, r, c);
    m_robots[m_nRobots] = R;

    m_nRobots++;
    // If MAXROBOTS have already been added, return false.  Otherwise,
    // dynamically allocate a new robot at coordinates (r,c).  Save the
    // pointer to the newly allocated robot and return true.

    // TODO:  Implement this.
    return true;  // This implementation compiles, but is incorrect.
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c) // done 
{
    for (int i = 0; i < m_nRobots; i++)
    {
        if (m_robots[i]->row() == r && m_robots[i]->col() == c)
        {
            // Ryan How can we attack a robot? What class do I have access to? well I do recall I have a function in the robots cpp that is takedamageandlive.
            // well that function returns true if robot is dead. Oh so I can have an if statement that validates the boolean to be true and makes the robot die.
            // but when we kill that robot in the array we need to delete that specific robot. I believe if i delete that robot in the robot array i will have a memory leak because The pointer was pointing to what was once there. 
            // well we could make that pointer point to a null pointer and it willnot cause any memory leaks for now. Lets ask the professor what his thoughts of this approach is. 
            // now we can delete the robot by putting the array name with the for loop index and place delete before it. that way it does delete the robot. 
            if (m_robots[i]->takeDamageAndLive() == false)
            {
                delete m_robots[i];
                m_nRobots--;
                for (int j = i; j < MAXROBOTS - 1; j++)
                {
                    m_robots[j] = m_robots[j + 1];
                }

                // Ryans todo: I feel as if i am not done so now that i deleted the robot its gone, but that also means i have to reduce the number of robots.
                // I cannot reduce MAXROBOTS because that is a constant and constant remain the same. so that means i have to reduce the variable m_nRobots.
                // I need the professor to see if I have any memory leaks.
            }
        }
    }
    // TODO:  Damage one robot at row r, column c if at least one is there.
    // If the robot does not survive the damage, destroy it.
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {

        // THINK RYAN.

        // so how does this section go? well we know the robot makes its own moves, so we should make it move on its own. so in a way it is random. 
        // this function also states if the robot is at the same spot as the player, then it will also kill the player as well. 

        // I think I can reference back to my maze code that I did to find a path if it was a valid spot or not. copy that over Ryan.
        // how did you know if it was safe for the pogram in the maze to procede over too the next spot? Well I had a set of conditions that said
        // if I did not run into these specific chaacters, then we may proceed to move on.

        // OHH SO WE CAN COMPARE THE COORDINATES OF THE PLAYER AND THE ROBOTS TO SEE IF THEY ARE THE SAME. IN THAT CASE WE CAN DETERMINE I THEY ARE IN THE SAME PSOT.
        // THUS IF THEY ARE THE SAME THEN WE DO RETURN THE PLAYER IS DEAD LIKE THE TODO DISCRIPTION ASKS.
        /*
        bool pathPresent(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec && maze[sr][sc] == '.')
    {
        return true;
    }


            if (maze[sr][sc] == '@' || maze[sr][sc] == 'X' || maze[sr][sc] == 'V')
            {
                return false;
            }
                if (maze[sr][sc] == '.')
                {
                    maze[sr][sc] = 'V';

                    if (pathPresent(maze, nRows, nCols, sr - 1, sc, er, ec))
                    {
                        return true;
                    }
                        if (pathPresent(maze, nRows, nCols, sr + 1, sc, er, ec))
                        {
                            return true;
                        }
                        if (pathPresent(maze, nRows, nCols, sr, sc - 1, er, ec))
                        {
                            return true;
                        }
                            if (pathPresent(maze, nRows, nCols, sr, sc + 1, er, ec))
                            {
                                return true;
                            }

                                return false;
                }
    return false;

}
        */

        // TODO:  Have the k-th robot in the arena make one move.
        //        If that move results in that robot being in the same
        //        position as the player, the player dies.
        m_robots[k]->move();

        if (m_robots[k]->row() == m_player->row() && m_robots[k]->col() == m_player->col())
        {
            m_player->setDead();

        }
        // why is it giving an error on M_player if it is defined? I included the proper files. the other two do not have erd lines under the variables.
        // lets get back to it after we try to figure out that robot makes its own move.

        // WHAT ARE THE ROBOTS OPTIONS IN TERMS OF MOVING? WELL THEY CAN GO UP, DOWN, LEFT OR RIGHT.
        // WAIT. i BELIEVE I CAN MAKE THE ROBOT MOVE IF I HAVE ITS MOVE CALCULATED FROM THE MOVE FUNCTION I MADE IN THE ROBOT.CPP FILE CALLED ROBOT::MOVE().
        // OKAY AND I CAN MAKE THAT ONE ROBOT MOVE. it has to be a specific robot though? well it can be the one K value is. so we can make that robot move.
        // WE ALSO HAVE TO RETUN THE POSSIBILITY OF THE PLAYER NOT BEING DEAD. SO WE CN ACTUALLY RETURN THE PLAYER NOT BEING DEAD AND WE CAN DO THAT BY PUTTING
        // AN ! BEFORE THE VARIABLE BECAUSE IT IS A BOOL FUNTION AND WHEN YOU PUT AN ! MARK BEFORE A VARIABLE, IT MEANS IT IS FALSE.

        // HAVE SOMEONE REVISE THIS RYAN.
    }

    return !m_player->isDead();
}


bool Arena::iswall(int Row, int Col, Arena* m_arena)
{
    if (Row > m_rows || Col < 0 || Row < 0 || Col > m_cols)
    {
        return true;
    }

    return false;
}
// main.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;



/////////////////////////////////////////////////////////////////////////////
////  main()
/////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
int main()
{
    // Initialize the random number generator.  (You don't need to
    // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(9, 9, 1);

    // Play the game
    g.play();
}

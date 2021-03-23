#include <iostream>
#include <ctime>
using namespace std;

// Polymorphic classes
const int MAXGUESS = 1000;  // range is [0,MAXGUESS]
bool checkForWin(int guess, int answer);

class Player {
private:


public:
    int virtual getGuess() = 0;
    void updateHighLow(bool tooHigh, int guess)
    {

        //if (Answer > guess && guess > low)
        if (tooHigh && (guess < high))
        {
            high = guess;
        }
        //if (Answer < guess && guess < high)
        else if (!tooHigh && (guess > low))
        {
            low = guess;
        }
    }
    // same as private except inherited classes can see it.
protected:

    int high = 1000;
    int low = 0;
    int guess;
    /*int Answer = secretnumber;*/

};

class HumanPlayer : public Player {
private:

public:



    // this is where we shall start to see if we are going good.
    int virtual getGuess()
    {

        /*cout << "Player 1's turn to guess. " << endl;*/
        cout << "Guess a number: ";
        cin >> guess;



        // this should only update necessarily though if the guess is closer to the answer.

        //if (Answer > guess && guess > low)
        //{
        //    low = guess;
        //}
        //if (Answer < guess && guess < high)
        //{
        //    high = guess;
        //}


        return guess;
    }

};

class ComputerPlayer : public Player {
private:
public:

    int virtual getGuess()
    {


        int number; // we can make a int variable to hold the randomized number

        srand(time(NULL)); // here is where the random number generator comes into play and for this case, we can use the time function
                           // so every number can be be unique. we will not be getting the same number all the time.

        /*cout << "Player 2's turn to guess." << endl;*/
        cout << "The computers guess is ";
        number = (rand() % MAXGUESS) + 1; // this is debateable whether i should add a 1 at the very end because i am not sure if 1000 is included.
        cout << number << endl;

        return number;
    }




};

class SmartComputerPlayer : public ComputerPlayer {
private:

public:
    int virtual getGuess()
    {
        /* his is where the random number generator.
        However, this also cannot just abruptly guess still from 0 to 1000. it should not be like first run. guess is 500.
        the computer says okay too low. the computer should not choose say 21. ti should do "ok the guess is from 0 to 1000.
        lets

        */
        int AiGuess;
        /*cout << "Player 2's turn to guess." << endl;*/
        cout << "The computers guess is ";


        AiGuess = ((high - low) / 2) + low;
        cout << AiGuess << endl;

        //updatehighlow();
        return AiGuess;

    }


};




// You can change this however you want
bool checkForWin(int guess, int answer, Player& player, Player& player2) {
    if (answer == guess) {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess) {
        cout << "Your guess is too high." << endl;
        player.updateHighLow(true, guess);
        player2.updateHighLow(true, guess);
    }
    else {
        cout << "Your guess is too low." << endl;
        player.updateHighLow(false, guess);
        player2.updateHighLow(false, guess);
    }
    return  false;
}



int play(Player& player1, Player& player2) {  // do not change this line
    // change anything you like below this line
    int answer = 0, guess = 0;
    int numGuesses = 0;
    bool win = false;
    int roundelapsed = 1;
    srand(time(NULL));
    answer = (rand() % MAXGUESS) + 1;

    while (!win) {
        cout << "***************- Round " << roundelapsed << " -********************" << endl;
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer, player1, player2);
        if (win) break;

        cout << "\nPlayer 2's turn to guess." << endl;
        guess = player2.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer, player2, player1);
        roundelapsed++;
        cout << endl;
        /*cout << "Rounds passed " << roundelapsed << endl;*/
    }
    cout << "Rounds passed " << roundelapsed - 1 << endl;
    cout << "The number of guess in total is " << numGuesses << endl;
    return numGuesses;
}

int main() {

    // TODO: your code goes here

    /*int guess = 0;

    cout << "Plese enter a number between o and " << MAXGUESS << ": " << endl;*/



    //Write a menu that allows the user to select whether player1 or player2 are human or computer players



    int P1decision;
    int P2decision;

    cout << "Please make a selection for Player 1: " << endl;
    cout << "1. Human Player" << endl;
    cout << "2. Regular Computer Player" << endl;
    cout << "3. Smart Computer Player" << endl;
    cout << "--------------------------" << endl;
    cin >> P1decision;

    while (P1decision < 1 || P1decision > 3)
    {
        cout << "Error! The number you entered was out of range!" << endl;
        cout << "Please enter a number between 1 and 3: " << endl;
        cin >> P1decision;
    }


    cout << "Please make a selection for Player 2: " << endl;
    cout << "1. Human Player" << endl;
    cout << "2. Regular Computer Player" << endl;
    cout << "3. Smart Computer Player" << endl;
    cout << "--------------------------" << endl;
    cin >> P2decision;

    while (P2decision < 1 || P2decision > 3)
    {
        cout << "Error! The number you entered was out of range!" << endl;
        cout << "Please enter a number between 1 and 3: " << endl;
        cin >> P2decision;
    }


    if (P1decision == 1)
    {
        HumanPlayer human;
        if (P2decision == 1)
        {
            HumanPlayer human2;
            play(human, human2);
        }

        if (P2decision == 2)
        {
            ComputerPlayer avgAI2;
            play(human, avgAI2);
        }
        if (P2decision == 3)
        {
            SmartComputerPlayer smrtAI2;
            play(human, smrtAI2);
        }
    }
    else if (P1decision == 2)
    {
        ComputerPlayer avgAI;

        if (P2decision == 1)
        {
            HumanPlayer human2;
            play(avgAI, human2);
        }

        if (P2decision == 2)
        {
            ComputerPlayer avgAI2;
            play(avgAI, avgAI2);
        }
        if (P2decision == 3)
        {
            SmartComputerPlayer smrtAI2;
            play(avgAI, smrtAI2);
        }

    }
    else if (P1decision == 3)
    {
        SmartComputerPlayer smrtAI;

        if (P2decision == 1)
        {
            HumanPlayer human2;
            play(smrtAI, human2);
        }

        if (P2decision == 2)
        {
            ComputerPlayer avgAI2;
            play(smrtAI, avgAI2);
        }
        if (P2decision == 3)
        {
            SmartComputerPlayer smrtAI2;
            play(smrtAI, smrtAI2);
        }

    }

}
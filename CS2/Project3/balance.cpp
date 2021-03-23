#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include<stack>
using namespace std;

void printFile(istream& dictfile)
{
    int LineNumber = 1;
    while (!dictfile.eof())
    {
        string temp = "";
        getline(dictfile, temp);

        cout << LineNumber << " " << temp << endl;
        LineNumber++;
    }
    dictfile.clear();
    dictfile.seekg(0, dictfile.beg);

}

bool MatchOperators(char c, char d)
{
    bool newmatch = false;

    if (c == '(' && d == ')')
    {
        newmatch = true;
    }

    if (c == '[' && d == ']')
    {
        newmatch = true;
    }

    if (c == '{' && d == '}')
    {
        newmatch = true;
    }

    if (c == '\'' && d == '\'')
    {
        newmatch = true;
    }
    if (c == '\"' && d == '\"')
    {
        newmatch = true;
    }

    if (c == 'Y' && d == 'Z') // Y is suppose to represent the openning of the multiline comment. /*
                              // z represents the closing of the multiline comment. */
    {
        newmatch = true;

    }

    //if (c == '/' && d == '*') // openning multi comments we need to bind these two if statements. so this and the one under.
    //{
    //    newmatch = true;
    //}

    //if (c == '*' && d == '/')// closeing multi comments
    //{
    //    newmatch = true;
    //}

    //if (c == '*') // multiplication
    //{
    //    newmatch = true;
    //}

    //if (c == '/' && d == '/') // single comment
    //{
    //    newmatch = true;
    //}
    //if (c == '/') // division 
    //{
    //    newmatch = true;
    //}

    return newmatch;
}

bool balanceFile(istream& dictfile)
{
    stack<char> S;
    stack<int> LineNumber; // this stack is for keeping track of the line number that coordinates with stack s.
    char c;
    char d;
    bool match = true;
    bool inQuotes = false;
    bool Comments = false;
    int Line = 1;
    vector <string> LineCount;

    while (dictfile.peek() != EOF)
    {
        string Temp;
        getline(dictfile, Temp);
        LineCount.push_back(Temp);

    }
    bool blockcomment = false;
    for (Line = 1; Line <= LineCount.size(); Line++)
    {
        string CurrentLine = LineCount[Line - 1];
        for (int I = 0; I < CurrentLine.size(); I++) {

            c = CurrentLine[I];
            if (inQuotes == false)
            {
                if (c == '/' && CurrentLine[I + 1] == '/' && blockcomment == false)
                {
                    break;
                }

                if (c == '/' && CurrentLine[I + 1] == '*' && blockcomment == false)
                {
                    I++;
                    
                        blockcomment = true;
                        S.push('Y'); // reffer to matchoperators function
                        LineNumber.push(Line);
                        continue; // makes it skip the rest of the logic.
                    
                }

                if (c == '*' && CurrentLine[I + 1] == '/')
                {
                    I++;
                    blockcomment = false;
                    c = 'Z';

                    if (S.empty())
                    {
                        match = false;
                        /*cout << "first case" << endl;*/
                        break;
                    }
                    char T = S.top();
                    S.pop();
                    LineNumber.pop();
                    if (!MatchOperators(T, c)) // reffer to matchoperators function
                    {
                        match = false;
                        break;
                    }
                    else
                    {
                        cout << "pair matching /* and */" << endl;
                    }
                }

                else if (blockcomment == true)
                {
                    continue;
                }
            }
            if (inQuotes && c == '\"' || inQuotes && c == '\'')
            {

                if (c == S.top() && (CurrentLine[I - 1] != '\\' || CurrentLine[I - 2] == '\\'))
                {
                    /*cout << S.top() << endl;*/
                    S.pop();
                    LineNumber.pop();
                    inQuotes = false;

                    cout << "pair matching " << c << " and " << c << endl;
                }



            }
            else if (inQuotes) {
                continue;
            }


            /*if (Comments) following a similar approach from how we did inQuotes.
            {
                if (c == S.top())
                {
                    Comments = false;
                    S.pop();
                }

            }*/

            /*else if (c == '/')
            {
                I++;
                char Q = CurrentLine[I];
                if (!MatchOperators(c, Q))
                {
                    match = false;
                    break;
                }
            }*/

            

            else if (c == '(' || c == '{' || c == '[')
            {
                S.push(c);
                LineNumber.push(Line);
            }

            else if (c == ')' || c == '}' || c == ']')
            {
                if (S.empty())
                {
                    match = false;
                    /*cout << "first case" << endl;*/
                    break;
                }

                d = S.top();
                S.pop();
                LineNumber.pop();

                if (!MatchOperators(d, c))
                {
                    match = false;

                    break;
                }
                else
                {

                    cout << "pair matching " << d << " and " << c << endl;
                }


            }
            else if (c == '\'' || c == '\"') //
            {
                S.push(c);
                LineNumber.push(Line);
                inQuotes = true;
            }





        }

        if (match == false)
        {
            break;
        }
        if (inQuotes) { //unfinished line with quote EX: " hello world
            break;
        }
    }


    if (!S.empty() && match == true) // This if statement was to catch an open parenthises mismatch.
    {
        match = false;
        if (S.top() == 'Y') // reffer to matchoperators function
        {
            cout << "unmatched /* symbol on line " << LineNumber.top() << endl;
        }
        else 
        {
         cout << "unmatched " << S.top() << " symbol on line " << LineNumber.top() << endl;
        }
    }
    /* cout << match << endl;*/
    else if (match == false) // this is to catch a closing parenthesis mismatch.
    {
        if (c == 'Z') // reffer to matchoperators function
        {
            cout << "unmatched */ symbol on line " << Line << endl;
        }
        else
        {
            cout << "unmatched " << c << " symbol on line " << Line << endl;
        }
    }
    return match;
}

//inspired by the article you included. I present to you...


int main()
{
    ifstream infile;
    string filename;

    cout << "Please enter filename for C++ code: ";
    cout << endl;
    filename = "parenthstest.txt";
    /*cin >> filename;*/
    infile.open(filename.c_str());

    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }

    printFile(infile);

    if (balanceFile(infile))
        cout << "Balance is ok" << endl;

}


/*create a stack S;
    char c, d;
    int match = TRUE;

    while (there is more expression to read)
    {
        read a character, c;
        if (c is one of '(' or '{' or '[')
            push on to S;
        else if (c is one of ')' or '}' or ']')
        {
            if (the stack S is empty)
            {
                match = FALSE;
                break;
            }
            d = pop from S
                if (!MatchingParens(c, d))
                {
                    match = FALSE;
                    break;
                }
        }
    }
    if (stack S not empty) match = FALSE;
    if (match == TRUE)
        cout << "Parentheses match" << endl;
    else
        cout << "Parentheses do not match" << endl;*/



        //If(c != '(' || c != '[') // case sensitive
        //{
        //    if (c == '*' || c == '/')
        //    {
        //        If(c != '(' || c != '[')
        //    }
        //}
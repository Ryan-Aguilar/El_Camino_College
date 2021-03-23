#include <iostream>
#include <fstream>
#include <istream>
#include <string>
using namespace std;

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

//Prototypes
int loadDictionary(istream& dictfile, string dict[]); //original function 
int LoadDictionaryHelper(istream& dictfile, string dict[], int index);

int permuteRecur(string word, const string dict[], int size, string result[]); // original function

bool Find(int i, string s, const string dict[], int size);
void Filter(int i, int max, string permutations[], int& ri, const string dict[], string result[]);
int permute(string prefix, string rest, const string dict[], int size, string results[], int& resultsindex);
int Loop(int initval, int max, string prefix, string rest, const string dict[], int size, string results[], int i, int& resultsindex);
bool CheckforNoDuplicates(int& resultsindex, string prefix, int z, string results[]);

void printRecur(const string results[], int size); // original function
void printRecurHelper(int i, int size, const string results[]);

int loadDictionary(istream& dictfile, string dict[]) // actual function
{

	return LoadDictionaryHelper(dictfile, dict, 0); // using a templete to convert a for loop into a recursive loop, I have added a helper funtion for loadDictionary so we load each sting into the dictionary array recursively.

	/* Places each string in dictfile into the array dict. Returns the number of words loaded into dict.
	   This number should not be larger than MAXDICTWORDS since that is the size of the array.*/
}

int LoadDictionaryHelper(istream& dictfile, string dict[], int index) // in this function we are loading each string line from the dictionary file into the dictionary array.
																	  // there is only one string per element in the dictionary array.
{
	string str; // we are creating a string variable so it can hold one line of string from the ditionary file.

	if (index == MAXDICTWORDS) // here we are saying if our index is equal to the MAXDICTWORDS then we stop and return nothing. we do not want to exceede MAXDICTWORDS.
	{
		return 0;
	}

	if (dictfile.peek() == EOF) // this if statement is saying when the computer reads the dictfile, it may read everything in the dict file until it hits an EOF. this stands for end of file. 
								// when it reaches the end of the file, it will stop. it stops because there is nothing else to read. 
	{
		return 0;
	}

	if (getline(dictfile, str)) // here we use get line and store the line of string and store it to variable str.
	{
		dict[index] = str; // we want the dict array to hold everything in the dict file has for every line, so we set the dict array the str variable. now we also have a variable called index so it can keep track on where it should be storing the string. 
						   // say the dictionary has the first word dog. well index holds the value zero and in an array we cound from zero. so at index zero, its first word is dog too. when we call the function again, we add one to the index varible so it can store the next string in a new element.
		return 1 + LoadDictionaryHelper(dictfile, dict, index + 1); // we call this function so it increments i and continues until it hits its base cases.
	}


}

int permuteRecur(string word, const string dict[], int size, string results[]) // original function
																			   // Returns the number of words loaded into dict. This number should not be larger than MAXDICTWORDS since that is the size of the array.
{
	int temp = 0;
	return permute("", word, dict, size, results, temp); // here we have a helper function so it may call other helper functions to find all permutations, compare the permutations to the dictionary array to see if the permutations are valid anagrams and delete duplicates. 

}

int permute(string prefix, string rest, const string dict[], int size, string results[], int& resultsindex)
{
	if (rest.size() == 0) // this is a base case that indactes if my rest variable size is equal to zero, then we stop running because there nothing left to process for rest.
	{

		if (Find(0, prefix, dict, size)) // this function is being called so it may do comparisons to find valid anagrams.
		{
			if (resultsindex < MAXRESULTS) // i do not want to have more results than the suggested MAXRESULTS. this is defined as a constant with a value of 20. we cannot have more than 20 results after all the processing is done.
			{
				//call function to check if there are duplicates.
				/*
				if no duplicates, insert the word.
				*/

				if (CheckforNoDuplicates(resultsindex, prefix, 0, results)) // once there was no duplicates found and the function returns true, we are going to set our results arrary to hold the string that was compared to prefix. 
																			// we also increment resultsindex variable for every run because we do not want everything to a single element when there more not being utalized.
				{
					results[resultsindex] = prefix;
					resultsindex++;
				}
			}
		}

	}
	string ogPrefix = prefix;
	string ogRest = rest;
	int initval = 0;
	int maxval = rest.size();
	return Loop(initval, maxval, prefix, rest, dict, size, results, 0, resultsindex); // we make a call to loop so it may find the permutations of the given word the user typed in. that input is stored in the variable called rest. 
}

bool CheckforNoDuplicates(int& resultsindex, string prefix, int z, string results[])
{
	if (z >= resultsindex) // resuults index is a fixed size and we do not want to exceed it. we do not want to go out of scope. 
	{
		return true;
	}
	if (results[z] == prefix) // so we do not have duplicates, we are setting reults array element at index z position to prefix because if there is a word that is equal to the prefix, then we do not want it in the results array.
	{                         // an example is look. if this funtion has the word look and if look is the prefix, then it will not want to include it. thus, being false. we do not want look to appear twice in our results. just once should it appear.
		return false;
	}
	CheckforNoDuplicates(resultsindex, prefix, z + 1, results);
}

int Loop(int initval, int max, string prefix, string rest, const string dict[], int size, string results[], int i, int& resultsindex) // here the permutations are found.
{
	if (i >= max) // this is saying when my index is equal to the size of the sting given, then stop processing and return reultsindex. 
	{
		return resultsindex;
	}
	string ogPrefix = prefix; // this is holding noting because we want to reset prefix at the end of one run, prefix should be holding nothing so it can continue finding new permutations.
	string ogRest = rest;     // this is holding noting because we want to reset rest at the end of one run, rest should be holding nothing so it can continue finding new permutations.

	prefix = prefix + rest[i]; // here we are taking the first letter of every string in rest and transferring it over for the variable prefix.
	rest = rest.substr(0, i) + rest.substr(i + 1, rest.size()); // in this line we are chopping off the the fist letter in rest and making it only hold evry letter that was not chopped off. so say we had cat. prefix holds "c" and rest holds "at"
	permute(prefix, rest, dict, size, results, resultsindex); // here we call the funtion permute with the updated information of these variables because we do not want the program to process one thing over and over and over again becuase we did not make the call to permute with an update. we do this so we can find more permutations.

	prefix = ogPrefix;// We are resetting the variable prefix because we do not want it to hold old data.
	rest = ogRest; // same goes to the variable rest because we do not want it to hold old data.
	return Loop(initval, max, prefix, rest, dict, size, results, i + 1, resultsindex); // here we want to increment varible i because variable i is guiding through the string and telling it to leep moving one over so it does not keep getting the same prefix and rest over and over again.
																					   // our goal is to eventually get the whole string in rest to prefix.
}

bool Find(int i, string s, const string dict[], int size)
{
	if (i == size) // if i is equal to the size of the dictionary array then we tell it to stop. size is linked to the size of the dictionary array.
	{
		return false;
	}
	if (s == dict[i]) // here we are saying if the string is found in the dictionary array then we want to validate that the permutation is now an anagram. so we return true
	{
		return true;
	}

	return Find(i + 1, s, dict, size); // we call the function again so it can continue to keep comparing.
}

void printRecur(const string results[], int size) // actual function.
{
	printRecurHelper(0, size, results);
}

void printRecurHelper(int i, int size, const string results[]) // this is the function helper that will help print every result in the results array.
{
	if (i >= size)
	{
		return;
	}
	cout << results[i] << endl;
	printRecurHelper(i + 1, size, results); // we make the call to itself again because we update i and in doing so will continue to print everything in the results array.
}

int main()
{

	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile;         // file containing the list of words
	int nwords;                // number of words read from dictionary
	string word;

	dictfile.open("words.txt");
	if (!dictfile)
	{
		cout << "File not found!" << endl;
		return (1);
	}

	nwords = loadDictionary(dictfile, dict);

	cout << "Please enter a string for an anagram: ";
	cin >> word;

	int numMatches = permuteRecur(word, dict, nwords, results);
	if (!numMatches)
		cout << "No matches found" << endl;
	else
		printRecur(results, numMatches);


}
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int loadDictionary(istream& dictfile, vector<string>& dict) {
	string temp;
	while (getline(dictfile, temp))
	{
		dict.push_back(temp);
	}

	return dict.size();
}

int permute(string word, vector<string>& dict, vector<string>& results) {

	sort(begin(word), end(word)); // we sort at the beginning because we can lose other permutations if we do not account for this.

	do {
		for (int i = 0; i < results.size(); i++)
		{
			if (results[i] == word)
			{
				continue;
			}
		}
		for (int i = 0; i < dict.size(); i++)
		{
			if (dict[i] == word)
			{
				results.push_back(word);
			}
		}

		//if (find(begin(dict), end(dict), word) != end(dict) && find(begin(results), end(results), word) == end(results)) {
		//	results.push_back(word);
		//	/*cout << word << endl;    this was for testing*/
		//}
			/*
			the purpose of the if statement is we utalize the find stl function and the way it works is that we have to pass in
			the beginning and ending of the dictionary. I think of it as it needs the entire dictionary first so it can compare
			the word it is looking for. That is also another parameter we must include. we must pass in the word. The way we have
			it set up is we sort the word and we are taking the permutation and seeing if the permutation is found in the dictionary.
			That is half of the if and the the other half is we set this find function to not equal the end of the dictionary index,
			because the way the find function works is that it returns the last index number of the dictionary if it has not found what its looking for in itself.
			when it does find what it is looking for, then we can input that word into the reults vector.

			the other find is to make sure there are no duplications. so we have to pass the entire results vector and what the find is
			doing is that if the word say look is in the results array and it wants to add look again, it will negate the adding it into
			the results array. if the word is not in the vector, then it will add it into the results vector.



			*/
	} while (std::next_permutation(begin(word), end(word))); // this is where the permutations are done.

	return results.size();
}


void print(const vector<string>& results) {
	if (results.size() == 0) {
		cout << "No matching words" << endl;
		return;
	}

	for (int i = 0; i < results.size(); i++)
	{
		cout << results[i] << endl;
	}
}

int main()
{
	cout << "Please insert the dictionary file: " << endl;
	fstream infile("words.txt");
	vector <string> dictionary;
	loadDictionary(infile, dictionary);
	while (true)
	{
		vector <string> results_;
		string input;
		cout << "Please enter a string anagram for a word: ";
		cin >> input;
		permute(input, dictionary, results_);
		print(results_);

		cout << " Would you like to continue? (y/n): ";
		cin >> input;
		if (input != "y" && input != "Y")
		{
			break;
		}


	}

	/*print(holder)*/;

}
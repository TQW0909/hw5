// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle(
	std::string& word,
	set<string>* words,
	std::string& floating_copy,
	const std::string& in,
	const std::string& floating, 
	const std::set<std::string>& dict, 
	const unsigned int& size);

// bool containFloat(const std::string& word, const std::string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
	const std::string& in,
	const std::string& floating,
	const std::set<std::string>& dict)
{
	// Add your code here
	string temp;
	set<string> words;
	string copy = floating;
	
	wordle(temp, &words, copy, in, floating, dict, in.size());

	return words;
}

// Define any helper functions here

// Helpher function
void wordle(
	std::string& word,
	set<string>* words,
	std::string& floating_copy,
	const std::string& in,
	const std::string& floating, 
	const std::set<std::string>& dict, 
	const unsigned int& size)
{
	// Base case
	if (word.size() == size)
	{
		// Seeing if word exists in the dictionary
		set<string>::iterator it = dict.find(word);

		// Insert into set only if word is a valid english word and that it contains the floating characters
		if (it != dict.end() && floating_copy.size() == 0)
		{
			words->insert(*it);
		}
	}
	else
	{
		// Case  1: Fixed letter (i.e. not '-')
		if (in[word.size()] != '-')
		{
			// Adding fixed letter to word
			word += in[word.size()];

			wordle(word, words, floating_copy, in, floating, dict, size); // Recurse

			// Undoing changes
			word.pop_back();
		}

		// Case 2: Open space
		else
		{
			// If there is more floating characters than remaining spaces, then just return (cuz not possible)
			if (floating_copy.size() > in.size() - word.size()) return;

			// Trying floating letters
			for (unsigned int i = 0; i < floating_copy.size(); i++)
			{
				// Adding float character to word
				word += floating_copy[i];
				// Creating a temp variable to hold removed floating character
				char temp = floating_copy[i];

				floating_copy.erase(floating_copy.begin() + i);
				
				wordle(word, words, floating_copy, in, floating, dict, size); // Recurse

				// Undoing changes
				floating_copy.insert(floating_copy.begin() + i, temp);
				word.pop_back();
			}

			// Trying remaining letters
			for (int i = 0; i < 26; i++)
			{
				// Does not recurse again for characters that exist in floating
				if (floating_copy.find(char(97 + i)) == string::npos)
				{
					// Adding character to word
					word += char(97 + i);

					wordle(word, words, floating_copy, in, floating, dict, size); // Recurse

					// Undoing changes
					word.pop_back();
				}
			}
		}
	}
}
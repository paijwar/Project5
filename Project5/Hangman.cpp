/**************************************************************
COSC 501
Elliott Plack
14 NOV 2013                            Due date: 30 NOV 2013

Problem:
	Write a program that plays the game of HANGMAN(guessing a
	mystery word).  Read a word to be guessed from a file into
	successive elements of the array WORD. The player must
	guess the letters belonging to WORD. A single guessing
	session should be terminated when either all letters have
	been guessed correctly (player wins) or a specified number
	of incorrect guesses have been made (computer wins). A run
	must consist of at least two sessions: one player wins and
	one computer wins. The player decides whether or not to
	start a new session. 

***************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h> // for random
using namespace std;

ifstream inFile;     // define ifstream to inFile command
ofstream outFile;    // define outfile2

void readString();
void initialize(unsigned long); // function to initalize everything
void guess(); 

// global variables
//char guess; // guess from user
string word; // word to be read from file (the solution)
string solution; // solution (guessed by user)
unsigned long wordLength; // length of word

// functions

int main() // reads in the file and sets the functions in motion
{
	readString();
	initialize(wordLength); // sends length of word to initialize function
	cout << "Let's play hangman!\n";
	guess();

	return 0;
}

void readString()
{
	int random20 = 0; // random number
	string dictionary[20]; // 20 words to load from file

	inFile.open("Words4Hangman.txt"); // open input file

	while (inFile.good())
	{
		for (int i = 0; i < 20; i++)
		{
			inFile >> dictionary[i]; // load file and fill dict
		}
	}

	inFile.close(); // close the file

	srand((int)time(NULL)); // initialize random seed
	random20 = (rand() % 20); // set random to 20 +-

	word = dictionary[rand() % 20]; // set word = to a random letter in the dictionary
	cout << word << endl; // cheater! (testing)
	wordLength = word.size(); // size (length) of the string
}

void initialize(unsigned long wordLength)
{
	solution.assign(wordLength, '*');

	cout << "Solution: " << solution << endl; // test
}

void guess()
{
	char guessLetter = ' '; // letter to guess
	cout << solution << endl; // output solution
	cout << "Guess a letter\n";
	cin >> guessLetter;

	for (unsigned long i = 0; i < wordLength; i++)
	{
		if (guessLetter == word[i])
		{
			cout << "char " << i << " is " << guessLetter << endl;
		}
		cout << guessLetter << "is not in the word";
	}
	
}
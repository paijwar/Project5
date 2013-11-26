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
#include <time.h>
using namespace std;

ifstream inFile;     // define ifstream to inFile command
ofstream outFile;    // define outfile2

int main()
{
	// variables
	
	char guess = ' '; // guess from user
	string dictionary[20]; // 20 words to load from file
	int random20 = 0;
	string word = ""; // word to be read from file (the solution)

	inFile.open("Words4Hangman.txt"); // open input file

	while (inFile.good())
	{
		for (int i = 0; i < 20; i++)
		{
			inFile >> dictionary[i]; // load file
			cout << dictionary[i] << endl; // testing
		}
	}

	srand((int)time(NULL));
	random20 = (rand() % 20);

	word = dictionary[rand() % 20]; // set word = to a random letter in the dictionary

	cout << "Random word: -------- " << word << endl; // test
	return 0;
}
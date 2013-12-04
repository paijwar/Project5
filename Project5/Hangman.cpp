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

void readString();
void initialize(unsigned long); // function to initalize everything
void guess(); 
void hangmanDraw(int, int, string);

// global variables
string word; // word to be read from file (the solution)
string solution; // solution (guessed by user)
unsigned long wordLength; // length of word

// functions

int main() // reads in the file and sets the functions in motion
{
	readString(); // reads the file and stores variables
	initialize(wordLength); // sends length of word to initialize function
	cout << "Let's play hangman!\n";
	guess(); // game logic

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
	solution.assign(wordLength, '*'); // fills up the solution string (an array) with as many *s as the word length
}

void guess()
{
	char guessLetter = ' '; // letter to guess
	int winning = 0, goodGuess = 0; // variable to check if the game is won or the guess is good
	int guessesCounter = 7; // hangman countdown
	
	//cout << solution << endl; // output solution
	
	// show hangman to start
	// hangmanDraw(-1, 0, solution); // coded values to show the first screen.
	


	while ((guessesCounter <= 7) && (winning == 0))
	{
		hangmanDraw(guessesCounter, winning, solution);
		cout << "Guess a letter: ";
		cin >> guessLetter;
		guessLetter = toupper(guessLetter); // make guess uppercase

		for (unsigned long i = 0; i < wordLength; i++) // loop through word looking for guess
		{
			if (guessLetter == word[i])
			{
				//cout << "char " << (i + 1) /* +1 because first is 0*/ << " is " << guessLetter << endl; // outputs that guess was correct
				solution[i] = guessLetter; // set the i char in solution to guessLetter
				goodGuess = 1; // sets the flag goodGuess = 1 for the logic below
			}
		}

		if (solution == word) // thus victory
		{
			winning = 1; // you won
			hangmanDraw(guessesCounter, winning, solution);
		}
		else if (goodGuess == 1)
		{
			goodGuess = 0; // clear flag for next run
			hangmanDraw(guessesCounter, winning, solution);
		}
		else
		{
			guessesCounter--; // decrement guess
			hangmanDraw(guessesCounter, winning, solution);
		}
	}
}

void hangmanDraw(int guessNumber, int winningResult, string solutionDisplay)
{
	// set up strings for game
	string hD01 = "    /\\  /\\__ _ _ __   __ _ _ __ ___   __ _ _ __  \n"; // have to escape out backslash
	string hD02 = "   / /_/ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n"; // have to escape out backslash
	string hD03 = "  / __  / (_| | | | | (_| | | | | | | (_| | | | |\n"; 
	string hD04 = "  \\/ /_/ \\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"; // have to escape out backslash
	string hD05 = "                     |___/                       \n";
	string hD06 = "                            by Elliott Plack     \n";
	string hD07 = "                                                 \n";
	string hD08 = "      _______                                    \n";
	string hD09 = "     |/      |          ______________________   \n";
	string hD10 = "     |                 |                      |  \n";
	string hD11 = "     |                 | Your Progress        |  \n";
	string hD12 = "     |                 |                      |  \n";
	string hD13 = "     |                 |                      |  \n";
	string hD14 = "     |                 |                      |  \n";
	string hD15 = "  ___|___              |______________________|  \n";

	// set up body parts
	string head = "(_)";
	string neck = "|";
	string leftArm = "\\";
	string rightArm = "/";
	string torso = "|";
	string leftLeg = "/";
	string rightLeg = "\\";
	const char space = ' ';
	string youWon = "YOU WON !!";
	string youLose = "YOU DIED !";

	//system("CLS"); // clear the input screen

	if (guessNumber <= 7)
	{
		switch (guessNumber)
		{
		case 7:
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 6:
			hD10 = hD10.replace(12, 3, head);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 5:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 1, leftArm);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 4:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 2, leftArm + neck);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 3:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 2:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 1:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(12, 2, leftLeg + space);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		case 0:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(12, 3, leftLeg + space + rightLeg);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			hD14 = hD14.replace(31, 10, youLose);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;
			break;
		default:
			cout << "\aError!";
			break;
		}
	}
	else if (winningResult == 1)
	{
		hD13 = hD13.replace(25, wordLength, solutionDisplay);
		hD14 = hD14.replace(31, 10, youWon);
		cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
			<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15;

	}
}
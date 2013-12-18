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

#include <iomanip.h>
#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <time.h> // for random
using namespace std;

ifstream inFile;     // define ifstream to inFile command

void readString();
void initialize(unsigned long); // function to initalize everything
void guess(); 
void hangmanDraw(int, int, string, char, int);

// global variables
string word; // word to be read from file (the solution)
string solution; // solution (guessed by user)
string hD17 = "  Your guesses:                                  \n"; // string to store guesses
unsigned long wordLength; // length of word

// functions

int main() // reads in the file and sets the functions in motion
{
	char repeat = 'Y'; // test if user wants to repeat
	while (repeat == 'Y' || repeat == 'y')
	{
		readString(); // reads the file and stores variables
		initialize(wordLength); // sends length of word to initialize function
		guess(); // game logic

		cout << "Do you want to play again? Y/N: ";
		
		cin >> repeat;
	}
	return 0;
}

void readString()
{
	int random20 = 0; // random number
	string dictionary[20]; // 20 words to load from file

	inFile.open("Words4Hangman.dat"); // open input file

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

	word = dictionary[random20]; // set word = to a random letter in the dictionary
	//cout << word << endl; // cheater! (testing)
	wordLength = word.size(); // size (length) of the string
}

void initialize(unsigned long wordLength)
{
	solution.assign(wordLength, '*'); // fills up the solution string (an array) with as many *s as the word length
	hD17 = "  Your guesses:                                  \n"; // string to store guesses
}

void guess()
{
	char guessLetter = ' '; // letter to guess
	int winning = 0, goodGuess = 0; // variable to check if the game is won or the guess is good
	int guessesCounter = 7; // hangman countdown

	hangmanDraw(guessesCounter, winning, solution, guessLetter, goodGuess); // show blank

	while ((guessesCounter > 0) && (winning == 0)) // while the guesses counter is greater than 0 and winning flag is unset
	{
		
		cout << "Guess a letter: ";
		cin >> guessLetter;
		guessLetter = toupper(guessLetter); // make guess uppercase

		for (unsigned long i = 0; i < wordLength; i++) // loop through word looking for guess
		{
			if (guessLetter == word[i])
			{
				solution[i] = guessLetter; // set the i char in solution to guessLetter
				goodGuess = 1; // sets the flag goodGuess = 1 for the logic below
			}
		}
		
		if (solution == word) // winning condition
		{
			winning = 1; // variable flag telling drawing function victory is true
			hangmanDraw(guessesCounter, winning, solution, guessLetter, goodGuess);
		}
		else if (goodGuess == 1) // good guess condition
		{
			hangmanDraw(guessesCounter, winning, solution, guessLetter, goodGuess);
			goodGuess = 0; // clear flag for next run
		}
		else // if you didn't win or get a good guess, fail
		{
			guessesCounter--; // decrement guess
			hangmanDraw(guessesCounter, winning, solution, guessLetter, goodGuess);
		}
	}
}

void hangmanDraw(int guessNumber, int winningResult, string solutionDisplay, char guessLetter, int goodGuess)
// epic function to display the game
{
	// set up strings for game using fixed with strings and ascii art
	// note that each line is a string with a unique variable name.
	// hD means hangmanDraw
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
	string hD16 = "                                                 \n";
	// last string had to be a global so it wouldn't be over writen each
	//      time the function runs. There is probably a more elegant way
	//      to do that.

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

	string guessStr; // string that will get the bad guesses for display

	if (goodGuess != 1) // if the guess isn't good add the fail letter to string
	{
		guessStr.push_back(guessLetter); // store guess char to string
	}

	system("CLS"); // clear the input screen (Windows only)

	if (guessNumber <= 7 && winningResult == 0)
	{
		switch (guessNumber) // switch based on the guess number parameter
		{
		case 7: // no bad guesses or beginning case
			hD13 = hD13.replace(25, wordLength, solutionDisplay); // replaces the string line with the 'box' to show solution
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17; // outputs each line 
			break;
		case 6: // lost a head
			hD10 = hD10.replace(12, 3, head); // adds the head
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1) // if the guess was bad ... vvv ... otherwise the good guess will end up on the guess line
				hD17 = hD17.replace(17, 1, guessStr);   // add the bad guess to the output line
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;// outputs each line 
			break;
		// each case from here on out adds a body part. the comments are basically the same as above.
		case 5:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 1, leftArm);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1)
				hD17 = hD17.replace(20, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		case 4:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 2, leftArm + neck);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1)
				hD17 = hD17.replace(23, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		case 3:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1)
				hD17 = hD17.replace(26, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		case 2:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1)
				hD17 = hD17.replace(29, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		case 1:
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(12, 2, leftLeg + space);
			hD13 = hD13.replace(25, wordLength, solutionDisplay);
			if (goodGuess != 1)
				hD17 = hD17.replace(32, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		case 0: // death
			hD10 = hD10.replace(12, 3, head);
			hD11 = hD11.replace(12, 3, leftArm + neck + rightArm);
			hD12 = hD12.replace(13, 1, torso);
			hD13 = hD13.replace(12, 3, leftLeg + space + rightLeg);
			hD13 = hD13.replace(25, wordLength, word); // show the full word to show what you missed
			hD14 = hD14.replace(31, 10, youLose);
			if (goodGuess != 1)
				hD17 = hD17.replace(35, 1, guessStr);
			cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
				<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
			break;
		default:
			cout << "\aError!";
			break;
		}
	}
	else if (winningResult == 1) // if you won, do this
	{
		// note: this takes away the body parts. I should
		//       rewrite the winning if statement as a
		//       switch, similar to the above one.
		//       see https://github.com/talllguy/Project5/issues/5
		hD13 = hD13.replace(25, wordLength, solutionDisplay);
		hD14 = hD14.replace(31, 10, youWon);
		cout << hD01 << hD02 << hD03 << hD04 << hD05 << hD06 << hD07
			<< hD08 << hD09 << hD10 << hD11 << hD12 << hD13 << hD14 << hD15 << hD16 << hD17;
	}
}

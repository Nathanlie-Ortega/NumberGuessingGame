
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

//Enumeration declaration for values displayLeft, displayRight, Guess, Change, and Exit
enum Menu{displayLeft = 1, displayRight, Guess, Change, Exit};

int main() {
	//A display of the title, my name, and e-mail address
    cout << "+-------------------------------------------------+" << endl;
    cout << "|      Number Guessing Game			  |" << endl;
    cout << "|      Author name: Nathanlie Ortega              |" << endl;
    cout << "|      NathanlieOrtega.Dev@gmail.com              |" << endl;
    cout << "+-------------------------------------------------+\n" << endl;
	
	//Seed the random number generator
	srand(static_cast<unsigned int>(time(0)));
	
	//Integer variable declaration and Initialize to 100 of player points
	int playerPoints = 100;
	
	//Ask the player for the name of the player
	string playerName;
	bool validName = false;
	
	while(!validName) {
		cout << "Enter your name: ";
		getline(cin, playerName);	//The name may have multiple words
		validName = true;
		
		//Validate the name and format it
		for(size_t i = 0; i < playerName.length(); ++i) {
			if(!isalpha(playerName[i]) && !isspace(playerName[i])) {
				validName = false;
				break;
			}
		}
		
		if(validName) {
			bool newWord = true;
			for(size_t i = 0; i < playerName.length(); ++i) {
				if(isalpha(playerName[i])) {
					if(newWord) {
						playerName[i] = toupper(playerName[i]);
						newWord = false;
					}
					else {
						playerName[i] = tolower(playerName[i]);
					}
				}
				else if (isspace(playerName[i])) {
					newWord = true;
				}
			}
		}
		
		// The player enters any other characters in the name, ask for the name again
		else {
			cout << "Your name can only have alphabets or spaces. Enter again." << endl;
		}
	}
	
	
	int lowerBound;
	int upperBound;
	
	// Two generated seeded random integers in the range of 100 to 200, inclusive.
	do {
		lowerBound = (rand() % 101) + 100;
		upperBound = (rand() % 101) + 100;
	}
	while (lowerBound >= upperBound);	// First integer MUST BE less than the second integer
	
	//Two integers with initialization of -1
	int displayLeftNum = -1;			//Display the first randomly generated integer instead of -1 on the left
	int displayRightNum = -1;			//Display the second randomly generated integer instead of -1 on the right
	bool leftDisplayed = false;
	bool rightDisplayed = false;
	
	Menu choice;
	
	do {
		//Displaye the current bounds
		if (leftDisplayed) {
			cout << displayLeftNum;
		}
		else {
			cout << -1;
		}
		
		cout << "     ";
		if (rightDisplayed) {
			cout << displayRightNum;
		}
		
		else {
			cout << -1;
		}
		
		cout << endl;
		
		//Display the menu for a player to choose
		cout << "1. Display Left Number" << endl;
		cout << "2. Display Right Number" << endl;
		cout << "3. Guess a number in between" << endl;
		cout << "4. Change numbers" << endl;
		cout << "5. Exit" << endl;
		cout << "What do you want to do? ";
		
		//Ask the player to select from the menu
		int menuChoice;
		cin >> menuChoice;
		choice = static_cast<Menu>(menuChoice);
		
		// A switch-case block with a default case in using the enumerated data constants
		switch (choice) {
			case displayLeft:				//The player chooses to display the integer on the left (the lower bound)
			if (!leftDisplayed && !rightDisplayed) {
				displayLeftNum = lowerBound;
				leftDisplayed = true;
				cout << "You will only get 1 point for guessing correctly and lose 10 points for guessing incorrectly." << endl;
			}
			else {
				cout << "You have already displayed the right boundary, you cannot display both." << endl;
			}
			break;
			
			//The player chooses to display the integer on the right 
			case displayRight:
			if (!rightDisplayed && !leftDisplayed) {
				displayRightNum = upperBound;
				rightDisplayed = true;
				cout << "You will only get 1 point for guessing correctly and lose 10 points for guessing incorrectly, now." << endl;
			}
			else {
				//The player cannot display both numbers/bounds
				cout << "You have already displayed the left boundary, you cannot display both." << endl;
			}
			break;
			
			//Prompt the player to guess a number between two bounds
			case Guess: {
			int guess;
			cout << "Enter your guess: ";		//Ask the player to enter the guess
			cin >> guess;
			
			if (guess > lowerBound && guess < upperBound) {
				if (leftDisplayed || rightDisplayed) {
					playerPoints += 1;			//The player corrected the guess and displayed bounds, incremented by 1
					cout << "You guessed correctly. You get 1 point." << endl;
				}
				else {
					playerPoints += 5;			//The player has NOT displayed any of the two bounds, incremented by 5 points 
					cout << "You guessed correctly. You get 5 points." << endl;
				}
			}
			
			else {
				if (leftDisplayed || rightDisplayed) {
					playerPoints -= 10;			//Decrement by 10 points when appropriate and incorrect guess
					cout << "You guessed incorrectly. You lost 10 points." << endl;		
				}
				else {
					playerPoints -= 5;			//Decrement by 5 points when appropriate and incorrect guess
					cout << "You guessed incorrectly. You lost 5 points." << endl;
				}
			}
			
			cout << "Your remaining points: " << playerPoints << endl;
			break;
		}
		
			
			case Change:			//The player chooses to change the random numbers, regenerate the two seeded random numbers
			do{
				lowerBound = rand() % 101 + 100;
				upperBound = rand() % 101 + 100;
			}
			
			while (lowerBound >= upperBound);
			leftDisplayed = rightDisplayed = false;
			displayLeftNum = displayRightNum = -1;
			
			playerPoints -= 1;	//Deduct 1 point for this choice and provide the player updated points balance
			
			cout << "Your remaining points: " << playerPoints << endl;
			cout << "Generating new boundaries. " << endl;
			break;

			
			case Exit:
			cout << "Bye " << playerName << "!!!" << endl;		//The player choose to Exit
			cout << "Your final points balance: " << playerPoints << endl;
			break;
			
			
			default:						//The player enters a wrong choice
			cout << "Invalid choice. Please try again." << endl;
		
		}
	}
	
	while (choice != Exit && playerPoints >= 0);
	
	if (playerPoints < 0) {			//The player is out of player points
		cout << "You are out of points." << endl;
		cout << "Bye " << playerName << "!!!" << endl;
	}


	return 0;
}
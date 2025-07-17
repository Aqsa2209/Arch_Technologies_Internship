#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to simulate rolling Dice
void rollDice(int numDice) {
    cout << "Rolling " << numDice << " dice..." << endl;
    for (int i = 1; i <= numDice; ++i) {
        int result = rand() % 6 + 1; // Random number between 1 and 6
        cout << "Die " << i << ": " << result << endl;
    }
    cout << "-----------------------------" << endl;
}

int main() {
    srand(time(0)); // Seed random number generator with current time
    int numDice;
    char choice;
    int rollCount = 0;

    cout << "Welcome to the Dice Roller Simulator!" << endl;

    cout << "Enter how many dice you want to roll: ";
    cin >> numDice;

    // Input validation
    while (numDice <= 0) {
        cout << "Please enter a number greater than 0: ";
        cin >> numDice;
    }

    do {
        rollDice(numDice);     // Roll the dice
        rollCount++;           // Increment counter

        cout << "You have rolled the dice " << rollCount << " time(s)." << endl;
        cout << "Do you want to roll again? (y/n): ";
        cin >> choice;

        while (choice != 'y' && choice != 'n') {
            cout << "Invalid input. Please enter 'y' or 'n': ";
            cin >> choice;
        }

    } while (choice == 'y');

    cout << "Thanks for playing! You rolled " << rollCount << " time(s)." << endl;

    return 0;
}


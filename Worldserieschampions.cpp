/*
------------------------------------------------------------
Program: World Series Champions
Author: Charles Duncan
Date: December 2025
Description:
    This program reads a list of Major League Baseball teams
    (Teams.txt) and a chronological list of World Series winners
    (WorldSeriesWinners.txt). It displays the list of teams, then
    allows the user to enter a team name repeatedly. For each team,
    the program reports how many times that team won the World Series
    between 1903 and 2012. User enters "quit" to terminate.

Preconditions:
    - Teams.txt contains team names (alphabetical order).
    - WorldSeriesWinners.txt contains winners from 1903–2012.
    - Files exist and are formatted correctly.

Postconditions:
    - Outputs the number of wins for any team entered by the user.
------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function Prototypes
bool getTeams(const string& filename, vector<string>& teams);
int findWinner(const string& team, const vector<string>& winners);

int main() {
    vector<string> teams;
    vector<string> winners;

    // Load teams
    if (!getTeams("Teams.txt", teams)) {
        cerr << "Error: Could not open Teams.txt" << endl;
        return 1;
    }

    // Load winners
    if (!getTeams("WorldSeriesWinners.txt", winners)) {
        cerr << "Error: Could not open WorldSeriesWinners.txt" << endl;
        return 1;
    }

    // Display team list
    cout << "World Series Teams (1903–2012):" << endl;
    for (const string& team : teams) {
        cout << " - " << team << endl;
    }

    // User input loop
    string input;
    cout << "\nEnter a team name to see how many times they won (or type 'quit' to exit): ";
    getline(cin, input);

    while (input != "quit") {
        int wins = findWinner(input, winners);
        cout << input << " won the World Series " << wins << " times." << endl;

        cout << "\nEnter another team name (or 'quit' to exit): ";
        getline(cin, input);
    }

    cout << "Program terminated. Goodbye!" << endl;
    return 0;
}

/*
------------------------------------------------------------
Function: getTeams
Purpose: Reads names from a file into a vector
Parameters:
    - filename: name of file containing team names
    - teams: vector to store names
Returns:
    - true if file read successfully, false otherwise
------------------------------------------------------------
*/
bool getTeams(const string& filename, vector<string>& teams) {
    ifstream inFile(filename);
    if (!inFile) return false;

    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            teams.push_back(line);
        }
    }
    inFile.close();
    return true;
}

/*
------------------------------------------------------------
Function: findWinner
Purpose: Counts how many times a team appears in winners list
Parameters:
    - team: team name to search for
    - winners: vector of World Series winners
Returns:
    - number of times team won
------------------------------------------------------------
*/
int findWinner(const string& team, const vector<string>& winners) {
    int count = 0;
    for (const string& winner : winners) {
        if (winner == team) {
            count++;
        }
    }
    return count;
}

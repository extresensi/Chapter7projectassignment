/*
------------------------------------------------------------
Program: Exam Grader
Author: Charles Duncan
Date: December 2025
Description:
    This program grades a student's exam consisting of 20
    multiple-choice questions (A-D). It reads the correct
    answers from CorrectAnswers.txt and the student's answers
    from StudentAnswers.txt, compares them, and generates a
    report showing:
        - Questions missed with correct vs. student answers
        - Total number missed
        - Percentage correct
        - Pass/Fail status (>=70% = Pass)

Preconditions:
    - CorrectAnswers.txt and StudentAnswers.txt exist
    - Each file contains exactly 20 answers (A-D), one per line

Postconditions:
    - Outputs formatted grading report to console
------------------------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Constants
const int NUM_QUESTIONS = 20;

// Function Prototypes
bool getAnswers(const string& filename, char answers[], int size);
int gradeExam(const char correct[], const char student[], int missed[], char missedAnswers[][2], int size);
void writeReport(const int missed[], const char missedAnswers[][2], int numMissed, int size);

int main() {
    char correct[NUM_QUESTIONS];
    char student[NUM_QUESTIONS];
    int missed[NUM_QUESTIONS];              // Stores indices of missed questions
    char missedAnswers[NUM_QUESTIONS][2];   // Stores correct and student answers
    int numMissed;

    // Load correct answers
    if (!getAnswers("CorrectAnswers.txt", correct, NUM_QUESTIONS)) {
        cerr << "Error: Could not open CorrectAnswers.txt" << endl;
        return 1;
    }

    // Load student answers
    if (!getAnswers("StudentAnswers.txt", student, NUM_QUESTIONS)) {
        cerr << "Error: Could not open StudentAnswers.txt" << endl;
        return 1;
    }

    // Grade exam
    numMissed = gradeExam(correct, student, missed, missedAnswers, NUM_QUESTIONS);

    // Write report
    writeReport(missed, missedAnswers, numMissed, NUM_QUESTIONS);

    return 0;
}

/*
------------------------------------------------------------
Function: getAnswers
Purpose: Reads exam answers from a file into an array
Parameters:
    - filename: name of file containing answers
    - answers[]: array to store answers
    - size: number of questions
Returns:
    - true if file read successfully, false otherwise
------------------------------------------------------------
*/
bool getAnswers(const string& filename, char answers[], int size) {
    ifstream inFile(filename);
    if (!inFile) return false;

    for (int i = 0; i < size; i++) {
        inFile >> answers[i];
    }
    inFile.close();
    return true;
}

/*
------------------------------------------------------------
Function: gradeExam
Purpose: Compares student answers to correct answers
Parameters:
    - correct[]: array of correct answers
    - student[]: array of student answers
    - missed[]: array storing indices of missed questions
    - missedAnswers[][]: 2D array storing correct vs. student answers
    - size: number of questions
Returns:
    - number of missed questions
------------------------------------------------------------
*/
int gradeExam(const char correct[], const char student[], int missed[], char missedAnswers[][2], int size) {
    int numMissed = 0;
    for (int i = 0; i < size; i++) {
        if (correct[i] != student[i]) {
            missed[numMissed] = i; // store question index
            missedAnswers[numMissed][0] = correct[i];
            missedAnswers[numMissed][1] = student[i];
            numMissed++;
        }
    }
    return numMissed;
}

/*
------------------------------------------------------------
Function: writeReport
Purpose: Outputs exam results
Parameters:
    - missed[]: array of missed question indices
    - missedAnswers[][]: 2D array of correct vs. student answers
    - numMissed: number of missed questions
    - size: total number of questions
------------------------------------------------------------
*/
void writeReport(const int missed[], const char missedAnswers[][2], int numMissed, int size) {
    cout << "---------------- Exam Report ----------------" << endl;

    if (numMissed > 0) {
        cout << "Questions Missed:" << endl;
        for (int i = 0; i < numMissed; i++) {
            cout << "Q" << setw(2) << missed[i] + 1
                 << ": Correct = " << missedAnswers[i][0]
                 << ", Student = " << missedAnswers[i][1] << endl;
        }
    } else {
        cout << "No questions missed!" << endl;
    }

    cout << "\nTotal Missed: " << numMissed << endl;

    double percentCorrect = ((size - numMissed) / (double)size) * 100.0;
    cout << fixed << setprecision(2);
    cout << "Percentage Correct: " << percentCorrect << "%" << endl;

    if (percentCorrect >= 70.0)
        cout << "Result: PASS" << endl;
    else
        cout << "Result: FAIL" << endl;

    cout << "---------------------------------------------" << endl;
}

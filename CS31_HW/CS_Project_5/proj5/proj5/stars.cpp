#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
#include <cstring>
#include <iostream>
using namespace std;

const char WORDFILENAME[] = "./myWords.txt";
const int MAXWORDS = 8000;

int runOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);
bool stringIsLower(const char cstring[]);
bool inValidWords(const char words[][MAXWORDLEN + 1], int nWords, const char cstring[]);
void calcPlanetStars(const char trialWord[], const char secret[]);

int main()
{
    /*
    REREAD SPEC

   */

    // main routine
 
    char wordlist[MAXWORDS][MAXWORDLEN + 1];
    int numWordsLoaded = getWords(wordlist, MAXWORDS, WORDFILENAME);
    int totalRounds = 0;

    if (numWordsLoaded < 1) {
        cout << "No words were loaded, so I can't play the game.";
    }
    else {
        // prompt and check for number of rounds
        cout << "How many rounds do you want to play? ";
        cin >> totalRounds;
        cin.ignore(1000, '\n');
        if (totalRounds <= 0) {
            cout << "The number of rounds must be positive.";
        }
    }

    // score stats
    int maxScore;
    int minScore;
    int totalScore = 0;

    // play rounds
    int roundNum = 0;
    while (roundNum < totalRounds) {
        roundNum++;
        int secretRandInt; // random int/index for secret
        secretRandInt = randInt(0, numWordsLoaded-1);

        cout << endl << "Round " << roundNum << endl;
        cout << "The secret word is " << strlen(wordlist[secretRandInt]) << " letters long." << endl;
        int score = runOneRound(wordlist, numWordsLoaded, secretRandInt);
        if (score == 1) {
            cout << "You got it in " << score << " try." << endl;
        }
        else {
            cout << "You got it in " << score << " tries." << endl;
        } 
        totalScore += score;
        
        // calculate and display stats
        if (roundNum == 1) {
            maxScore = score;
            minScore = score;
        }
        else {
            if (score < minScore) {
                minScore = score;
            }
            else if (score > maxScore) {
                maxScore = score;
            }
        }
        double average = totalScore / static_cast<double>(roundNum);
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << average << ", minimum: " << minScore
             << ", maximum: " << maxScore << endl; 

    }

}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) {
        return -1;
    }
    char trialInp[100];
    int score = 0;
    for (;;) {
        
        cout << "Trial word: ";
        cin.getline(trialInp, 100);

        // check trial word length
        if (strlen(trialInp) > MAXWORDLEN || strlen(trialInp) < MINWORDLEN || !stringIsLower(trialInp)) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        // check if trial word in wordlist
        if (!inValidWords(words, nWords, trialInp)) {
            cout << "I don't know that word." << endl;
            continue;
        }
        // check if trail word is equal to secret
        if (strcmp(words[wordnum], trialInp) == 0) {
            score++;
            break;
        }
        // otherwise calculate planets and stars
        calcPlanetStars(trialInp, words[wordnum]);
        score++;
    }
    
    return score;
}

void calcPlanetStars(const char trialWord[], const char secret[]) {
    // copy made to keep track of matched planets and stars
    char secretCopy[MAXWORDLEN+1];
    strcpy(secretCopy, secret);
    char trialCopy[MAXWORDLEN+1];
    strcpy(trialCopy, trialWord);

    int stars = 0;
    int planets = 0;

    int maxInd;
    if (strlen(secret) <= strlen(trialWord)) {
        maxInd = static_cast<int>(strlen(secret));
    }
    else {
        maxInd = static_cast<int>(strlen(trialWord));
    }
    // match stars first
    for (int i = 0; i < maxInd; i++) {
        if (trialWord[i] == secretCopy[i]) {
            stars++;
            // period signifies already matched star
            secretCopy[i] = '.';
            trialCopy[i] = '.';
        }
    }
    
    // match planets if star not already matched
    for (int i = 0; trialWord[i] != '\0'; i++) {
        if (trialCopy[i] == '.') {
            continue;
        }
        for (int j = 0; secretCopy[j] != '\0'; j++) {
            if (secretCopy[j] == trialCopy[i]) {
                planets++;
                // period signifies already matched planet
                secretCopy[j] = '.';
                break;
            }
        }
    }
    cout << "Stars: "<< stars << ", Planets: " << planets << endl;
}


// Check if trail word is in the wordlist
bool inValidWords(const char words[][MAXWORDLEN+1], int nWords, const char cstring[]) {
    for (int i = 0; i < nWords; i++) {
        if (strcmp(words[i],cstring) == 0) {
            return true;
        }
    }
    return false;
}

// Check if C string is all lowercase
bool stringIsLower(const char cstring[]) {
    for (int i = 0; cstring[i] != '\0'; i++) {
        if (!islower(cstring[i])) {
            return false;
        }
    }
    return true;
}
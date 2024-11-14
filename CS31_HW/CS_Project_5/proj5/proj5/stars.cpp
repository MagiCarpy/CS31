#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
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
    
    1. The getWords function must return an int no greater than maxWords.
    If it returns a value less than 1, your main routine must write
    No words were loaded, so I can't play the game.

    2. Add randomize secret

    3. You must call getWords exactly once, before you start playing 
    any of the rounds of the game.

    4. The getWords function must return an int no greater than maxWords. 
    If it returns a value less than 1, your main routine must write:
        No words were loaded, so I can't play the game.

    5. Your program must call this function to play each round of the 
    game. Notice that this function does not select a random number 
    and does not tell the user the length of the secret word; the 
    caller of this function does, and passes the random number as 
    the third argument. Notice also that this function does not write 
    the message about the player successfully determining the secret word;
   */
    char wordlist[MAXWORDS][MAXWORDLEN + 1];
    int numWords = 12; // FIXME: is required?
    int n = getWords(wordlist, numWords, WORDFILENAME);
    for (int i = 0; i < 12; i++) {
        cout << wordlist[i] << " ";
    }
    cout << endl << endl;

    // DEL: main routine

    if (n < 1) {
        cout << "No words were loaded, so I can't play the game.";
    }

    cout << "How many rounds do you want to play? ";
    int totalRounds;
    cin >> totalRounds;
    cin.ignore(1000, '\n');
    if (totalRounds <= 0) {
        cout << "The number of rounds must be positive.";
    }

    // DEL: store stuff about stats
    int roundNum = 0;
    while (roundNum < totalRounds) {
        roundNum++;
        int secretRandInt; // random int/index for secret
        secretRandInt = randInt(0, numWords-1); // FIXME: figure out numWords

        cout << endl << "Round " << roundNum << endl;
        cout << "The secret word is " << strlen(wordlist[secretRandInt]) << " letters long." << endl;
        int score = runOneRound(wordlist, MAXWORDS, secretRandInt);
        if (score == 1) {
            cout << "You got it in " << score << " try." << endl;
        }
        else {
            cout << "You got it in " << score << " tries." << endl;
        } 
        /* DEL: The average number of trials must be written with a decimal
           point and exactly two digits to the right of the decimal point. 
        */
    }

        

}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    if (nWords < 0 || wordnum >= nWords) {
        return -1;
    }
    char trialInp[100];
    int score = 0;
    for (;;) {
        /*
        DEL: Notice that unknown words and trial strings that don't consist of 
        exactly 4 to 6 lower case letters don't count toward the number 
        of tries for a round. The average number of trials must be 
        written with a decimal point and exactly two digits 
        to the right of the decimal point.
        */
        cout << "Trial word: ";
        cin.getline(trialInp, 100);
        if (strlen(trialInp) > MAXWORDLEN || strlen(trialInp) < MINWORDLEN || !stringIsLower(trialInp)) {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        if (!inValidWords(words, nWords, trialInp)) {
            cout << "I don't know that word." << endl;
            continue;
        }
        if (strcmp(words[wordnum], trialInp) == 0) {
            score++;
            break;
        }

        calcPlanetStars(trialInp, words[wordnum]);
        score++;
    }
    
    return score;
}

void calcPlanetStars(const char trialWord[], const char secret[]) {
    // copy made to keep track of matched planets and stars
    char secretCopy[MAXWORDLEN+1]; // FIXME: change length == secret max length?
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
        // FIXME: check diff secret/trial len (ex. secret: egret trial: egrett ask)
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

bool inValidWords(const char words[][MAXWORDLEN+1], int nWords, const char cstring[]) {
    for (int i = 0; i < nWords; i++) {
        if (strcmp(words[i],cstring) == 0) {
            return true;
        }
    }
    return false;
}

bool stringIsLower(const char cstring[]) {
    for (int i = 0; cstring[i] != '\0'; i++) {
        if (!islower(cstring[i])) {
            return false;
        }
    }
    return true;
}
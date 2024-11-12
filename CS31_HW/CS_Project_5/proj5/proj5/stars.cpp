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
    1. The getWords function must return an int no greater than maxWords.
    If it returns a value less than 1, your main routine must write
    No words were loaded, so I can't play the game.

    2. Add randomize secret
   */
    char wordlist[MAXWORDS][MAXWORDLEN + 1];
    int numWords = 20; // FIXME: is required?
    int n = getWords(wordlist, 12, WORDFILENAME);
    for (int i = 0; i < 12; i++) {
        cout << wordlist[i] << " ";
    }
    cout << endl;
    int x = runOneRound(wordlist, MAXWORDS, 0);
    cout << "SCORE: " << x;
}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum) {
    if (nWords < 0 || wordnum >= nWords) {
        return -1;
    }
    char trialInp[100];
    int score = 0;
    for (;;) {
        /*
        Notice that unknown words and trial strings that don't consist of 
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
    char secretCopy[10]; // FIXME: change length == secret max length?
    strcpy(secretCopy, secret);

    int stars = 0;
    int planets = 0;
    for (int i = 0; trialWord[i] != '\0'; i++) {
        // FIXME: check diff secret/trial len (ex. secret: egret trial: egrett ask)
        if (i < strlen(trialWord) && trialWord[i] == secretCopy[i]) {
            stars++;
            // period signifies already matched star
            secretCopy[i] = '.';
        }
        else {
            // check if current char is in secretCopy
            for (int j = 0; secretCopy[j] != '\0'; j++) {
                if (secretCopy[j] == trialWord[i]) {
                    planets++;
                    // period signifies already matched planet
                    secretCopy[j] = '.';
                    break;
                }
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
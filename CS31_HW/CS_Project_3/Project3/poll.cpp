#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

/*
Your assignment is essentially to take a poll
data string and a party letter (in either upper 
or lower case), and compute the number of 
electoral votes the poll data string predicts 
the candidate of that party will get. For example, 
in the poll data string R40TXD54CAr6Msd28nYL06UT 
the predicted number of votes for the party D is 
82 (54 from CA plus 28 from NY); for the party r 
it's 46 (40 from TX plus 6 from MS); for the party 
L it's 6 (from UT). 

!!!COMPARE WITH FAQ and SPEC!!!
!!!CHECK ALL THE COMMENTS!!!
!!!MAKE SURE TO CHECK BEFORE FINAL SUBMISSIONS!!!
*/
bool hasRightSyntax(string pollData);
int computeVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
bool checkVoteSegment(string pollData, int& index);

int main() {
    // TEST CASES

    //hasRightSyntax Function
    //Valid Input
    assert(hasRightSyntax("")); // empty string
    assert(hasRightSyntax("R40TX")); // single vote segment
    assert(hasRightSyntax("R5TX")); // single digit vote amount 
    assert(hasRightSyntax("d25txl5cA")); // mixed cases for state code and party
    assert(hasRightSyntax("g0NYl05MI")); // zero votes and padding with 0
    assert(hasRightSyntax("R40TXD54CAr6Msd28nYL06UT")); // poll with multiple valid segments

    //Invalid Input
    assert(!hasRightSyntax(" ")); // space rather than empty string
    assert(!hasRightSyntax("R4")); // no state code
    assert(!hasRightSyntax("D4T")); // incomplete state code
    assert(!hasRightSyntax("D45LL")); // bad state code
    assert(!hasRightSyntax("D45TXD")); // more than 3 char state code
    assert(!hasRightSyntax("40TX")); // no party
    assert(!hasRightSyntax("RTX")); // no vote amount
    assert(!hasRightSyntax("R111TX")); // more than 3 digit vote amount
    assert(!hasRightSyntax("R40MX D54CA")); // space in middle of poll data
    assert(!hasRightSyntax("R40TX:D54CA")); // char in middle of poll data
    assert(!hasRightSyntax("R40TXaD54CA")); // alphabetic char in middle of poll data
    assert(!hasRightSyntax("R40TXD54CA ")); // test space after poll data

    int votes = 0;
    votes = -999;    // so we can detect whether computeVotes sets votes
    assert(computeVotes("R40TXD54CAr6Msd28nYL06UT", 'd', votes) == 0 && votes == 82);
    votes = -999;    // so we can detect whether computeVotes sets votes
    assert(computeVotes("R40TXD54CA", '%', votes) == 3 && votes == -999);
    cout << "All tests succeeded" << endl;

    /*
    cout << "VALUE: " << hasRightSyntax("D0CA"); //DEL
    cout << endl << "VALUE: " << computeVotes("R40TXD54CAr6Msd28nYL06UT", 'R', votes) << endl;
    cout << "VOTES: " << votes;
    */
}

// Modifies voteCount argument to a specific party's total number of votes
int computeVotes(string pollData, char party, int& voteCount) {
    // to keep voteCount unmodified for the 3 special cases
    int totalVotes = 0;

    // checks if pollData is valid sequence
    if (!hasRightSyntax(pollData)) {
        return 1;
    }

    // checks if valid party char
    if (!isalpha(party)) {
        return 3;
    }

    int index = 0;
    while (index != pollData.size()) {
        // checks if correct party char for each segment
        char startChar = pollData.at(index);
        if (static_cast<char>(tolower(party)) == static_cast<char>(tolower(startChar))) { //FIXME: ADD THIS CASTING SYNTAX EVERYWHERE???
            index++;
            string numVotes;
            for (numVotes = ""; isdigit(pollData.at(index)); index++) {
                numVotes += pollData.at(index);
            }
            // check if any state has 0 votes
            if (stoi(numVotes) == 0) {
                return 2;
            }
            // add to temporary total vote counter
            totalVotes += stoi(numVotes);

            // index past digit -> goto next party index
            index += 2;
        } else {
            // goto to the next segment
            index++;
            while (isdigit(pollData.at(index))) {
                index++;
            }
            index += 2;
        }
    }
    // modify referenced voteCount count is successful
    voteCount = totalVotes;
    return 0;
}

// Checks whether parameter pollData meets definition/syntax
bool hasRightSyntax(string pollData) {
    if (pollData == "") {
        return true;
    }

    int index = 0;
    while (index != pollData.size()) {
        // check if each poll sequence is valid (party, votes, state)
        if (!checkVoteSegment(pollData, index)) {
            return false;
        }
    }
    return true;
}

// Checks whether each segment of pollData meets definition/syntax
bool checkVoteSegment(string pollData, int& index) {
    char startChar = pollData.at(index);
    if (isalpha(startChar)) {
        index++;
    } else {
        return false;
    }

    // index past the party -> check number of votes
    string numVotes;
    if (index == pollData.size() || !isdigit(pollData.at(index))) {
        return false;
    }
    for (numVotes = ""; index != pollData.size() && numVotes.size() < 2 && isdigit(pollData.at(index)); index++) {
        numVotes += pollData.at(index);
    }

    // index past the digits for numVote -> check state
    string stateCode;
    if (index == pollData.size() || !isalpha(pollData.at(index))) {
        return false;
    }
    for (stateCode = ""; index != pollData.size() && stateCode.size() < 2 && isalpha(pollData.at(index)); index++) {
        stateCode += toupper(pollData.at(index));
    }

    // index ready to next check next poll sequence
    return isValidUppercaseStateCode(stateCode);
}

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.
// borrowed from "web.cs.ucla.edu"
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
        stateCode.find('.') == string::npos &&  // no '.' in stateCode
        codes.find(stateCode) != string::npos);  // match found
}
#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool hasRightSyntax(string pollData);
int computeVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
bool checkVoteSegment(string pollData, int& index);

int main() {
    // TEST CASES
    // 
    // Assume valid vote digit syntax is any from 0-99
    // 
    //hasRightSyntax Function
    //Valid Input
    assert(hasRightSyntax("")); // empty string
    assert(hasRightSyntax("R40TX")); // single vote segment
    assert(hasRightSyntax("R5TX")); // single digit vote amount 
    assert(hasRightSyntax("d25txl5cA")); // mixed cases for state code and party
    assert(hasRightSyntax("g0NYl05MI")); // zero votes and padding with 0
    assert(hasRightSyntax("D54CAD40TXr6MsD28nYL06uT")); // poll with multiple valid segments
    assert(hasRightSyntax("D54CAD40TXA6MsF28nYP08HI")); // valid alternative party chars
    assert(hasRightSyntax("D54CAD40TXA66MsF28nYP99HI")); // valid syntax for incorrect electoral vote amount

    //Invalid Input
    assert(!hasRightSyntax(" ")); // space rather than empty string
    assert(!hasRightSyntax("R")); // only party
    assert(!hasRightSyntax("R4")); // no state code
    assert(!hasRightSyntax("D4T")); // incomplete state code
    assert(!hasRightSyntax("D45LL")); // bad state code
    assert(!hasRightSyntax("D45TXD")); // more than 2 char state code
    assert(!hasRightSyntax("40TX")); // no party
    assert(!hasRightSyntax("RTX")); // no vote amount
    assert(!hasRightSyntax("R111TX")); // more than 3 digit vote amount
    assert(!hasRightSyntax("R40MX D54CA")); // space in middle of poll data
    assert(!hasRightSyntax("R40TX:D54CA")); // char in middle of poll data
    assert(!hasRightSyntax("R40TXaD54CA")); // alphabetic char in middle of poll data
    assert(!hasRightSyntax("R40TXD54CA ")); // test space after poll data
    assert(!hasRightSyntax(" R40TXD54CA")); // test space leading poll data
    assert(!hasRightSyntax("waddw213vdaw12341dwav%#@%#@")); // completely random string


    //computeVotes Function
    int votes;
    votes = -999;
    // valid poll data returns 0 and modifies votes correctly
    assert(computeVotes("R54CAD40TXr6MsD28nYL06uT", 'r', votes) == 0 && votes == 60);
    votes = -999;
    // valid if other alphabetic party chars
    assert(computeVotes("R54CAD40TXr6MsD28nYL06uT", 'l', votes) == 0 && votes == 6);
    votes = -999;
    // invalid poll data string, returns 1 and keeps votes unmodified
    assert(computeVotes("R40TX@@@D54CA", 'R', votes) == 1 && votes == -999);
    assert(computeVotes("WAAAAAAAAA", 'D', votes) == 1 && votes == -999);
    votes = -999;
    // invalid if atleast one state has 0 votes, returns 2 and keeps votes unmodified  
    assert(computeVotes("R0TXD54CA", 'R', votes) == 2 && votes == -999);
    votes = -999;
    assert(computeVotes("R0TXD54CA", 'D', votes) == 2 && votes == -999);
    votes = -999;
    assert(computeVotes("R28nYL06UTD0CA", 'L', votes) == 2 && votes == -999);
    votes = -999;
    // return 3 and keeps votes unmodified if party char is not letter
    assert(computeVotes("R40TXD54CA", '%', votes) == 3 && votes == -999);
    assert(computeVotes("R40TXD54CA", '.', votes) == 3 && votes == -999);
    assert(computeVotes("R40TXD54CA", ' ', votes) == 3 && votes == -999);

    cout << "All tests succeeded" << endl;

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
        if (static_cast<char>(tolower(party)) == static_cast<char>(tolower(startChar))) {
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
            // goto to the next segment while checking for 0 votes
            index++;
            string numVotes;
            for (numVotes = ""; isdigit(pollData.at(index)); index++) {
                numVotes += pollData.at(index);
            }
            // check if any state has 0 votes
            if (stoi(numVotes) == 0) {
                return 2;
            }

            // index past digit -> goto next party index
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
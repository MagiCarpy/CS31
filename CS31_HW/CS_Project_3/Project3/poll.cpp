#include <iostream>
#include <string>
#include <cctype>
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
*/
bool hasRightSyntax(string pollData);
int computeVotes(string pollData, char party, int& voteCount);
bool isValidUppercaseStateCode(string stateCode);
bool checkVotes(string pollData, int& index);

int main() {
    cout << "VALUE: " << hasRightSyntax("R40TXD54CAr6Msd28nYL06UT"); //DEL
}

// returns true if parameter pollData meets definition
bool hasRightSyntax(string pollData) {
    if (pollData == "") {
        return true;
    }

    //R40TXD54CA EXAMPLE DELETE
    int index = 0;
    while (index != pollData.size()) {
        cout << "*" << pollData << "*"; //DEL
        cout << " LOOP:" << index << " "; //DEL
        //check if each poll sequence is valid (party, votes, state)
        if (!checkVotes(pollData, index)) {
            return false;
        }
    }
    return true;
}

int computeVotes(string pollData, char party, int& voteCount) {
    return 1;
}

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.
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

bool checkVotes(string pollData, int& index) {
    char firstChar = pollData.at(index);
    if (isalpha(firstChar)) {
        index++;
    } else {
        return false;
    }
    cout << "vote:" << index; //DEL
    // index past the party -> check number of votes
    string numVotes;
    // FIXME: Ask if second conditional is required for no vote input (EX. D0CA -> DCA)
    if (index == pollData.size() || !isdigit(pollData.at(index))) {
        return false;
    }
    for (numVotes = ""; index != pollData.size() && numVotes.size() < 2 && isdigit(pollData.at(index)); index++) {
        numVotes += pollData.at(index);
    }
    cout << " digit:" << index; //DEL
    // index past the digits for numVote -> check state
    string stateCode;
    if (index == pollData.size() || !isalpha(pollData.at(index))) {
        return false;
    }
    for (stateCode = ""; index != pollData.size() && stateCode.size() < 2 && isalpha(pollData.at(index)); index++) {
        stateCode += toupper(pollData.at(index));
    }
    cout << " final:" << index << endl; //DEL
    // index ready  to next check next poll sequence
    return isValidUppercaseStateCode(stateCode);
}
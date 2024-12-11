#include <iostream>
#include <string>
using namespace std;

int main() {
	// constants
	const double FIRST100_RATE = 0.33;
	const double NEXT500_WINTERRATE = 0.33;
	const double NEXT500_OTHERRATE = 0.27;
	const double AFTER600_RATE = 0.21;

	// prompt user inputs
	int odometerStart;
	cout << "Odometer at start: ";
	cin >> odometerStart;

	int odometerEnd;
	cout << "Odometer at end: ";
	cin >> odometerEnd;

	int rentalDays;
	cout << "Rental days: ";
	cin >> rentalDays;
	cin.ignore(1000, '\n');

	string customerName;
	cout << "Customer name: ";
	getline(cin, customerName);

	string luxuryStatus;
	cout << "Luxury car? (y/n): ";
	getline(cin, luxuryStatus);

	int startMonth;
	cout << "Starting month (1=Jan, 2=Feb, etc.): ";
	cin >> startMonth;
	cin.ignore(1000, '\n');


	// input error checking and output
	if (odometerStart < 0) {
		cout << "---" << endl;
		cout << "The starting odometer reading must not be negative.";
	}
	else if (odometerEnd < odometerStart) {
		cout << "---" << endl;
		cout << "The ending odometer reading must be at least as large as the starting reading.";
	}
	else if (rentalDays <= 0) {
		cout << "---" << endl;
		cout << "The number of rental days must be positive.";
	}
	else if (customerName.length() == 0) {
		cout << "---" << endl;
		cout << "You must enter a customer name.";
	}
	else if (luxuryStatus != "y" && luxuryStatus != "n") {
		cout << "---" << endl;
		cout << "You must enter y or n.";
	}
	else if (!(startMonth >= 1 && startMonth <= 12)) {
		cout << "---" << endl;
		cout << "The month number must be in the range 1 through 12.";
	}
	// final amount calculations and output
	else {
		double amount;
		int baseCharge;

		// daily baseCharge determined by luxury car or not
		if (luxuryStatus == "n") {
			baseCharge = 45;
		}
		else {
			baseCharge = 75;
		}

		amount = baseCharge * rentalDays;

		// calculate rates for first 100, 100 to 600, and greater than 600 miles driven
		int milesDriven = odometerEnd - odometerStart;
		
		if (milesDriven <= 100) {
			amount += milesDriven * FIRST100_RATE;
		}
		else if (milesDriven <= 600) {
			amount += 100 * FIRST100_RATE;
		}
		else {
			amount += 100 * FIRST100_RATE;
			amount += (milesDriven - 600) * AFTER600_RATE;
		}

		// calculates month based rates from 100 to 600 miles driven
		if (milesDriven > 100) {
			if (startMonth == 12 || (startMonth >= 1 && startMonth <= 3)) {
				if (milesDriven < 600) {
					amount += (milesDriven - 100) * NEXT500_WINTERRATE;
				}
				else {
					amount += 500 * NEXT500_WINTERRATE;
				}
			}
			else {
				if (milesDriven < 600) {
					amount += (milesDriven - 100) * NEXT500_OTHERRATE;
				}
				else {
					amount += 500 * NEXT500_OTHERRATE;
				}
			}
		}
		// final output message if no user input errors
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "---" << endl;
		cout << "The rental charge for " << customerName << " is $" << amount;
	}
}
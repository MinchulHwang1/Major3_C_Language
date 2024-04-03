/*
* FILE : m3.cpp
* PROJECT : Major 3
* PROGRAMMER : Minchul Hwang
* FIRST VERSION : 2023-04-10
* Description : This project originates from focused 1.2 and Major 1
				From focused 1, the function has a condition that can be changed.
				From focused 2, the function to get fare has been added.
				From Major 1, the modification of fare has been added.
				The user's input can be received indefinitely, and if a . is entered at any position,
				the input is terminated and the data received up to the previous time is output. (ascending list fare and destination)
				and the program get destination and date.
				if user input correct destination and date, the indication of fare input has come.
				if user input fare, destination list is changed as input fare which is included with destination and date.
				and then the fare list will be changed as ascending list, ans print the list.
				other different things from Major1, this project must use multimap to searching and modify.
				the language style changes c into c++
* 
*/
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<map>
#include<algorithm>

using namespace std;
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#define kContinue				1
#define kIgnore					1000

struct ascendByDestination {
	bool operator()(const string& leftHandSide, const string& rightHandSide) const {
		return leftHandSide < rightHandSide;
	}
} ;

struct ascendByFare {
	bool operator()(const float& leftHandSide, const float& rightHandSide) const {
		return leftHandSide < rightHandSide;
	}
};

struct FlightInfo {
	string destination;
	string date;
	float fare = 0;
} ;

int main() {
	typedef multimap<string, FlightInfo, ascendByDestination> ascendByDesti;
	typedef multimap<float, FlightInfo, ascendByFare> ascendByFareRate;
	ascendByDesti destiMap;
	ascendByFareRate fareMap;

	FlightInfo flight;

	float getFare = 0.00;
		
	while (kContinue) {

		cout << fixed;
		cout.precision(2);		// Make floating number under 2 from .

		cout << "Destination : ";
		getline(cin, flight.destination);
		if (flight.destination == ".") {			// Finishing to get destination until get '.'
			break;
		}

		cout << "Date : ";
		getline(cin, flight.date);

		if (flight.date == "."){					// Finishing to get date until get '.'
			break;
		}
	
		cout << "Fare : "; 
		cin >> flight.fare;
		
		if (cin.fail() == 1) {
			flight.fare = 0;
			cin.clear();
		}
		cin.ignore(kIgnore, '\n');

		// Insert pair into each map
		destiMap.insert(make_pair(flight.destination, flight));
		fareMap.insert(make_pair(flight.fare, flight));
	}
	
	// Sorted by Fare
	cout << endl;
	cout << "Sorted by Fare : " << endl;
	for (ascendByFareRate::const_iterator startOfFare = fareMap.begin(), finishOfFare = fareMap.end(); startOfFare != finishOfFare; ++startOfFare) {
		cout.width(35);
		cout << left << startOfFare->second.destination;
		cout.width(35);
		cout << left << startOfFare->second.date;
		cout << '$' << startOfFare->first << endl;
	}
	cout << endl;
	
	// Sorted by Destination
	cout << "Sorted by Destination : " << endl;
	for (ascendByDesti::const_iterator startOfDesti = destiMap.begin(), finishOfDesti = destiMap.end(); startOfDesti != finishOfDesti; ++startOfDesti) {
		cout.width(35);
		cout << left << startOfDesti->first;
		cout.width(35);
		cout << left << startOfDesti->second.date;
		cout << '$' << startOfDesti->second.fare << endl;
	}
	
	cout << endl;

	cout << "Insert the Destination you want to change :";
	cin >> flight.destination;
	cout << "Insert the Date :";
	cin >> flight.date;

	ascendByDesti::const_iterator pointOfDest;
	pointOfDest = destiMap.find(flight.destination);			// Save iterator pointerOfDest which the pointer in destiMap

	if (pointOfDest == destiMap.end()) {
		cout << "No matched destination!! " << endl;
	}
	else {
		if(pointOfDest->second.date != flight.date)
			cout << "No matched date!! " << endl;

		else {
			cout << "Old Fare : " << pointOfDest->second.fare << endl;;
			cout << "New Fare : ";
			cin >> flight.fare;
			cout << endl;
			
			// If there is matched pair, erase it and put new pair on that location
			destiMap.erase(flight.destination);
			destiMap.insert(make_pair(flight.destination, flight));
			
			cout << "New Sorted by Destination : " << endl;
			for (ascendByDesti::const_iterator newStartOfDesti = destiMap.begin(), newFinishOfDesti = destiMap.end(); newStartOfDesti != newFinishOfDesti; ++newStartOfDesti) {
				cout.width(35);
				cout << left << newStartOfDesti->first;
				cout.width(35);
				cout << left << newStartOfDesti->second.date;
				cout << '$' << newStartOfDesti->second.fare << endl;
			}
			cout << endl;

			ascendByFareRate::const_iterator pointOfFare = fareMap.begin();
			while (pointOfFare->second.destination != flight.destination) {
				pointOfFare++;
			}
				
			fareMap.erase(pointOfFare);
			fareMap.insert(make_pair(flight.fare, flight));
			cout << "New Sorted by Fare : " << endl;
			for (ascendByFareRate::const_iterator newStartOfFare = fareMap.begin(), newFinishOfFare = fareMap.end(); newStartOfFare != newFinishOfFare; ++newStartOfFare) {
				cout.width(35);
				cout << left << newStartOfFare->second.destination;
				cout.width(35);
				cout << left << newStartOfFare->second.date;
				cout << '$' << newStartOfFare->first << endl;
			}
			cout << endl;
		}
	}
	return 0;
}
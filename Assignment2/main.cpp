#include "activity.h"

#include <iostream>
using namespace std;

int main()
{
	//The activities array and count of activities (n)
	Activity activities[20];
	int n;

	//part A
	cout << "[A] Input activities from file\n";
	cout << "==============================\n";
	char inputString[50];
	cout << "Type the pathname of the input file: ";
	cin >> inputString;
	readFileOfActivities(activities, n, inputString);
	cout << endl;
	cout << n << " activities are extracted.\n\n\n";

	//part B
	cout << "[B] Display list of activities\n";
	cout << "==============================\n";
	displayActivitiesTable(activities,n);
	cout << endl << endl;

	//part C
	cout << "[C] Sort activities\n";
	cout << "===================\n";
	sortingChoice(activities,n);
	cout << endl << endl;

	//part D
	char startPartD;
	do{
		cout << "Do you want to continue to Part D?  [Y/N] ";
		cin >> startPartD;
	}while(startPartD!='Y' && startPartD!='N');
	if(startPartD=='Y')
		partDloop(activities, n);
	
	cout << "Thank you for using this program.\n\n\n";
	return 0;
}
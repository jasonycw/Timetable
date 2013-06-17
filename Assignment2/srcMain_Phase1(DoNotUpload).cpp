#include "activity.h"

#include <iostream>
using namespace std;

void main()
{
	//The activities array and count of activities (n)
	Activity activities[20];
	int n;

	cout << "[A] Input activities from file\n";
	cout << "==============================\n";
	readFileOfActivities(activities, n);
	cout << endl;
	cout << n << " activities are extracted.\n\n\n";

	cout << "[B] Display list of activities\n";
	cout << "==============================\n";

	for (int i=0;i<n;i++)
		cout << activities[i] << endl;
	cout << endl << endl;

	cout << "Thank you for using this program.\n\n";
}
#include "activity.h"

#include <iostream>
using namespace std;

void main()
{
	//The activities array and count of activities (n)
	Activity activities[20];
	int n;

	//For part D
	int id_found;
	int search_hh, search_mm;
	char dummy; //colon between search_hh and search_mm

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

	cout << "[C] Sort activities\n";
	cout << "===================\n";
	insertion_sort(activities,n);
	for (int i=0;i<n;i++)
		cout << activities[i] << endl;

	cout << endl << endl;

	cout << "[D] Search activities\n";
	cout << "=====================\n";
	cout << "Type a start time to search: ";
	cin >> search_hh >> dummy >> search_mm;

	if (binary_search(activities,n,search_hh,search_mm,id_found))
	{	cout << "\n";
		cout << activities[id_found] << "\n\n\n";
	}
	else
		cout << "\nNo activity is found.\n\n\n";


	cout << "Thank you for using this program.\n\n";
}
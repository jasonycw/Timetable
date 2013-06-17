#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <iostream>
using namespace std;

class Activity
{
private:
	int _startTime_hour;
	int _startTime_minute;
	int _endTime_hour;
	int _endTime_minute;
	int _timeDuration_inMinutes;
	char _description[26];
public:
	Activity();
	Activity(const int hour, const int minute, const int duration, const char description[]);
	Activity(const Activity &clone);

	//return member functions
	int startTime_hour() const;
	int startTime_minute() const;
	int endTime_hour() const;
	int endTime_minute() const;
	int timeDuration_inMinutes() const;
	char* description() const;

	void extendDuration(const int extendTime_inMinutes); //for increase duration

	//friend operators:
	friend istream &operator >>(istream &ins, Activity &activity);
	friend ostream &operator <<(ostream &outs, const Activity &activity);
	friend bool operator >(const Activity &activity1, const Activity &activity2);
	friend bool operator <(const Activity &activity1, const Activity &activity2);
	friend bool operator ==(const Activity &activity1, const Activity &activity2);

	//friend functions:
	friend void readFileOfActivities (Activity activities[], int &n, const char inputString[]); //for file I/O
	friend void displayActivitiesTable(const Activity activities[], const int n); //for displaying the time table
	friend bool binary_search(Activity activities[], int n, int lower, int upper, int hour, int minute, int &id_found); //binary searching
	friend bool search(const Activity activities[], const int n, const int hour, const int minute, int &id_found); //for searching normally
};

void swap(Activity &activity1, Activity &activity2); //swapping function
void insertion_sort(Activity activities[], const int n); //insertion sort by starting time
void sortByDuration(Activity activities[], const int n); //sort based by duration time
void sortingChoice(Activity activities[], const int n); //for user to choose the table to be sorted by starting time or duration length
void partDloop(Activity activities[], int n); //function for part D and creative design

#endif
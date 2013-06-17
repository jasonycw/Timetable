#include <iostream>
#include <iomanip>
#include <fstream>
#include "activity.h"
using namespace std;

bool inserted_sorting = false;

//default constructor - initialize everything to zero
Activity::Activity()
{
	_startTime_minute = 0;
	_startTime_hour = 0;
	_endTime_hour = 0;
	_endTime_minute = 0;
	_timeDuration_inMinutes = 0;
	_description[0] = 0;
}

//type convertion constructor - get from user for the start time, duration and description and calculate it's own end time
Activity::Activity(const int hour, const int minute, const int duration, const char description[])
{
	_startTime_minute = minute;
	_startTime_hour = hour;
	_timeDuration_inMinutes = duration;
	_endTime_minute = (_startTime_minute+_timeDuration_inMinutes) % 60;
	_endTime_hour =  _startTime_hour + (_startTime_minute+_timeDuration_inMinutes) / 60;
	strcpy(_description, description);
}

//copy constructor
Activity::Activity(const Activity &clone)
{
	_startTime_minute = clone._startTime_minute;
	_startTime_hour = clone._startTime_hour;
	_endTime_hour = clone._endTime_hour;
	_endTime_minute = clone._endTime_minute;
	_timeDuration_inMinutes = clone._timeDuration_inMinutes;
	strcpy(_description,clone._description);
}

//functions for return results
int Activity::startTime_hour() const
{
	return _startTime_hour;
}
int Activity::startTime_minute() const
{
	return _startTime_minute;
}
int Activity::endTime_hour() const
{
	return _endTime_hour;
}
int Activity::endTime_minute() const
{
	return _endTime_minute;
}
int Activity::timeDuration_inMinutes() const
{
	return _timeDuration_inMinutes;
}
char* Activity::description() const
{
	char *output = new char[26];
	strcpy(output, _description);
	return output;
}

//extend the duration of an activity
void Activity::extendDuration(const int extendTime_inMinutes)
{
	_timeDuration_inMinutes += extendTime_inMinutes;
	_endTime_minute = (_startTime_minute+_timeDuration_inMinutes) % 60;
	_endTime_hour =  _startTime_hour + (_startTime_minute+_timeDuration_inMinutes) / 60;
}

//input operator for Activity object
istream &operator >> (istream &ins, Activity &activity)
{
	char dummy, description[26];
	int startHour, startMinute, duration;

	ins >> startHour >> dummy >> startMinute >> duration;
	ins.get(dummy);
	ins.getline(description,26);

	activity = Activity(startHour, startMinute, duration, description);
	return ins;
}

//outstream operation in table form
ostream &operator <<(ostream &outs, const Activity &activity)
{
	//heading
	outs << " ------- ------- -------------------- ---------------------------" << endl;
	outs << "| Start |  End  |      Duration      |        Description        |" << endl;
	outs << " ------- ------- -------------------- ---------------------------" << endl;
	
	//the time informations
	outs << "| " << setw(2) << right << setfill('0') << activity._startTime_hour%24 << ":" << setw(2) << activity._startTime_minute << " | " << setw(2) << activity._endTime_hour%24 << ":" << setw(2) << activity._endTime_minute << setfill(' ') << " | ";
	
	//for different duration appearence
	if(activity._timeDuration_inMinutes<60)
		outs << setw(5) << " " << activity._timeDuration_inMinutes << " minutes    | ";
	else
	{
		if(activity._timeDuration_inMinutes%60)
		{
			outs << " " << activity._timeDuration_inMinutes/60 << " hour";
			outs << " " << setw(2) << activity._timeDuration_inMinutes%60 << " minutes | ";
		}
		else
			outs << setw(6) << " " << activity._timeDuration_inMinutes/60 << " hour       | ";
	}

	//description
	outs << setw(26) << left << activity._description << "|" << right << endl;
	outs << " ------- ------- -------------------- ---------------------------" << endl;
	return outs;
}

//compare operator for two activities if activity1 is larger than activity2
bool operator >(const Activity &activity1, const Activity &activity2)
{
	int duration1 = activity1._startTime_hour*60 + activity1._startTime_minute;
	int duration2 = activity2._startTime_hour*60 + activity2._startTime_minute;
	if(duration1>duration2)
		return true;
	else
		return false;
}

//compare operator for two activities if activity1 is smaller than activity2
bool operator <(const Activity &activity1, const Activity &activity2)
{
	int duration1 = activity1._startTime_hour*60 + activity1._startTime_minute;
	int duration2 = activity2._startTime_hour*60 + activity2._startTime_minute;
	if(duration1<duration2)
		return true;
	else
		return false;
}

//compare operator for two activities if they are equal
bool operator ==(const Activity &activity1, const Activity &activity2)
{
	int duration1 = activity1._startTime_hour*60 + activity1._startTime_minute;
	int duration2 = activity2._startTime_hour*60 + activity2._startTime_minute;
	if(duration1==duration2)
		return true;
	else
		return false;
}

//function for file I/O for activities array, included checking
void readFileOfActivities (Activity activities[], int &counterForActivity, const char inputString[])
{
	ifstream inFile;
	inFile.open(inputString);
	
	//file validation
	if(inFile.fail())
	{
		cout << "No such file." << endl;
		exit(1);
	}

	counterForActivity=0;
	int n;

	//read file and checking
	while(!inFile.eof())
	{
		n = counterForActivity;
		inFile >> activities[n];
		if(!inFile.fail())
			//check hour
			if(activities[n]._startTime_hour>=0 && activities[n]._startTime_hour<24)
				//check minute
				if(activities[n]._startTime_minute>=0 && activities[n]._startTime_minute<60)
					//check duration
					if(activities[n]._timeDuration_inMinutes>=0)
						//check over-run
						if(activities[n]._startTime_hour+(activities[n]._timeDuration_inMinutes/60)<24)
							if(activities[n]._startTime_hour!=23 || (activities[n]._startTime_hour==23 && activities[n]._startTime_minute+activities[n]._timeDuration_inMinutes<60))
								counterForActivity++;
	}
	inFile.close();
}

//display an array of activity in table form
void displayActivitiesTable(const Activity activities[], const int n)
{
	int startHour,startMinute,endHour,endMinute,duration;

	//heading
	cout << " ------- ------- -------------------- ---------------------------" << endl;
	cout << "| Start |  End  |      Duration      |        Description        |" << endl;
	cout << " ------- ------- -------------------- ---------------------------" << endl;

	//loop the table
	for (int i=0;i<n;i++)
	{
		startHour = activities[i]._startTime_hour%24;
		startMinute = activities[i]._startTime_minute;
		endHour = (activities[i]._startTime_hour + (activities[i]._startTime_minute+activities[i]._timeDuration_inMinutes) / 60)%24;
		endMinute = (activities[i]._startTime_minute+activities[i]._timeDuration_inMinutes) % 60;
		duration = activities[i]._timeDuration_inMinutes;

		//the time informations
		cout << "| " << setw(2) << right << setfill('0') << startHour << ":" << setw(2) << startMinute << " | " << setw(2) << endHour << ":" << setw(2) << endMinute << setfill(' ') << " | ";
		
		//for different duration appearence
		if(duration<60)
			cout << setw(5) << " " << duration << " minutes    | ";
		else
		{
			if(activities[i]._timeDuration_inMinutes%60)
			{
				cout << " " << duration/60 << " hour";
				cout << " " << setw(2) << duration%60 << " minutes | ";
			}
			else
				cout << setw(6) << " " << duration/60 << " hour       | ";
		}

		//description
		cout << setw(26) << left << activities[i]._description << "|" << right << endl;
		cout << " ------- ------- -------------------- ---------------------------" << endl;
	}
	
}

//binary searching with starting hour and minutes
bool binary_search(Activity activities[], int n, int lower, int upper, int hour, int minute, int &id_found)
{
	if(inserted_sorting == false)
	{
		insertion_sort(activities, n);
		//restore inserted_sorting global variable to false after insertion sorting
		inserted_sorting = false;
	}

	//sorting recurtion
	Activity wanted(hour,minute,0,"dummy");
	if(lower>upper || activities[lower]>wanted||activities[upper]<wanted)
	{
		id_found = -1;
		return false;
	}
	else
	{
		int mid = (lower+upper)/2;
		bool result;
		if(activities[mid] == wanted)
		{
			id_found = mid;
			return true;
		}
		if(activities[mid]>wanted)
			result = binary_search(activities, n, lower, mid-1, wanted._startTime_hour, wanted._startTime_minute, id_found);
		if(wanted>activities[mid])
			result = binary_search(activities, n, mid+1, upper, wanted._startTime_hour, wanted._startTime_minute, id_found);
		return result;
	}

	//restore to duration sorting if it is not insert sorting
	if(inserted_sorting == false)
		sortByDuration(activities, n);
	return false;
}

//direct search if the time is in the duration of an activity
bool search(const Activity activities[], const int n, const int hour, const int minute, int &id_found)
{
	for(int i=0;i<n;i++)
	{
		//the hour is in bound
		if(hour>activities[i]._startTime_hour && hour<activities[i]._endTime_hour)
		{
			id_found = i;
			return true;
		}

		//the hour is the same as start hour and minutes is in bound
		else if(hour==activities[i]._startTime_hour && minute>activities[i]._startTime_minute && minute<(activities[i]._startTime_minute+activities[i]._timeDuration_inMinutes))
		{
			id_found = i;
			return true;
		}

		//the hour is near the end time and minutes is in bound
		else if(activities[i]._startTime_hour!=activities[i]._endTime_hour && hour==activities[i]._endTime_hour && minute<activities[i]._endTime_minute)
		{
			id_found = i;
			return true;
		}

		//the hour is near the end time and minutes is in bound for duration shorter than 60min
		else if(hour==activities[i]._endTime_hour && minute>activities[i]._startTime_minute && minute<activities[i]._endTime_minute)
		{
			id_found = i;
			return true;
		}
	}
	return false;
}

//swaping two activities
void swap(Activity &activity1, Activity &activity2)
{
	Activity temp = activity1;
	activity1 = activity2;
	activity2 = temp;
}

//insertion sorting function using activity start time
void insertion_sort(Activity activities[], const int n)
{
	for(int i=0;i<n;i++)
	{
		int j=i;
		while(j>0 && activities[j-1]>activities[j])
		{
			swap(activities[j-1],activities[j]);
			j--;
		}
	}
	inserted_sorting = true;
}

//sorting by duration
void sortByDuration(Activity activities[], const int n)
{
	for(int i=0;i<n;i++)
	{
		int j=i;
		while(j>0 && activities[j-1].timeDuration_inMinutes()>activities[j].timeDuration_inMinutes())
		{
			swap(activities[j-1],activities[j]);
			j--;
		}
	}
	inserted_sorting = false;
}

//for user to choose the table to be sorted by starting time or duration length
void sortingChoice(Activity activities[], const int n)
{
	char inputString[10];
	do{//input loop
		cout << "What kind of sorting do you want? Sort by starting time or duration?" << endl;
		cout << "[time] or [duration]              ";
		cin >> inputString;
	}while( strcmp(inputString, "time") && strcmp(inputString, "duration") );

	//sort by choice
	if(!strcmp(inputString, "time"))
		insertion_sort(activities,n);
	else if(!strcmp(inputString, "duration"))
		sortByDuration(activities,n);

	cout << endl;
	displayActivitiesTable(activities,n);
}

//ask if the user want to display the table
void choiceToDisplayTable(const Activity activities[], const int n)
{
	char input;
	do{//input loop
		cout << "Do you want to see the new time table? [Y/N] ";
		cin >> input;
	}while(input!='Y'&&input!='N');
	cout << endl;
	if(input=='Y')
		displayActivitiesTable(activities, n);
}

//search for an activity with the start time
void searchActivities(Activity activities[], const int n)
{
	int id_found;
	int search_hh, search_mm;
	char dummy, inputString[26];

	cout << "  Search activities\n";
	cout << "=====================\n";
	do{//input loop
		cout << "Do you want to search starting time or description?" << endl;
		cout << "[time] or [description]        ";
		cin >> inputString;
	}while( strcmp(inputString, "time") && strcmp(inputString, "description") );

	//search by time
	if(!strcmp(inputString, "time"))
	{
		cout << "Type in the starting time to search: ";
		cin >> search_hh >> dummy >> search_mm;
		if (binary_search(activities,n,0,n-1,search_hh,search_mm,id_found))
			cout << "\n" << activities[id_found];
		else
			cout << "\nNo activity is found.\n";
	}

	//search by description
	else if(!strcmp(inputString, "description"))
	{
		bool found = false;
		cout << "Type in the description to search: ";
		cin.get(dummy);
		cin.getline(inputString,26);
		for(int i=0;i<n;i++)
			if( !strcmp(inputString, activities[i].description()) )
			{
				cout << endl << activities[i];
				found = true;
			}
		if(!found)
			cout << "\nNo activity is found.\n";
	}
}

//increase the duration of a specified activity
void extendActivities(Activity activities[], const int n)
{
	int userInput;
	cout << "  Extend activities\n";
	cout << "=====================\n";
	int x;
	do{//input loop
		cout << "Which activity do you want to extend? (1-" << n << ") ";
		cin >> x;
	}while(!(x>0 && x<=n));

	cout << "How many minutes do you want to extend? ";
	cin >> userInput;

	activities[x-1].extendDuration(userInput);

	//sort again only if the table is sorted by duration
	if(inserted_sorting == false)
		sortByDuration(activities, n);
	cout << "\tDone!" << endl;
	choiceToDisplayTable(activities, n);
}

//add another activity into the activities array
void addingActivities(Activity activities[], int& n)
{
	bool added = false;
	int startHour, startMinutes, duration, x;
	char description[26], dummy;
	description[0] = 0;
	cout << "  Adding activities\n";
	cout << "=====================\n";
	//if the table is already full, reject
	if(n==20)
		cout << "The list is already full, sorry." << endl;
	else
	{
		//repeat until an activity is added
		do{
			do{//input loop
				cout << "Starting time (hh:mm): ";
				cin >> startHour >> dummy >> startMinutes;
			}while(!(startHour>=0&&startHour<24&&startMinutes>=0&&startMinutes<60));
			
			//check for time conflicts
			if(binary_search(activities, n, 0, n-1, startHour, startMinutes, x))
				cout << "Conflicted time with the following activity." << endl << activities[x] << endl;
			else if(search(activities, n, startHour, startMinutes, x))
				cout << "Conflicted time with the following activity." << endl << activities[x] << endl;

			//get the duration and description
			else
			{
				do{//input loop
					cout << "How many minutes does this activity continue? ";
					cin >> duration;
				}while(duration<=0);
				cout << "Enter activity description: ";
				cin.get(dummy);
				cin.getline(description,26);
				//add the new activity
				activities[n++] = Activity(startHour, startMinutes, duration, description);
				added = true;
				//sort the table
				if(inserted_sorting == true)
					insertion_sort(activities,n);
				else
					sortByDuration(activities,n);
				cout << "\tDone!" << endl;
				choiceToDisplayTable(activities, n);
			}
		}while(!added);
	}
}

//calculate a little bit of duration statistics
void showStatistics(Activity activities[], const int n)
{
	bool repeatShortActivity[20], repeatLongActivity[20];
	repeatShortActivity[0] = 1;
	repeatLongActivity[0] = 1;
	for(int i=1;i<20;i++)
	{
		repeatShortActivity[i] = 0;
		repeatLongActivity[i] = 0;
	}
	int shortestDuration = activities[0].timeDuration_inMinutes();
	int longestDuration = activities[0].timeDuration_inMinutes();
	int totalDuration = activities[0].timeDuration_inMinutes();

	cout << "  Display Satistics\n";
	cout << "=====================\n";

	for(int i=1;i<n;i++)
	{
		//add the total duration
		totalDuration += activities[i].timeDuration_inMinutes();

		//for checking the shortest time
		if(activities[i].timeDuration_inMinutes() == shortestDuration)
			repeatShortActivity[i] = 1;
		else if(activities[i].timeDuration_inMinutes() < shortestDuration)
		{
			for(int j=0;j<20;j++)
				repeatShortActivity[j] = 0;
			repeatShortActivity[i] = 1;
			shortestDuration = activities[i].timeDuration_inMinutes();
		}

		//for checking the longest time
		if(activities[i].timeDuration_inMinutes() == longestDuration)
			repeatLongActivity[i] = 1;
		else if(activities[i].timeDuration_inMinutes() > longestDuration)
		{
			for(int j=0;j<20;j++)
				repeatLongActivity[j] = 0;
			repeatLongActivity[i] = 1;
			longestDuration = activities[i].timeDuration_inMinutes();
		}
	}

	//show all the longest activities
	cout << "Longest activity: " << endl;
	for(int i=0;i<n;i++)
	{
		if(repeatLongActivity[i])
		{
			char *longestDurationActivityDescription = activities[i].description();
			cout << setw(5) << " \"" << longestDurationActivityDescription << "\"" << endl << activities[i] << endl;
			delete[] longestDurationActivityDescription;
		}
	}
	cout << endl << endl;

	//show all the shortest activities
	cout << "Shortest activity: " << endl;
	for(int i=0;i<n;i++)
	{
		if(repeatShortActivity[i])
		{
			char *shortestDurationActivityDescription = activities[i].description();
			cout << setw(5) << " \"" << shortestDurationActivityDescription << "\"" << endl << activities[i] << endl;
			delete[] shortestDurationActivityDescription;
		}
	}
	cout << endl << endl;

	//show the total time
	cout << "Total activities time is " << totalDuration << " minutes." << endl;
	cout << "That is " << totalDuration/60 << " hours and " << totalDuration%60 << " minutes." << endl;
}

//main loop for partD and the creative design
void partDloop(Activity activities[], int n)
{
	int userChoice;
	do{//start of part D loop
		system("cls");
		cout << "[D] Functions Choice" << endl;
		cout << "====================" << endl;
		cout << endl;
		displayActivitiesTable(activities,n);
		cout << endl;
		cout << "0 = print the activities table" << endl;
		cout << "1 = search for a activity" << endl;
		cout << "2 = extendTime for an activity" << endl;
		cout << "3 = adding a new activity" << endl;
		cout << "4 = show statistics about duration of activities" << endl;
		cout << "5 = user define sorting base" << endl;
		cout << "What do you want to do? (enter -1 to quit)  ";
		cin >> userChoice;
		cout << endl << endl;

		//use for running the selected function
		switch(userChoice)
		{
		case 0:
			displayActivitiesTable(activities, n);
			cout << endl << endl;
			system("pause");break;
		case 1:
			searchActivities(activities, n);
			cout << endl << endl;
			system("pause");break;
		case 2:
			extendActivities(activities, n);
			cout << endl << endl;
			system("pause");break;
		case 3:
			addingActivities(activities, n);
			cout << endl << endl;
			system("pause");break;
		case 4:
			showStatistics(activities, n);
			cout << endl << endl;
			system("pause");break;
		case 5:
			cout << " Choose sorting base\n";
			cout << "=====================\n";
			sortingChoice(activities, n);
			cout << endl << endl;
			system("pause");break;
		}
	}while(userChoice!=-1);
}
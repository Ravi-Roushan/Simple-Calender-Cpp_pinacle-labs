#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <map>
#include <string>

using namespace std;

map<pair<int, int>, string> events;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void addEvent() {
    int month, day;
    string event;

    cout << "Enter month (1-12): ";
    cin >> month;
    cout << "Enter day: ";
    cin >> day;
    cin.ignore(); 

    cout << "Enter the event description: ";
    getline(cin, event); 

    
    events[{month, day}] = event;
    cout << "Event added successfully!" << endl;
}

void viewEvent(int month, int day) {
    if (events.find({month, day}) != events.end()) {
        cout << "Event on " << month << "/" << day << ": " << events[{month, day}] << endl;
    } else {
        cout << "No events for this date." << endl;
    }
}

void printCalendar(int year) {
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int mDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    string monthList[] = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};

    cout << "  --------------------------------" << endl;
    cout << "           Calendar - " << year << endl;
    cout << "  --------------------------------" << endl << endl;

    int days;
    int current;

    
    int y = year - 1;
    current = (y + y / 4 - y / 100 + y / 400 + t[0] + 1) % 7;

    for (int i = 0; i < 12; i++) {
        if (i == 1) {  
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                days = 29;
            else
                days = mDays[i];
        } else {
            days = mDays[i];
        }

        cout << endl << "  ------------" << monthList[i] << "-------------" << endl;
        cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

    
        int k;
        for (k = 0; k < current; k++)
            cout << "     ";

        
        for (int j = 1; j <= days; j++) {
            cout << setw(5) << j;

            
            if (events.find({i + 1, j}) != events.end()) {
                cout << "*";  
            }

            k++;
            if (k > 6) { 
                k = 0;
                cout << endl;
            }
        }

        if (k)  
            cout << endl;

        current = k;  
    }
}

int main() {
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int year = 1900 + local_time->tm_year;
    char option;

    do {
        clearScreen();
        printCalendar(year);

        cout << endl << endl;
        cout << "Press: " << endl;
        cout << "- n for next year" << endl;
        cout << "- p for previous year" << endl;
        cout << "- a to add an event" << endl;
        cout << "- v to view an event" << endl;
        cout << "- e for exit" << endl;
        cin >> option;

        switch (option) {
            case 'n':  
                year++;
                break;
            case 'p': 
                year--;
                break;
            case 'a':  
                addEvent();
                break;
            case 'v': 
                int month, day;
                cout << "Enter month (1-12): ";
                cin >> month;
                cout << "Enter day: ";
                cin >> day;
                viewEvent(month, day);
                break;
        }
    } while (option != 'e' && option != 'E');  
    return 0;
}

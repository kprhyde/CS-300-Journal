//============================================================================
// Name        : Project2.8.cpp
// Author      : Kevin Rhyden
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project 2
//============================================================================

#include <cstdlib> // avoids potential naming conflicts and helps us stoi
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#define TABLE_SIZE 8

using namespace std;

// Course object structure
struct Course {
	string courseId;
	string courseTitle;
	string coursePrerequisite1;
	string coursePrerequisite2;
};

// Creates vector list
vector<Course> courses;

// Hash function
unsigned int hash(int key) {
	return key % TABLE_SIZE;
}

// Load course file
void loadCourseFile() {
	string column; // column in excel file
	string csvfile; // course file "CS 300 ABCU_Advising_Program_Input.csv"
	csvfile = "CS 300 ABCU_Advising_Program_Input.csv";
	ifstream file; // File reader for file
	file.open(csvfile); // opens file

	// Error if file does not open
	if (!file.is_open()) {
		cerr << "File " << csvfile << " did not open." << endl;
		return;
	}

	else {
		cout << endl;
		cout << "Loading course file." << endl;
		cout << endl;
		while (getline(file, column)) { // While reading rows and columns
			vector<string> datas; // Every row's column data is put in a list
			string data; // individual column data
			stringstream ss(column); // program reads column of file

			while (getline(ss, data, ',')) { // While reading a row's columns
				datas.push_back(data); // Adds every column in that row to make its own vector object
			}

			Course newCourse = Course(); // A new course object is made to hold each row's data (HashTable.cpp gives a good example with node construction)
			newCourse.courseId = datas[0]; // Takes the first piece of data (first column) and makes it the key
			newCourse.courseTitle = datas[1]; // Takes the second piece of data (second column) and makes it the value
			newCourse.coursePrerequisite1 = "";
			newCourse.coursePrerequisite2 = "";

			if (datas.size() > 2 && datas.size() < 5) { // For each course there should only be 2 possible prerequisites 
				for (int i = 2; i < datas.size(); ++i) { // For any prerequisites
					if (i == 2) {
						newCourse.coursePrerequisite1 = datas[2]; // Add the prequisites to that course's value
					}
					else {
						newCourse.coursePrerequisite2 = datas[3];
					}
				}
			}
			courses.push_back(newCourse); // Creates course object in courses list

			// Print course information (row) loaded from file
			cout << "Course ID: " << newCourse.courseId << " | Course Title: " << newCourse.courseTitle << " ";
			if (newCourse.coursePrerequisite1 != "") {
				cout << "| Prerequisites: " << newCourse.coursePrerequisite1;
			}
			if (newCourse.coursePrerequisite2 != "") {
				cout << ", " << newCourse.coursePrerequisite2;
			}
			cout << endl;
			cout << endl;

		}
		file.close(); // Close file 
	}
}

// Hash function ambiguous but found this to sort objects in a list
void sortCourseList() {
	for (int i = 0; i < courses.size() - 1; ++i) { // Takes object i to compare to all other objects
		for (int j = 0; j < courses.size() - i - 1; ++j) { // Takes the one object to the right of the first
			if (courses[j].courseId > courses[j + 1].courseId) { // Compares the two objects values based on letters and numbers coming first 
				swap(courses[j + 1], courses[j]); // Swaps the two objects places if true
			}
		}
	}
}

// Displays course information
void displayCourse(Course course) { 
	cout << "Course ID: " << course.courseId << " | Course Title: " << course.courseTitle << " ";
	if (course.coursePrerequisite1 != "") {
		cout << "| Prerequisites: " << course.coursePrerequisite1;
	}
	if (course.coursePrerequisite2 != "") {
		cout << ", " << course.coursePrerequisite2;
	}
	cout << endl;
	cout << endl;
}

// Displays all courses
void displayCoursesList() {
	if (courses.size() == 0) { // Error check to verify there is comething in the list
		cout << "Load courses." << endl;
		cout << endl;
	}
	else {
		sortCourseList();
		for (int i = 0; i < courses.size(); ++i) {
			displayCourse(courses[i]);
		}
	}
}

// Search for specific course based on user input
void courseSearch() {
	if (courses.size() == 0) { // Error check to verify there is comething in the list
		cerr << "Load file before searching." << endl;
		cout << endl;
		return;
	}
	else {
		string input;
		cout << "Course ID: ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), toupper); // Error found when inputting lowercase letters (https://www.google.com/search?q=c%2B%2B+changing+input+to+uppercase&rlz=1C1CHBF_enUS962US962&oq=C%2B%2B+changing+input+to+upper&gs_lcrp=EgZjaHJvbWUqBwgBECEYoAEyBggAEEUYOTIHCAEQIRigATIHCAIQIRigATIHCAMQIRirAjIHCAQQIRirAtIBCjMwMzczajBqMTWoAgiwAgHxBc1IkXAlTJ5M8QXNSJFwJUyeTA&sourceid=chrome&ie=UTF-8)
		bool found = false;
		int i;
		cout << endl;

		for (i = 0; i < courses.size(); ++i) {
			if (courses[i].courseId == input) {
				found = true;
				break;
			}
		}
		if (found) {
			return displayCourse(courses[i]);
		}
		else {
			cout << "No course IDs matching " << input << " found." << endl;
			cout << endl;
		}
	}
}

int main() {

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display Sorted Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl;
		cout << endl;
        cout << "Enter choice: ";
        cin >> choice;
		cout << endl;

        switch (choice) {

        case 1:
			loadCourseFile();
			break;

        case 2:
			displayCoursesList();
            break;

        case 3:
			courseSearch();
            break;
        }
    }
	cout << endl;
    cout << "Good bye." << endl;
	cout << endl;

    return 0;
}
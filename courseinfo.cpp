#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string code;
    string name;
    vector<string> prerequisites;
};

// Function prototypes
void loadDataStructure(vector<Course> &courses);
void printCourseList(const vector<Course> &courses);
void printCourse(const vector<Course> &courses);
void displayMenu();

int main() {
    vector<Course> courses;

    // Load course data
    loadDataStructure(courses);

    int choice;

    cout << "Welcome to the course planner" << endl;

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                printCourseList(courses);
                break;
            case 2:
                printCourse(courses);
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}

void loadDataStructure(vector<Course> &courses) {
    // Add courses to the vector
    courses.push_back({"MATH201", "Discrete Mathematics", {}});
    courses.push_back({"CSCI300", "Introduction to Algorithms", {"CSCI200"}});
    courses.push_back({"CSCI350", "Operating Systems", {"CSCI300"}});
    courses.push_back({"CSCI101", "Introduction to Programming in C++", {"CSCI100"}});
    courses.push_back({"CSCI100", "Introduction to Computer Science", {}});
    courses.push_back({"CSCI301", "Advanced Programming in C++", {"CSCI101"}});
    courses.push_back({"CSCI400", "Large Software Development", {"CSCI301", "CSCI350"}});
    courses.push_back({"CSCI200", "Data Structures", {"CSCI101"}});
}

void printCourseList(const vector<Course> &courses) {
    cout << "List of Courses:" << endl;
    for (size_t i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i].code << " - " << courses[i].name << endl;
    }
}

void printCourse(const vector<Course> &courses) {
    cout << "Enter the number of the course to print details: ";
    int index;
    cin >> index;
    cin.ignore(); // Clear the newline character from the input buffer

    if (index >= 1 && index <= courses.size()) {
        const Course &course = courses[index - 1];
        cout << "Course Code: " << course.code << endl;
        cout << "Course Name: " << course.name << endl;
        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto &prerequisite : course.prerequisites) {
                // Find the prerequisite course with code number lower than the current course
                auto it = find_if(courses.begin(), courses.end(), [&](const Course &c) {
                    return c.code == prerequisite;
                });
                if (it != courses.end() && distance(courses.begin(), it) < index - 1) {
                    cout << prerequisite << " ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "Invalid course number. Please try again." << endl;
    }
}

void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Print course list" << endl;
    cout << "2. Print course" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

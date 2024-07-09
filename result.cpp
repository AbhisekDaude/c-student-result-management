#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Define a structure for student
struct Student {
    string name;
    int rollNumber;
    float marks;
};

// Function prototypes
void addStudent(vector<Student> &students);
void displayStudents(const vector<Student> &students);
void saveStudentsToFile(const vector<Student> &students, const string &filename);
void loadStudentsFromFile(vector<Student> &students, const string &filename);
void calculateResult(vector<Student> &students);

int main() {
    vector<Student> students;
    string filename = "students.txt"; // File to store student data

    int choice;
    do {
        cout << "\nStudent Result Management System\n";
        cout << "------------------------------\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Calculate Results\n";
        cout << "4. Save Students to File\n";
        cout << "5. Load Students from File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                calculateResult(students);
                break;
            case 4:
                saveStudentsToFile(students, filename);
                break;
            case 5:
                loadStudentsFromFile(students, filename);
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}

void addStudent(vector<Student> &students) {
    Student newStudent;
    cout << "\nEnter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter roll number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter marks: ";
    cin >> newStudent.marks;

    students.push_back(newStudent);
}

void displayStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students to display.\n";
    } else {
        cout << "\nStudent List\n";
        cout << "-----------------------------------------------------\n";
        cout << setw(20) << "Name" << setw(15) << "Roll Number" << setw(10) << "Marks\n";
        cout << "-----------------------------------------------------\n";
        for (const auto &student : students) {
            cout << setw(20) << student.name << setw(15) << student.rollNumber << setw(10) << student.marks << "\n";
        }
        cout << "-----------------------------------------------------\n";
    }
}

void saveStudentsToFile(const vector<Student> &students, const string &filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto &student : students) {
        outFile << student.name << "," << student.rollNumber << "," << student.marks << "\n";
    }

    outFile.close();
    cout << "Student data saved to file: " << filename << "\n";
}

void loadStudentsFromFile(vector<Student> &students, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading.\n";
        return;
    }

    students.clear(); // Clear existing data

    string line;
    while (getline(inFile, line)) {
        Student student;
        size_t pos = line.find(',');
        student.name = line.substr(0, pos);
        line = line.substr(pos + 1);

        pos = line.find(',');
        student.rollNumber = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        student.marks = stof(line);

        students.push_back(student);
    }

    inFile.close();
    cout << "Student data loaded from file: " << filename << "\n";
}

void calculateResult(vector<Student> &students) {
    if (students.empty()) {
        cout << "\nNo students to calculate results.\n";
    } else {
        for (auto &student : students) {
            // Add your result calculation logic here, e.g., grading based on marks
            // For simplicity, let's assume a pass mark of 50
            if (student.marks >= 50) {
                cout << student.name << " has passed.\n";
            } else {
                cout << student.name << " has failed.\n";
            }
        }
    }
}
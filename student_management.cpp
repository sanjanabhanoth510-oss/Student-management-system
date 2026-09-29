// Student Management System
// A console-based C++ program to add, view, search, update and delete student records.

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------------------------------------------------------------
// Input helpers: keep asking until the user enters valid input
// ---------------------------------------------------------------

// Reads one line from the user. Exits cleanly if input ends (Ctrl+D / Ctrl+Z).
string readLine(const string &prompt) {
    string line;
    cout << prompt;
    if (!getline(cin, line)) {
        cout << "\nInput ended. Exiting program.\n";
        exit(0);
    }
    return line;
}

// Reads a non-empty piece of text (used for name and course).
string readText(const string &prompt) {
    while (true) {
        string text = readLine(prompt);
        if (text.find_first_not_of(" \t") != string::npos) {
            return text;
        }
        cout << "Input cannot be empty. Please try again.\n";
    }
}

// Reads a whole number between min and max (inclusive).
int readNumber(const string &prompt, int min, int max) {
    while (true) {
        string input = readLine(prompt);
        bool valid = !input.empty() && input.length() <= 9;
        for (char ch : input) {
            if (ch < '0' || ch > '9') {
                valid = false;
            }
        }
        if (valid) {
            int number = stoi(input);
            if (number >= min && number <= max) {
                return number;
            }
        }
        cout << "Invalid input. Please enter a number between " << min << " and "
             << max << ".\n";
    }
}

// ---------------------------------------------------------------
// Student class: stores the details of one student
// ---------------------------------------------------------------
class Student {
private:
    int id;
    string name;
    int age;
    string course;
    int marks;

public:
    Student(int studentId, string studentName, int studentAge, string studentCourse,
            int studentMarks) {
        id = studentId;
        name = studentName;
        age = studentAge;
        course = studentCourse;
        marks = studentMarks;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }
    int getMarks() const { return marks; }

    void setName(string newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setCourse(string newCourse) { course = newCourse; }
    void setMarks(int newMarks) { marks = newMarks; }

    // Grading system: 90+ = A, 75-89 = B, 60-74 = C, 40-59 = D, below 40 = F
    char getGrade() const {
        if (marks >= 90) return 'A';
        if (marks >= 75) return 'B';
        if (marks >= 60) return 'C';
        if (marks >= 40) return 'D';
        return 'F';
    }

    // A student passes with 40 marks or more.
    string getResult() const {
        if (marks >= 40) {
            return "Pass";
        }
        return "Fail";
    }

    void display() const {
        cout << "Student ID : " << id << "\n";
        cout << "Name       : " << name << "\n";
        cout << "Age        : " << age << "\n";
        cout << "Course     : " << course << "\n";
        cout << "Marks      : " << marks << "\n";
        cout << "Grade      : " << getGrade() << " (" << getResult() << ")\n";
        cout << "----------------------------------------\n";
    }
};

// ---------------------------------------------------------------
// StudentManager class: keeps all students and performs operations
// ---------------------------------------------------------------
class StudentManager {
private:
    vector<Student> students;

    // Returns the position of the student in the vector, or -1 if not found.
    int findStudentIndex(int id) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    void addStudent() {
        int id = readNumber("Enter Student ID: ", 1, 999999);
        if (findStudentIndex(id) != -1) {
            cout << "Error: A student with ID " << id << " already exists.\n";
            return;
        }
        string name = readText("Enter name: ");
        int age = readNumber("Enter age (5-100): ", 5, 100);
        string course = readText("Enter course/branch: ");
        int marks = readNumber("Enter marks (0-100): ", 0, 100);

        students.push_back(Student(id, name, age, course, marks));
        cout << "Student added successfully.\n";
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }
        cout << "----------------------------------------\n";
        for (size_t i = 0; i < students.size(); i++) {
            students[i].display();
        }
        cout << "Total students: " << students.size() << "\n";
    }

    void searchStudent() const {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }
        int id = readNumber("Enter Student ID to search: ", 1, 999999);
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "Error: Student with ID " << id << " not found.\n";
            return;
        }
        cout << "----------------------------------------\n";
        students[index].display();
    }

    void updateStudent() {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }
        int id = readNumber("Enter Student ID to update: ", 1, 999999);
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "Error: Student with ID " << id << " not found.\n";
            return;
        }

        cout << "\nCurrent details:\n";
        cout << "----------------------------------------\n";
        students[index].display();

        cout << "What do you want to update?\n";
        cout << "1. Name\n";
        cout << "2. Age\n";
        cout << "3. Course/Branch\n";
        cout << "4. Marks\n";
        cout << "5. Cancel\n";
        int choice = readNumber("Enter your choice (1-5): ", 1, 5);

        switch (choice) {
            case 1:
                students[index].setName(readText("Enter new name: "));
                break;
            case 2:
                students[index].setAge(readNumber("Enter new age (5-100): ", 5, 100));
                break;
            case 3:
                students[index].setCourse(readText("Enter new course/branch: "));
                break;
            case 4:
                students[index].setMarks(readNumber("Enter new marks (0-100): ", 0, 100));
                break;
            case 5:
                cout << "Update cancelled.\n";
                return;
        }
        cout << "Student updated successfully.\n";
        cout << "----------------------------------------\n";
        students[index].display();
    }

    void deleteStudent() {
        if (students.empty()) {
            cout << "No student records found.\n";
            return;
        }
        int id = readNumber("Enter Student ID to delete: ", 1, 999999);
        int index = findStudentIndex(id);
        if (index == -1) {
            cout << "Error: Student with ID " << id << " not found.\n";
            return;
        }
        students.erase(students.begin() + index);
        cout << "Student with ID " << id << " deleted successfully.\n";
    }
};

// ---------------------------------------------------------------
// Menu
// ---------------------------------------------------------------
void showMenu() {
    cout << "\n========================================\n";
    cout << "        STUDENT MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "----------------------------------------\n";
}

int main() {
    StudentManager manager;
    int choice = 0;

    while (choice != 6) {
        showMenu();
        choice = readNumber("Enter your choice (1-6): ", 1, 6);
        cout << "\n";

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.displayAllStudents(); break;
            case 3: manager.searchStudent(); break;
            case 4: manager.updateStudent(); break;
            case 5: manager.deleteStudent(); break;
            case 6: cout << "Thank you for using the Student Management System.\n"; break;
        }
    }
    return 0;
}

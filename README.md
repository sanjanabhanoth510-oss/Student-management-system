# Student Management System

A simple console-based Student Management System written in C++ using object-oriented programming.

## Objective

To build a menu-driven application that manages student records and demonstrates basic programming concepts.

## Features

- Add a student (ID, name, age, course/branch, marks); duplicate IDs are rejected
- Display all students with their grade and result
- Search a student by Student ID
- Update a student's name, age, course or marks
- Delete a student by Student ID
- Grade calculated from marks:

| Marks  | Grade |
|--------|-------|
| 90-100 | A     |
| 75-89  | B     |
| 60-74  | C     |
| 40-59  | D     |
| 0-39   | F (Fail) |

  A student passes with 40 marks or more.
- Input validation and clear messages for invalid numbers, invalid menu choices, empty lists and IDs that do not exist

## Technologies Used

- C++ (C++17)
- Standard library only (`iostream`, `string`, `vector`, `cstdlib`)

## Programming Concepts Used

- Classes and objects (`Student`, `StudentManager`)
- Encapsulation (private data with public getters/setters)
- Vectors
- Functions
- Loops and conditional statements (`while`, `for`, `if`, `switch`)
- Input validation

## How to Compile

```bash
g++ -std=c++17 student_management.cpp -o student_management
```

## How to Run

```bash
./student_management
```

On Windows:

```bash
student_management.exe
```

## Basic Usage

1. Choose an option from the menu (1-6).
2. Add students first. Student IDs must be unique whole numbers (1-999999).
3. Use Display, Search, Update or Delete with a Student ID.
4. Choose 6 to exit.

## Expected Behavior

- Age must be between 5 and 100, and marks between 0 and 100.
- Invalid input shows an error message and asks again.
- Searching, updating or deleting an ID that does not exist shows a "not found" message.
- Data is stored in memory only, so all records are cleared when the program exits.

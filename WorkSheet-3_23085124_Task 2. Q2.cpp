#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

class Student {
private:
    int rollNumber;
    string name;
    float marks;

public:
    Student(int roll = 0, string n = "", float m = 0.0f) {
        rollNumber = roll;
        name = n;
        setMarks(m);
    }

    void setMarks(float m) {
        if (m < 0 || m > 100) {
            throw out_of_range("Marks must be between 0 and 100");
        }
        marks = m;
    }

    int getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    float getMarks() const { return marks; }

    void display() const {
        cout << "Roll: " << rollNumber << ", Name: " << name
             << ", Marks: " << marks << endl;
    }

    void writeToFile(ofstream& file) const {
        file << rollNumber << " " << name << " " << marks << "\n";
    }

    bool readFromFile(ifstream& file) {
        if (file >> rollNumber >> name >> marks) {
            return true;
        }
        return false;
    }
};

class StudentManager {
private:
    string filename;

public:
    StudentManager(string fn = "students.txt") : filename(fn) {}

    void addStudent() {
        int roll;
        string name;
        float marks;

        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks (0-100): ";
        cin >> marks;
        cin.ignore();

        if (marks < 0 || marks > 100) {
            throw out_of_range("Marks must be between 0 and 100");
        }

        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file for writing");
        }

        Student s(roll, name, marks);
        s.writeToFile(file);
        file.close();
        cout << "Student added successfully.\n";
    }

    void displayAllStudents() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "No student records found.\n";
            return;
        }

        cout << "\nStudent Records:\n";
        Student s;
        while (s.readFromFile(file)) {
            s.display();
        }
        file.close();
    }

    void modifyStudent() {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            throw runtime_error("Cannot open file for reading");
        }

        string tempFilename = "temp_" + filename;
        ofstream outFile(tempFilename);
        if (!outFile.is_open()) {
            inFile.close();
            throw runtime_error("Cannot create temporary file");
        }

        int targetRoll;
        cout << "Enter Roll Number to modify: ";
        cin >> targetRoll;
        cin.ignore();

        bool found = false;
        Student s;
        while (s.readFromFile(inFile)) {
            if (s.getRollNumber() == targetRoll) {
                found = true;
                string newName;
                float newMarks;

                cout << "Current Record: ";
                s.display();

                cout << "Enter new Name (or press enter to keep current): ";
                getline(cin, newName);
                if (newName.empty()) {
                    newName = s.getName();
                }

                cout << "Enter new Marks (0-100): ";
                string marksInput;
                getline(cin, marksInput);
                if (marksInput.empty()) {
                    newMarks = s.getMarks();
                } else {
                    newMarks = stof(marksInput);
                    if (newMarks < 0 || newMarks > 100) {
                        throw out_of_range("Marks must be between 0 and 100");
                    }
                }

                Student modified(s.getRollNumber(), newName, newMarks);
                modified.writeToFile(outFile);
                cout << "Record updated successfully.\n";
            } else {
                s.writeToFile(outFile);
            }
        }

        inFile.close();
        outFile.close();

        if (!found) {
            remove(tempFilename.c_str());
            cout << "Student with roll number " << targetRoll << " not found.\n";
        } else {
            remove(filename.c_str());
            rename(tempFilename.c_str(), filename.c_str());
        }
    }
};

void displayMenu() {
    cout << "\nStudent Management System\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Modify Student Record\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    StudentManager manager;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
                case 1:
                    manager.addStudent();
                    break;
                case 2:
                    manager.displayAllStudents();
                    break;
                case 3:
                    manager.modifyStudent();
                    break;
                case 4:
                    cout << "Exiting program.\n";
                    return 0;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Vehicle {
protected:
    string registrationNumber;
    string color;
    const string filename = "vehicles.txt";

public:
    Vehicle(string reg = "", string col = "") : registrationNumber(reg), color(col) {}
    virtual ~Vehicle() {}


    virtual void writeToFile() {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Type: Vehicle\n";
            file << "Registration: " << registrationNumber << "\n";
            file << "Color: " << color << "\n";
            file << "----------------\n";
            file.close();
        }
        else {
            cerr << "Error opening " << filename << " for writing!" << endl;
        }
    }


    string getRegNumber() const { return registrationNumber; }
    string getColor() const { return color; }
    string getFilename() const { return filename; }
};

class Car : public Vehicle {
private:
    int numberOfSeats;

public:
    Car(string reg, string col, int seats) : Vehicle(reg, col), numberOfSeats(seats) {}

    void writeToFile() override {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Type: Car\n";
            file << "Registration: " << getRegNumber() << "\n";
            file << "Color: " << getColor() << "\n";
            file << "Seats: " << numberOfSeats << "\n";
            file << "----------------\n";
            file.close();
        }
        else {
            cerr << "Error opening " << filename << " for writing!" << endl;
        }
    }

    int getSeats() const { return numberOfSeats; }
};

class Bike : public Vehicle {
private:
    int engineCapacity;

public:
    Bike(string reg, string col, int capacity) : Vehicle(reg, col), engineCapacity(capacity) {}

    void writeToFile() override {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Type: Bike\n";
            file << "Registration: " << getRegNumber() << "\n";
            file << "Color: " << getColor() << "\n";
            file << "Engine Capacity: " << engineCapacity << "cc\n";
            file << "----------------\n";
            file.close();
        }
        else {
            cerr << "Error opening " << filename << " for writing!" << endl;
        }
    }

    int getEngineCapacity() const { return engineCapacity; }
};

void displayMenu() {
    cout << "\nVehicle Management System\n";
    cout << "1. Add Vehicle\n";
    cout << "2. Add Car\n";
    cout << "3. Add Bike\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void clearFile(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (file.is_open()) {
        file.close();
        cout << "Previous data cleared.\n";
    }
}

int main() {
    int choice;
    string reg, color;
    int seats, engineCapacity;
    const string filename = "vehicles.txt";


    clearFile(filename);

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 4) {
            cout << "Exiting program.\n";
            break;
        }

        cout << "Enter Registration Number: ";
        getline(cin, reg);
        cout << "Enter Color: ";
        getline(cin, color);

        try {
            if (choice == 1) {
                Vehicle v(reg, color);
                v.writeToFile();
            }
            else if (choice == 2) {
                cout << "Enter Number of Seats: ";
                cin >> seats;
                cin.ignore();
                Car c(reg, color, seats);
                c.writeToFile();
            }
            else if (choice == 3) {
                cout << "Enter Engine Capacity (cc): ";
                cin >> engineCapacity;
                cin.ignore();
                Bike b(reg, color, engineCapacity);
                b.writeToFile();
            }
            else {
                cout << "Invalid choice! Please try again.\n";
                continue;
            }
            cout << "Details saved successfully to " << filename << ".\n";
        }
        catch (...) {
            cerr << "An error occurred while saving details.\n";
        }
    }

    return 0;
}

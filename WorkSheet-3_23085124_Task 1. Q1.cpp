#include <iostream>
#include <stdexcept>

using namespace std;

class Time {
private:
    int hours;
    int minutes;

    void validate() {
        if (hours < 0 || minutes < 0 || minutes >= 60 || hours >= 24) {
            throw runtime_error("Invalid time: Hours must be 0-23 and minutes must be 0-59.");
        }
    }

public:

    Time(int h = 0, int m = 0) : hours(h), minutes(m) {
        validate();
    }

    Time(int h, int m, bool) : hours(h), minutes(m) {}

    void input() {
        cin >> hours >> minutes;
        validate();
    }

    Time operator+(const Time& t) const {
        int totalMinutes = minutes + t.minutes;
        int carryHours = totalMinutes / 60;
        int finalMinutes = totalMinutes % 60;
        int finalHours = hours + t.hours + carryHours;
        return Time(finalHours, finalMinutes, false);
    }

    bool operator>(const Time& t) const {
        if (hours > t.hours) return true;
        if (hours == t.hours && minutes > t.minutes) return true;
        return false;
    }

    void display() const {
        cout << hours << "h " << minutes << "m" << endl;
    }
};

int main() {
    try {
        Time t1, t2;

        cout << "Enter time 1 (hours and minutes): ";
        t1.input();

        cout << "Enter time 2 (hours and minutes): ";
        t2.input();

        Time t3 = t1 + t2;
        cout << "Sum: ";
        t3.display();

        if (t1 > t2) {
            cout << "Time 1 is later than Time 2" << endl;
        } else {
            cout << "Time 2 is later than or equal to Time 1" << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

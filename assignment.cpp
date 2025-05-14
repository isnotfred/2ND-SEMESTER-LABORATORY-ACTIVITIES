#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

// Checks if the input string can be safely converted to type T
template<typename T>
bool isValidInput(const string &str, T &result) {
    stringstream ss(str);
    ss >> result;
    return ss.eof() && !ss.fail();
}

// Prompts the user for valid input of type T with error checking
template<typename T>
T getValidInput(const string &prompt) {
    string input;
    T value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isValidInput(input, value)) {
            return value;
        } else {
            cout << "Invalid input. Please enter a valid value." << endl;
        }
    }
}

// Gets a list of temperature readings from user input
void getTempReadings(vector<double>& temperatures, int numReadings) {
    for (int i = 0; i < numReadings; i++) {
        temperatures.push_back(getValidInput<double>("Enter temperature " + to_string(i + 1) + ": "));
    }
}

// Calculates and returns the average of the temperatures
double getAverage(const vector<double>& temperatures) {
    double sum = 0;
    for (size_t i = 0; i < temperatures.size(); i++) {
        sum += temperatures[i];
    }
    return sum / temperatures.size();
}

// Sorts the temperatures in ascending order using bubble sort
void arrangeAscending(vector<double>& temperatures) {
    double temp;
    for (size_t i = 0; i < temperatures.size() - 1; i++) {
        for (size_t j = 0; j < temperatures.size() - 1; j++) {
            if (temperatures[j] > temperatures[j + 1]) {
                temp = temperatures[j];
                temperatures[j] = temperatures[j + 1];
                temperatures[j + 1] = temp;
            }
        }
    }
}

// Counts how many temperatures are greater than a given value
int countTempGreaterThan(const vector<double>& temperatures, double value) {
    int count = 0;
    for (size_t i = 0; i < temperatures.size(); i++) {
        if (temperatures[i] > value)
            count++;
    }
    return count;
}

// Displays the average, highest, lowest, count above 40, and sorted temperatures
void displayOutput(vector<double>& temperatures) {
    arrangeAscending(temperatures);
    cout << "Average: " << fixed << setprecision(2) << getAverage(temperatures) << " deg C" << endl;
    cout << "Highest: " << temperatures.back() << " deg C" << endl;
    cout << "Lowest: " << temperatures.front() << " deg C" << endl;
    cout << "Temperatures > 40 deg C: " << countTempGreaterThan(temperatures, 40) << endl;
    cout << "Sorted temperatures: ";
    for (size_t i = 0; i < temperatures.size(); i++) {
        cout << temperatures[i] << '\t';
    }
    cout << endl;
}

// Main program loop: collects and processes daily temperature readings
int main() {
    char shouldContinue = 'Y';
    int days = 0;
    vector<double> tempInCelsius;

    while (shouldContinue == 'Y') {
        tempInCelsius.clear();
        int numReadings;
        days++;

        cout << "Day " << days << endl;
        do {
            numReadings = getValidInput<int>("Enter the number of temperature readings: ");
            if (numReadings < 1) cout << "Invalid number! Enter a positive number." << endl;
        } while (numReadings < 1);

        getTempReadings(tempInCelsius, numReadings);
        cout << endl;
        displayOutput(tempInCelsius);

        cout << endl;
        do {
            cout << "Encode for another day? (Y/N): ";
            cin >> shouldContinue;
            shouldContinue = toupper(shouldContinue);

            if (shouldContinue != 'Y' && shouldContinue != 'N') {
                cout << "Invalid input! Please enter 'Y' for Yes or 'N' for No." << endl;
            }
        } while (shouldContinue != 'Y' && shouldContinue != 'N');

        cin.ignore(); // Clear newline character for the next getline
        cout << endl;
    }
    cout << "Thank you!" << endl;
    return 0;
}

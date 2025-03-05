#include <iostream>
#include <iomanip>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;                       // Check if n is 1 or 0
    if (n <= 3) return true;                        // Check if n is 2 or 3
    if (n % 2 == 0 || n % 3 == 0) return false;     // Check if n is divisible by 2 or 3

    for (int i = 5; i * i <= n; i += 6) {           // Check if n is divisible from 5 to square root of n (iterate i by i+6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int main() {
    cout << "WELCOME!" << endl;

    int row;
    int col;
    
    while (true) {
        // Take user input for the number of rows
        while (true) {
            cout << "\nEnter the row size of the array: ";
            cin >> row;
            if (cin.fail() || row <= 0) { // Validate if input is a number and not negative or 0
                cout << "Invalid input!";
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            break;
        }

        // Take user input for the number of columns
        while (true) {
            cout << "Enter the column size of the array: ";
            cin >> col;
            if (cin.fail() || col <= 0) { // Validate if input is a number and not negative or 0
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            break;
        }

        // Check if row and col is equal
        if (row == col) {
            break;
        } else {
            cout << "\nOops! The size of the row and column must be equal!" << endl;
        }
    }

    int matrix[row][col];

    // Prompt user to enter a value for each element in the matrix
    for (int i = 0; i < row; i++) {
        cout << "\nData entry for row " << i + 1 << endl;
        for (int j = 0; j < col; j++) {
            while (true) {
                cout << "Enter a number for [" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
                if (cin.fail()) { // Validate if input is a number
                    cout << "Invalid input!";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                break;
            }
        }
    }

    // Display matrix contents
    cout << "\nMatrix Contents" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
           cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }

    // Calculate and display the sum of the diagonal elements
    int sumDiagonal = 0;
    for (int i = 0; i < row; i++) {
        sumDiagonal += matrix[i][i];
    }
    cout << "\nThe sum of diagonal is: " << sumDiagonal << endl;

    // Calculate and display the sum of the anti-diagonal elements
    int sumAntiDiagonal = 0;
    for (int i = 0; i < row; i++) {
        sumAntiDiagonal += matrix[i][row - 1 - i];
    }
    cout << "The sum of anti-diagonal is: " << sumAntiDiagonal << endl;  
    
    // Calculate and display the average of the prime numbers
    int countPrime = 0, sumPrime = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (isPrime(matrix[i][j])) {
                sumPrime += matrix[i][j];
                countPrime++;
            }
        }
    }
    double avgPrime = double(sumPrime) / countPrime;
    cout << "The average of prime numbers is: " << fixed << setprecision(2) << avgPrime << endl;  

    // Create a transposed matrix of the original matrix
    int transposed[row][col];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    // Display transposed matrix contents
    cout << "\nTransposed Matrix" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
           cout << transposed[i][j] << '\t';
        }
        cout << endl;
    }   

    return 0;
}

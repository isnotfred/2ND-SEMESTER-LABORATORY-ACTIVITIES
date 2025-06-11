#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a product
struct Product {
    string id, name;
    double price;
    int quantity;
    vector<double> priceHistory;
    vector<int> stockHistory;

    // Update the product's price and log the change
    void updatePrice(double value) {
        price = value;
        priceHistory.push_back(price);
        cout << "\nPrice changed.\n";
        cout << "Name: " << name << " | New price: " << price << endl; 
    }

    // Add to stock and log the new quantity
    void stockIn(int value) {
        quantity += value;
        stockHistory.push_back(quantity);
        cout << "\nStock Increased.\n";
        cout << "Name: " << name << " | New stock: " << quantity << endl; 
    }

    // Remove from stock and log the new quantity
    void stockOut(int value) {
        if (value > quantity) {
            cout << "Error: Cannot stock out more than current stock (" << quantity << ").\n";
            return;
        }
        quantity -= value;
        stockHistory.push_back(quantity);
        cout << "\nStock Decreased.\n";
        cout << "Name: " << name << " | New stock: " << quantity << endl;
    }

    // Display product details and history
    void displayDetails() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Current Selling Price: P" << setprecision(2) << price << endl;
        cout << "Current Stock: " << quantity << " items" << endl;

        // Show price history
        cout << "Price History: ";
        for (size_t i = 0; i < priceHistory.size(); i++) {
            cout << "P" << priceHistory[i];
            if (i != priceHistory.size()-1) cout << " | ";
        }

        // Show stock history
        cout << "\nStock History: ";
        for (size_t i = 0; i < stockHistory.size(); i++) {
            cout << stockHistory[i] << " items";
            if (i != stockHistory.size()-1) cout << " | ";
        }
        cout << endl;
    }
};

// Check if string input is a valid number and convert to type T
template<typename T>
bool isValidNum(const string &str, T &result) {
    stringstream ss(str);
    ss >> result;
    return ss.eof() && !ss.fail();
}

// Prompt user for valid input with error checking
template<typename T>
T getValidNum(const string &prompt) {
    string input;
    T value;

    while (true) {
        cout << prompt;
        getline(cin, input);
        if (isValidNum(input, value)) {
            return value;
        } else {
            cout << "Invalid input. Please enter a valid value." << endl;
        }
    }
}

// Increment a 3-digit string ID (e.g., "001" -> "002")
string increaseID(string& idCount) {
    string strNum = idCount;
    int num = stoi(strNum); // convert to int
    num++; // increment

    // Convert back to string with leading zeros
    stringstream ss;
    ss << setw(3) << setfill('0') << num;
    return ss.str();
}

// Create a new product with user input
Product newProduct(string idCount) {
    Product item;
    string productName;
    double productPrice;
    int productQuantity;

    item.id = idCount;
    cout << "New Product - ID: " << idCount << endl;

    // Get name
    cout << "Enter Name: ";
    getline(cin, productName);
    item.name = productName;

    // Get valid price
    while (true) {
        productPrice = getValidNum<double>("Enter Price: ");
        if (productPrice <= 0) {
            cout << "Invalid price! Enter a positive value.\n"; 
            continue;
        }
        break;
    }
    item.price = productPrice;
    item.priceHistory.push_back(productPrice);

    // Get valid quantity
    while (true) {
        productQuantity = getValidNum<int>("Enter Quantity: ");
        if (productQuantity <= 0) {
            cout << "Invalid quantity! Enter a positive value.\n"; 
            continue;
        }
        break;
    }
    item.quantity = productQuantity;
    item.stockHistory.push_back(productQuantity);

    // Show summary
    cout << "\nSummary | ID: " << setfill('0') << setw(3) << item.id << " | Name: " << item.name << " | Price: P" << fixed << setprecision(2) << item.price << " | Quantity: " << item.quantity << endl << endl;

    return item;
}

// Search for a product by ID and return a reference to it
Product& searchProduct(vector<Product>& products) {
    string idToFind;
    bool found = false;

    while (!found) {
        // Ask user to enter valid ID
        while (true) {
            cout << "Enter ID of Product: ";
            getline(cin, idToFind);
            bool valid = false;
            for (char c : idToFind) {
                if (!isdigit(c)) {
                    cout << "Invalid Input! ID should only include digits.\n";
                    valid = false;
                    break;
                }
                valid = true;
            }

            if (!valid) continue;
            
            if (idToFind.length() != 3) {
                cout << "Invalid ID! Enter from 001-999.\n";
                continue;
            }
            break;
        }

        // Search in the product list
        for (Product& product : products) {
            if (idToFind == product.id) {
                cout << "Product Name: " << product.name << " | ID: " << product.id << endl;
                found = true;
                return product; // Return reference if found
            }
        }

        if (!found) {
            cout << "Product ID not found!\n";
        }
    }

    // Should never be reached
    static Product dummy;
    return dummy;
}

// Get new price from user
double getNewPrice() {
    double newPrice;
    while (true) {
        newPrice = getValidNum<double>("Enter new price: ");
        if (newPrice <= 0) {
            cout << "Invalid price! Enter a positive value.\n"; 
            continue;
        }
        break;
    }
    return newPrice;
}

// Get stock-in quantity
int getStockIncrease() {
    int stockIncrease;
    while (true) {
        stockIncrease = getValidNum<int>("Enter quantity: ");
        if (stockIncrease <= 0) {
            cout << "Invalid quantity! Enter a positive value.\n"; 
            continue;
        }
        break;
    }
    return stockIncrease;
}

// Get stock-out quantity
int getStockDecrease() {
    int stockDecrease;
    while (true) {
        stockDecrease = getValidNum<int>("Enter quantity: ");
        if (stockDecrease <= 0) {
            cout << "Invalid quantity! Enter a positive value.\n"; 
            continue;
        }
        break;
    }
    return stockDecrease;
}

// Main program
int main() {
    bool running = true;
    int choice, count;
    string idCount = "000"; // Start from ID 001
    vector<Product> products; // List of products

    while (running) {
        // Display menu
        cout << "==========| Welcome! |==========\n";
        cout << "1 - Add new product\n";
        cout << "2 - Update product price\n";
        cout << "3 - Product stock in\n";
        cout << "4 - Product stock out\n";
        cout << "5 - Display all products\n";
        cout << "6 - Exit\n";
        cout << "================================\n";

        // Get valid menu choice
        while (true) {
            choice = getValidNum<int>("Choice: ");
            if (choice < 1 || choice > 6) {
                cout << "Invalid choice! Choose from 1-6.\n";
                continue;
            }
            break;
        }

        // Perform selected action
        switch (choice) {
        case 1:
            cout << "=========| NEW PRODUCT |==========\n";
            idCount = increaseID(idCount);
            if (stoi(idCount) > 999) {
                cout << "Products have exceeded the id limit!\n";
                break;
            }
            products.push_back(newProduct(idCount));
            break;
        case 2:
            cout << "=========| NEW PRICE |==========\n";
            searchProduct(products).updatePrice(getNewPrice());
            cout << endl;
            break;
        case 3:
            cout << "==========| STOCK IN |==========\n";
            searchProduct(products).stockIn(getStockIncrease());
            cout << endl;        
            break;
        case 4:
            cout << "=========| STOCK OUT |==========\n";
            searchProduct(products).stockOut(getStockDecrease()); 
            cout << endl;            
            break;
        case 5:
            cout << "==========| PRODUCTS |==========\n";
            count = 1;
            for (Product product : products) {
                cout << "Product " << count << endl;
                product.displayDetails();
                count++;
                cout << endl;
            }
            break;
        case 6:
            cout << "Thank You!\n";
            running = false; // Exit loop
            break;
        }
    }

    return 0;
}
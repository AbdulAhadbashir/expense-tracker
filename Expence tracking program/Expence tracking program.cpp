#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;
struct Expense {
    string date;
    string category;
    double amount;
    string notes;
};
vector<Expense> expenses;
void addExpense() {
    Expense expense;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> expense.date;
    cout << "Enter category: ";
    cin >> expense.category;
    cout << "Enter amount: ";
    cin >> expense.amount;
    cout << "Enter notes: ";
    cin.ignore();
    getline(cin, expense.notes);
    expenses.push_back(expense);
    cout << "Expense added successfully!\n";
}
void displayExpenses() {
    cout << left << setw(15) << "Date" << setw(15) << "Category"
        << setw(10) << "Amount" << "Notes\n";
    for (const auto& expense : expenses) {
        cout << left << setw(15) << expense.date << setw(15) << expense.category
            << setw(10) << expense.amount << expense.notes << '\n';
    }
}
void calculateTotal() {
    string startDate, endDate;
    cout << "Enter start date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> endDate;

    double total = 0.0;
    for (const auto& expense : expenses) {
        if (expense.date >= startDate && expense.date <= endDate) {
            total += expense.amount;
        }
    }

    cout << "Total expenses from " << startDate << " to " << endDate << ": $"
        << total << '\n';
}
void displayByCategory() {
    map<string, double> categoryTotals;
    for (const auto& expense : expenses) {
        categoryTotals[expense.category] += expense.amount;
    }

    cout << left << setw(15) << "Category" << "Total Amount\n";
    for (const auto& pair : categoryTotals) {
        cout << left << setw(15) << pair.first << pair.second << '\n';
    }
}
void saveToFile() {
    ofstream file("expenses.csv");
    if (file.is_open()) {
        file << "Date,Category,Amount,Notes\n";
        for (const auto& expense : expenses) {
            file << expense.date << "," << expense.category << ","
                << expense.amount << "," << expense.notes << '\n';
        }
        file.close();
        cout << "Expenses saved to file successfully!\n";
    }
    else {
        cout << "Failed to open file for saving.\n";
    }
}
void loadFromFile() {
    ifstream file("expenses.csv");
    if (file.is_open()) {
        string line, word;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream s(line);
            Expense expense;

            getline(s, expense.date, ',');
            getline(s, expense.category, ',');
            getline(s, word, ',');
            expense.amount = stod(word);
            getline(s, expense.notes, ',');

            expenses.push_back(expense);
        }
        file.close();
        cout << "Expenses loaded from file successfully!\n";
    }
    else {
        cout << "No saved file found.\n";
    }
}

void displayMenu() {
    cout << "\nExpense Tracker Menu:\n";
    cout << "1. Add Expense\n";
    cout << "2. Display All Expenses\n";
    cout << "3. Calculate Total Expenses\n";
    cout << "4. Display Expenses by Category\n";
    cout << "5. Save Expenses to File\n";
    cout << "6. Load Expenses from File\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}
int main() {
    loadFromFile(); 
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addExpense();
            break;
        case 2:
            displayExpenses();
            break;
        case 3:
            calculateTotal();
            break;
        case 4:
            displayByCategory();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
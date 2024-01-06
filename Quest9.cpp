//21_ENG_151 W.D.S.R.RUDRIGO
//21/ENG/003 A.M.D.T Adikari
//21/ENG/149 U.H.K.S.Herath 

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <conio.h>
#include <algorithm>
using namespace std;

void loadAccountsFromFile(vector<string>& accounts, const string& type);

class User {
public:
    string username;
    string password;

    void getUserInfo() {
        cout << "\nEnter username: ";
        cin >> username;

        cout << "Enter password: ";
        //cin >> password;
        char ch;
        while ((ch = _getch()) != '\r') {
            password.push_back(ch);
            cout << '*'; // Print '*' instead of the actual character
        }
        cout << endl;


    }
};

class Administrator : public User {
public:
    Administrator() {
        username = "admin";
        password = "Password@1234";
    }


    void addAdmin(vector<User>& admins) {
        User admin;
        cout << "\nLog in as Admin" << endl;
        admin.getUserInfo();
        if (admin.password == "Password@1234") {
            admins.push_back(admin);
            cout << "Admin added successfully.\n";
        }
        else {
            cout << "Incorrect password.\n";
            exit(EXIT_FAILURE);
        }
    }


    void increaseDate() {

        cout << "\nDate increased by 1 day.\n";
    }

    void addEmployee(vector<User>& employees) {
        User employee;
        cout << "\nAdd Employees" << endl;
        employee.getUserInfo();
        employees.push_back(employee);
        cout << "Employee added successfully.\n";
    }

    void setInterestAndOverdraft(vector<User>& employees) {
        // Implement logic to set annual saving interest and overdraft charge
        cout << "\nAnnual Saving Interest and Overdraft Charge set.\n";
    }
};

class Employee : public User {
public:
    void employeeLogin() {
        cout << "\nEmployee Login" << endl;
        getUserInfo();
    }
    void addCustomer(vector<User>& customers) {
        User customer;
        cout << "\nLog in as Employee to Add Customer" << endl;
        customer.getUserInfo();
        customers.push_back(customer);
        cout << "Customer added successfully.\n";
        saveCustomerToFile(customer);
    }

    void createAccount(vector<string>& accounts, const string& type) {
        string accountNumber = type + to_string(accounts.size() + 1);
        accounts.push_back(accountNumber);
        cout << "Account created successfully. Account Number: " << accountNumber << "\n";
        saveAccountsToFile(accounts, type);
    }

    void closeAccount(vector<string>& accounts) {
        if (!accounts.empty()) {
            cout << "Enter the account number to close: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(accounts.begin(), accounts.end(), accountNumber);
            if (it != accounts.end()) {
                accounts.erase(it);
                cout << "Account closed successfully.\n";
                saveAccountsToFile(accounts, "all");
            }
            else {
                cout << "Account not found.\n";
            }
        }
        else {
            cout << "No accounts to close.\n";
        }
    }

    void depositMoney(vector<string>& accounts) {
        if (!accounts.empty()) {
            cout << "\Enter the account number to deposit money: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(accounts.begin(), accounts.end(), accountNumber);
            if (it != accounts.end()) {
                // Implement deposit logic
                cout << "Money deposited successfully.\n";
            }
            else {
                cout << "Account not found.\n";
            }
        }
        else {
            cout << "No accounts to deposit money.\n";
        }
    }

    void withdrawMoney(vector<string>& accounts) {
        if (!accounts.empty()) {
            cout << "\nEnter the account number to withdraw money: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(accounts.begin(), accounts.end(), accountNumber);
            if (it != accounts.end()) {
                // Implement withdrawal logic
                cout << "Money withdrawn successfully.\n";
            }
            else {
                cout << "Account not found.\n";
            }
        }
        else {
            cout << "No accounts to withdraw money.\n";
        }
    }

    void setOverdraftLimit(vector<string>& currentAccounts) {
        if (!currentAccounts.empty()) {
            cout << "\nEnter the current account number to set overdraft limit: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(currentAccounts.begin(), currentAccounts.end(), accountNumber);
            if (it != currentAccounts.end()) {
                // Implement overdraft limit setting logic
                cout << "Overdraft limit set successfully.\n";
            }
            else {
                cout << "Current account not found.\n";
            }
        }
        else {
            cout << "No current accounts to set overdraft limit.\n";
        }
    }

    void viewTransactions(vector<string>& accounts) {
        if (!accounts.empty()) {
            cout << "\nEnter the account number to view transactions: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(accounts.begin(), accounts.end(), accountNumber);
            if (it != accounts.end()) {
                // Implement transaction view logic
                cout << "Viewing transactions for account " << accountNumber << "...\n";
            }
            else {
                cout << "Account not found.\n";
            }
        }
        else {
            cout << "No accounts to view transactions.\n";
        }
    }

private:
    void saveAccountsToFile(const vector<string>& accounts, const string& type) {
        ofstream outFile(type + "_accounts.txt");
        if (outFile.is_open()) {
            for (const auto& account : accounts) {
                outFile << account << "\n";
            }
            outFile.close();
        }
        else {
            cerr << "Error opening file for writing.\n";
        }
    }

    void saveCustomerToFile(const User& customer) {
        ofstream outFile("customer_accounts.txt", ios::app); // Append mode
        if (outFile.is_open()) {
            outFile << customer.username << " " << customer.password << "\n";
            outFile.close();
        }
        else {
            cerr << "Error opening file for writing.\n";
        }
    }
};

class Customer : public User {
public:
    string accountType;
    void customerLogin() {
        cout << "\nCustomer Login" << endl;
        getUserInfo();
    }

    Customer(const string& type) : accountType(type) {}

    void viewTransactions(vector<string>& accounts) {
        if (!accounts.empty()) {
            cout << "\nEnter the account number to view transactions: ";
            string accountNumber;
            cin >> accountNumber;

            auto it = find(accounts.begin(), accounts.end(), accountNumber);
            if (it != accounts.end()) {

                cout << "Viewing transactions for account " << accountNumber << "...\n";
            }
            else {
                cout << "Account not found.\n";
            }
        }
        else {
            cout << "No accounts to view transactions.\n";
        }
    }

};

int main() {
    Administrator admin;
    vector<User> employees;
    vector<User> admins;
    vector<User> customers;
    vector<string> savingAccounts;
    vector<string> currentAccounts;

    // Load existing accounts from files
    loadAccountsFromFile(savingAccounts, "saving");
    loadAccountsFromFile(currentAccounts, "current");

    int usertype;
    cout << "1 : Login as Admin" << endl;
    cout << "2 : Login as Employee" << endl;
    cout << "3 : Login as Customer" << endl;

    cout << "\nEnter a number : ";
    cin >> usertype;

    if (usertype == 1) {
        admin.addAdmin(admins);
        admin.increaseDate();
        admin.addEmployee(employees);
        admin.setInterestAndOverdraft(employees);
    }

    if (usertype == 2) {
        Employee employee;
        employee.employeeLogin();

        cout << "\n\n1 : Add Customer" << endl;
        cout << "2 : Depostit Money" << endl;
        cout << "3 : Withdraw Money" << endl;
        cout << "4 : Set Overdraft Limit" << endl;
        cout << "5 : View Transtractions" << endl;
        cout << "6 : Close Account" << endl;

        cout << "\nEnter a Number : ";
        int employeework;
        cin >> employeework;

        if (employeework == 1) {
            employee.addCustomer(customers);
            employee.createAccount(savingAccounts, "saving");
            employee.createAccount(currentAccounts, "current");
        }
        if (employeework == 2) {
            employee.depositMoney(savingAccounts);
        }
        if (employeework == 3) {
            employee.withdrawMoney(savingAccounts);
        }
        if (employeework == 4) {
            employee.setOverdraftLimit(currentAccounts);
        }
        if (employeework == 5) {
            employee.viewTransactions(savingAccounts);
        }
        if (employeework == 65) {
            employee.closeAccount(savingAccounts);
        }
        else {
            cout << "Invalid number!" << endl;
            return 0;
        }


    }

    if (usertype == 3) {
        Customer customer("saving");
        customer.customerLogin();
        customer.viewTransactions(savingAccounts);

    }


    return 0;
}

void loadAccountsFromFile(vector<string>& accounts, const string& type) {
    ifstream inFile(type + "_accounts.txt");
    if (inFile.is_open()) {
        string accountNumber;
        while (inFile >> accountNumber) {
            accounts.push_back(accountNumber);
        }
        inFile.close();
    }
}

void saveCustomerToFile(const User& customer) {
    ofstream outFile("customer_accounts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << customer.username << " " << customer.password << "\n";
        outFile.close();
    }
    else {
        cerr << "Error opening file for writing.\n";
    }
}

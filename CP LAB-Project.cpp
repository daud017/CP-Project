#include<iostream>
#include<fstream>
#include<conio.h>
#include<cctype> // for isdigit
#include<stdlib.h> // for system()

using namespace std;

const int number_of_acc = 10; // This is for 10 accounts maximum can be made
string Name[number_of_acc];   // Account user name
int ACCnumber[number_of_acc]; // Account user accout number
float Amount[number_of_acc];  // Amount of balance in Accout
int total = 0;

// Save all accounts to file
void saveToFile() {
    ofstream file("bankdata.txt");
    for (int i = 0; i < total; i++) {
        file << Name[i] << " " << ACCnumber[i] << " " << Amount[i] << endl;
    }
    file.close();
}

// Load accounts from file at start
void loadFromFile() {
    ifstream file("bankdata.txt");
    while (file >> Name[total] >> ACCnumber[total] >> Amount[total]) {
        total++;
    }
    file.close();
}

// Create Account
void CreateAccount() {
    if (total >= number_of_acc) {
        cout << "Maximum Accounts are made\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> Name[total];

    for (char ch : Name[total]) {
        if (isdigit(ch)) {
            cout << "Invalid name. Name cannot contain numbers." << endl;
            return;
        }
    }

    int tempAcc;
    cout << "Enter Account Number: ";
    cin >> tempAcc;

    if (!cin) {
        cout << "Invalid input. Please Enter Digits only.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    for (int i = 0; i < total; i++) {
        if (ACCnumber[i] == tempAcc) {
            cout << "Account number already exists.\n";
            return;
        }
    }

    ACCnumber[total] = tempAcc;

    cout << "Enter starting balance: ";
    cin >> Amount[total];

    if (!cin) {
        cout << "Invalid balance input.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    total++;
    saveToFile(); // Save after creating account
    cout << "Account is created successfully" << endl;
}

int findAccount(int accNum) {
    for (int i = 0; i < total; i++) {
        if (ACCnumber[i] == accNum)
            return i;
    }
    return -1;
}

// Deposit Money
void Deposit() {
    float deposit_money = 0;
    int ACCnum;

    cout << "Enter the Account Number: ";
    cin >> ACCnum;

    int index = findAccount(ACCnum);
    if (index == -1) {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter the Amount of Money you wanna Deposit: ";
    cin >> deposit_money;

    if (deposit_money < 0) {
        cout << "Invalid amount.\n";
        return;
    }

    Amount[index] += deposit_money;
    saveToFile(); // Save after deposit
    cout << "New amount is now at: " << Amount[index] << endl;
}

// Withdraw Money
void withdraw() {
    int ACCnum;
    float withdraw_money;

    cout << "Enter Account number: ";
    cin >> ACCnum;

    int index = findAccount(ACCnum);
    if (index == -1) {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter amount to withdraw: ";
    cin >> withdraw_money;

    if (withdraw_money > Amount[index]) {
        cout << "Not enough balance." << endl;
        return;
    }

    Amount[index] -= withdraw_money;
    saveToFile(); // Save after withdraw
    cout << "Withdraw done. New balance: " << Amount[index] << endl;
}

// Display Account Info
void display() {
    int ACCnum;
    cout << "Enter Account Number: ";
    cin >> ACCnum;

    int index = findAccount(ACCnum);
    if (index == -1) {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Name: " << Name[index] << endl;
    cout << "Account Number: " << ACCnumber[index] << endl;
    cout << "Balance: " << Amount[index] << endl;
}

int main() {
    loadFromFile(); // Load data at start

    int choice;
    do {
        cout << "\n--- BANK MENU ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display Account\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) CreateAccount();
        else if (choice == 2) Deposit();
        else if (choice == 3) withdraw();
        else if (choice == 4) display();
        else if (choice == 5) cout << "Goodbye!\n";
        else cout << "Invalid choice.\n";

        if (choice != 5) {
            system("pause");
            system("cls");
        }
    } while (choice != 5);

    _getch();
    return 0;
}

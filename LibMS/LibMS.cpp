#include <iostream>
#include <cstdlib>
using namespace std;

void callMainMenuUI();

void callBookManagmentUI() {
    system("cls");
    int option;
    cout << "-----------------------------\n";
    cout << "|    Book Management Menu   |\n";
    cout << "-----------------------------\n";
    cout << "| 1> Get all books          |\n";
    cout << "| 2> Get book by ID         |\n";
    cout << "| 3> Create book            |\n";
    cout << "| 4> Modify book by ID      |\n";
    cout << "| 5> Delete book by ID      |\n";
    cout << "| 6> Back to Main Menu      |\n";
    cout << "-----------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
        case 1: cout << "callBookManagementUI\n"; break;
        case 2: cout << "callPatronManagementUI\n"; break;
        case 3: cout << "callLoanManagementUI\n"; break;
        case 4: cout << "callAuthorManagementUI\n"; break;
        case 5: callMainMenuUI(); break;
        default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void callPatronManagmentUI() {
    system("cls");
    int option;
    cout << "-----------------------------\n";
    cout << "|   Patron Management Menu  |\n";
    cout << "-----------------------------\n";
    cout << "| 1> Get all patrons        |\n";
    cout << "| 2> Get patron by ID       |\n";
    cout << "| 2> Create patron          |\n";
    cout << "| 3> Modify patron by ID    |\n";
    cout << "| 4> Delete patron by ID    |\n";
    cout << "| 5> Back to Main Menu      |\n";
    cout << "-----------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: cout << "callBookManagementUI\n"; break;
    case 2: cout << "callPatronManagementUI\n"; break;
    case 3: cout << "callLoanManagementUI\n"; break;
    case 4: cout << "callAuthorManagementUI\n"; break;
    case 5: callMainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void callLoanManagmentUI() {
    system("cls");
    int option;
    cout << "-----------------------------\n";
    cout << "|    Loan Management Menu   |\n";
    cout << "-----------------------------\n";
    cout << "| 1> Get all loans          |\n";
    cout << "| 2> Get loan by ID         |\n";
    cout << "| 3> Create loan            |\n";
    cout << "| 4> Modify loan by ID      |\n";
    cout << "| 5> Delete loan by ID      |\n";
    cout << "| 6> Back to Main Menu      |\n";
    cout << "-----------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: cout << "callBookManagementUI\n"; break;
    case 2: cout << "callPatronManagementUI\n"; break;
    case 3: cout << "callLoanManagementUI\n"; break;
    case 4: cout << "callAuthorManagementUI\n"; break;
    case 5: callMainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void callAuthorManagmentUI() {
    system("cls");
    int option;
    cout << "-----------------------------\n";
    cout << "|   Author Management Menu  |\n";
    cout << "-----------------------------\n";
    cout << "| 1> Get all authors        |\n";
    cout << "| 2> Get author by ID       |\n";
    cout << "| 3> Create author          |\n";
    cout << "| 4> Modify author by ID    |\n";
    cout << "| 5> Delete author by ID    |\n";
    cout << "| 6> Back to Main Menu      |\n";
    cout << "-----------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: cout << "callBookManagementUI\n"; break;
    case 2: cout << "callPatronManagementUI\n"; break;
    case 3: cout << "callLoanManagementUI\n"; break;
    case 4: cout << "callAuthorManagementUI\n"; break;
    case 5: callMainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void callMainMenuUI() {
    system("cls");
    int option;
    cout << "-----------------------------\n";
    cout << "| Library Management System |\n";
    cout << "-----------------------------\n";
    cout << "| 1> Book Management        |\n";
    cout << "| 2> Patron Management      |\n";
    cout << "| 3> Loan Management        |\n";
    cout << "| 4> Author Management      |\n";
    cout << "| 5> Logout                 |\n";
    cout << "-----------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: callBookManagmentUI(); break;
    case 2: callPatronManagmentUI(); break;
    case 3: callPatronManagmentUI(); break;
    case 4: callAuthorManagmentUI(); break;
    case 5: cout << "callLogoutUI\n"; break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

int main()
{
    callMainMenuUI();
    return 0;
}




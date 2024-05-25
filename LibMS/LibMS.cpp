#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void callMainMenuUI();

class Book {
    private:
        // Primary Key:
        int id;
        string title;
        string isbn;
        string category;
        int quantity;
        // Foreign Key:
        int authorId;

    public:
        //getter & setter (id)
        int getId() {
            return this->id;
        }
        void setId(int id) {
            this->id = id;
        }
        //getter & setter (title)
        string getTitle() {
            return this->title;
        }
        void setTitle(string title) {
            this->title = title;
        }
        //getter & setter (isbn)
        string getIsbn() {
            return this->isbn;
        }
        void setIsbn(string isbn) {
            this->isbn = isbn;
        }
        //getter & setter (category)
        string getCategory() {
            return this->category;
        }
        void setCategory(string category) {
            this->category = category;
        }
        //getter & setter (quantity)
        int getQuantity() {
            return this->quantity;
        }
        void setQuantity(int quantity) {
            this->quantity = quantity;
        }
        //getter & setter (authorId)
        int getAuthorId() {
            return this->authorId;
        }
        void setAuthorId(int authorId) {
            this->authorId = authorId;
        }

        //Book Constructor
        Book(){}

        Book(int id, string title, string isbn, string category, int quantity, int authorId) {
            this->id = id;
            this->title = title;
            this->isbn = isbn;
            this->category = category;
            this->quantity = quantity;
            this->authorId = authorId;
        }

        // Insert Book
        void insertBookIntoCSV()
        {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::app);

            if (bookCSV.is_open()) {
                bookCSV << this->id       << ',';
                bookCSV << this->title    << ',';
                bookCSV << this->isbn     << ',';
                bookCSV << this->category << ',';
                bookCSV << this->quantity << ',';
                bookCSV << this->authorId << endl;
                bookCSV.close();
            }
            cout << "!Notice: Book Created";
        }

        // Get Book by Id
        void getBookFromCSV(int id) {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::in);

            if (bookCSV.is_open()) {
                string line;
                while (getline(bookCSV, line)) {
                    vector<string> vectVal;
                    stringstream ss(line);

                    while (ss.good()) {
                        string word;
                        getline(ss, word, ',');
                        vectVal.push_back(word);
                    }

                    if (stoi(vectVal[0]) == id) {
                        for (int i = 0; i < 5; i++) {
                            cout << vectVal[i] << "\n";
                        }
                        return;
                    }
                }
                cout << "Can't not found book's id: " << id;
                bookCSV.close();
            }
        }

        // Update Book by Id
        void updateBookInCsv(int id, Book book) {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::in);

            if (bookCSV.is_open()) {
                vector<string> vectObj;
                string line;
                while (getline(bookCSV, line)) {
                    vector<string> vectVal;
                    stringstream ss(line);

                    while (ss.good()) {
                        string word;
                        getline(ss, word, ',');
                        vectVal.push_back(word);
                    }

                    if (stoi(vectVal[0]) == id) {
                        vectVal[0] = to_string(book.getId());
                        vectVal[1] = book.getTitle();
                        vectVal[2] = book.getIsbn();
                        vectVal[3] = book.getCategory();
                        vectVal[4] = to_string(book.getQuantity());
                        vectVal[5] = to_string(book.getAuthorId());
                        string altLine;
                        altLine = vectVal[0] + ','
                            + vectVal[1] + ','
                            + vectVal[2] + ','
                            + vectVal[3] + ','
                            + vectVal[4] + ','
                            + vectVal[5];
                        vectObj.push_back(altLine);
                    }
                    else {
                        vectObj.push_back(line);
                    }
                }
                bookCSV.close();

                fstream bookCSV;
                bookCSV.open("book.csv", ios::out);
                for (int i = 0; i < vectObj.size(); i++) {

                    if (bookCSV.is_open()) {
                        bookCSV << vectObj[i] << "\n";
                    }
                }
                bookCSV.close();
            }
        }

        // Delete Book by Id
        void deleteBookInCsv(int id) {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::in);

            if (bookCSV.is_open()) {
                vector<string> vectObj;
                string line;
                while (getline(bookCSV, line)) {
                    vector<string> vectVal;
                    stringstream ss(line);

                    while (ss.good()) {
                        string word;
                        getline(ss, word, ',');
                        vectVal.push_back(word);
                    }

                    if (stoi(vectVal[0]) != id) {
                        vectObj.push_back(line);
                    }
                }
                bookCSV.close();

                fstream bookCSV;
                bookCSV.open("book.csv", ios::out);
                for (int i = 0; i < vectObj.size(); i++) {
                    if (bookCSV.is_open()) {
                        bookCSV << vectObj[i] << "\n";
                    }
                }
                bookCSV.close();
            }
        }
};


void callBookManagementUI() {
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
    case 1: callBookManagementUI(); break;
    case 2: callPatronManagmentUI(); break;
    case 3: callPatronManagmentUI(); break;
    case 4: callAuthorManagmentUI(); break;
    case 5: cout << "callLogoutUI\n"; break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

int main()
{
    Book book;
    book.getBookFromCSV(3);
    return 0;
}




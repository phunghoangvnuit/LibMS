#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

string username = "phunghoangvnuit";
string password = "hello_world_123";

void loginUI();
void mainMenuUI();
void bookManagementUI();

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
        Book(){};

        Book(int id, string title, string isbn, string category, int quantity, int authorId) {
            this->id = id;
            this->title = title;
            this->isbn = isbn;
            this->category = category;
            this->quantity = quantity;
            this->authorId = authorId;
        }

        /*C.R.U.D - Book.CSV*/

        // Check book id if exsited
        bool checkBookIdIfExsited(int id) {
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
                        return true;
                    }
                }
                bookCSV.close();
                return false;
            }
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
            cout << "Notice: Book Created \n";
            system("pause");
            bookManagementUI();
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
                        cout << "----------------------------------\n";
                        cout << "| BookId   :  " << vectVal[0] << " (Current Version)\n";
                        cout << "| Title    :  " << vectVal[1] << "\n";
                        cout << "| ISBN     :  " << vectVal[2] << "\n";
                        cout << "| Category :  " << vectVal[3] << "\n";
                        cout << "| Quantity :  " << vectVal[4] << "\n";
                        cout << "| AuthorId :  " << vectVal[5] << "\n";
                        cout << "----------------------------------\n";
                        return;
                    }
                }
                bookCSV.close();
                cout << "Can't not found book's id: " << id;
            }
        }

        // Update Book by Id
        void updateBookInCsv(int id, Book book) {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::in);
            bool not_found = true;

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
                        not_found = false;
                    }
                    else {
                        vectObj.push_back(line);
                    }
                }
                bookCSV.close();

                if (not_found == true) {
                    cout << "Can't not found book's id: " << id;
                    return;
                }

                fstream bookCSV;
                bookCSV.open("book.csv", ios::out);
                for (int i = 0; i < vectObj.size(); i++) {

                    if (bookCSV.is_open()) {
                        bookCSV << vectObj[i] << "\n";
                    }
                }
                bookCSV.close();
            }
            cout << "Notice: Book ID " << id << " Updated \n";
            system("pause");
            bookManagementUI();
        }

        // Delete Book by Id
        void deleteBookInCsv(int id) {
            fstream bookCSV;
            bookCSV.open("book.csv", ios::in);
            bool not_found = true;

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
                    } else {
                        not_found = false;
                    }
                }
                bookCSV.close();

                if (not_found == true) {
                    cout << "Can't not found book's id: " << id;
                    return;
                }

                fstream bookCSV;
                bookCSV.open("book.csv", ios::out);
                for (int i = 0; i < vectObj.size(); i++) {
                    if (bookCSV.is_open()) {
                        bookCSV << vectObj[i] << "\n";
                    }
                }
                bookCSV.close();
            }
            cout << "Notice: Book ID " << id << " Deleted \n";
            system("pause");
        }
};

void createBookUI() {
    int id;
    char option = ' ';
    string title;
    string isbn;
    string category;
    int quantity;
    int authorId;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        CREATE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId   :  "; cin >> id;
    if (book.checkBookIdIfExsited(id)) {
    cout << "----------------------------------\n";
    book.getBookFromCSV(id);
    cout << "Notice: BookId is already exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    cout << "| Title    :  "; getline(cin >> ws,title);
    cout << "| ISBN     :  "; getline(cin >> ws,isbn);
    cout << "| Category :  "; getline(cin >> ws,category);
    cout << "| Quantity :  "; cin >> quantity;
    cout << "| AuthorId :  "; cin >> authorId;
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "| YOU WANT TO CREATE THIS BOOK?  |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Book newBook(id, title, isbn, category, quantity, authorId);
            newBook.insertBookIntoCSV();
            createBookUI();
        }
        else if (toupper(option) == 'N') {
            bookManagementUI();
        }
    }
}

void updateBookUI() {
    int id;
    char option = ' ';
    string title;
    string isbn;
    string category;
    int quantity;
    int authorId;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        UPDATE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!book.checkBookIdIfExsited(id)) {
    cout << "Notice: BookId is not exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getBookFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| BookId   :  " << id << " (Update Version)\n";
    cout << "| Title    :  "; getline(cin >> ws, title);
    cout << "| ISBN     :  "; getline(cin >> ws, isbn);
    cout << "| Category :  "; getline(cin >> ws, category);
    cout << "| Quantity :  "; cin >> quantity;
    cout << "| AuthorId :  "; cin >> authorId;
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "| YOU WANT TO UPDATE THIS BOOK?  |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Book altBook(id, title, isbn, category, quantity, authorId);
            altBook.updateBookInCsv(id, altBook);
            updateBookUI();
        }
        else if (toupper(option) == 'N') {
            bookManagementUI();
        }
    }
}

void deleteBookUI() {
    int id;
    char option = ' ';
    Book book;
    system("cls");
    cout << "----------------------------------\n";
    cout << "|        DELETE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!book.checkBookIdIfExsited(id)) {
        cout << "Notice: BookId is not exsited \n";
        system("pause");
        bookManagementUI();
        return;
    };
    book.getBookFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| YOU WANT TO DELETE THIS BOOK?  |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            book.deleteBookInCsv(id);
            deleteBookUI();
        } else if (toupper(option) == 'N') {
            bookManagementUI();
        }
    }
}

void bookManagementUI() {
    system("cls");
    int option;
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all books               |\n";
    cout << "| 2> Get book by ID              |\n";
    cout << "| 3> Get book by Category        |\n";
    cout << "| 4> Get book by Author          |\n";
    cout << "| 5> Create book                 |\n";
    cout << "| 6> Modify book by ID           |\n";
    cout << "| 7> Delete book by ID           |\n";
    cout << "| 8> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: cout << "c1\n"; break;
    case 2: cout << "c2\n"; break;
    case 3: cout << "c3\n"; break;
    case 4: cout << "c4\n"; break;
    case 5: createBookUI(); break;
    case 6: updateBookUI(); break;
    case 7: deleteBookUI(); break;
    case 8: system("cls"); mainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void patronManagmentUI() {
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
    case 5: mainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void loanManagmentUI() {
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
    case 5: mainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void categoryManagmentUI() {
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
    case 5: mainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void authorManagmentUI() {
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
    case 5: mainMenuUI(); break;
    default: cout << "Invalid input! Press 'Enter' to try again!";
    }
}

void logoutUI() {
    char option = ' ';

    system("cls");
    cout << "----------------------------------\n";
    cout << "| YOU WANT TO DELETE THIS BOOK?  |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            loginUI();
        }
        else if (toupper(option) == 'N') {
            mainMenuUI();
        }
    }
}

void loginUI() {
    int option;
    string usernameInput;
    string passwordInput;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|           LOGIN FORM           |\n";
    cout << "----------------------------------\n";
    cout << "| Username: "; getline(cin >> ws, usernameInput);
    cout << "| Password: "; getline(cin >> ws, passwordInput);
    cout << "----------------------------------\n";
    if (usernameInput == username 
    &&  passwordInput == password) 
    {
        mainMenuUI();
    } else {
        system("cls");
        loginUI();
    }
}

void mainMenuUI() {
    system("cls");
    int option;
    cout << "----------------------------------\n";
    cout << "|    LIBRARY MANAGEMENT SYSTEM   |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Book Management             |\n";
    cout << "| 2> Category Management         |\n";
    cout << "| 3> Author Management           |\n";
    cout << "| 4> Patron Management           |\n";
    cout << "| 5> Loan Management             |\n";
    cout << "| 6> Logout                      |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: bookManagementUI(); break;
    case 2: categoryManagmentUI(); break;
    case 3: authorManagmentUI(); break;
    case 4: patronManagmentUI(); break;
    case 5: loanManagmentUI(); break;
    case 6: logoutUI(); break;
    default: system("cls"); mainMenuUI();
    }
}

int main()
{
    //username = "phunghoangvnuit";
    //password = "hello_world_123";
    loginUI();
    return 0;
}




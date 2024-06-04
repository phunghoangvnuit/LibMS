/*Team Leader: Phung Hoang (20070832)   */
/*Team Member 1: Uong Thi Nga (21070270)*/
/*Team Member 2: Bui Linh Dan (20070815)*/     
/*Contact: phunghoangvnuit@gmail.com    */

/*Check my commits on GitHub: https://github.com/phunghoangvnuit/LibMS */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <ctime>

using namespace std;

string username = "phunghoangvnuit";
string password = "hello_world_123";

void loanManagementUI();
void patronManagementUI();
void authorManagementUI();
void categoryManagementUI();
void bookManagementUI();
void mainMenuUI();
void loginUI();
void logoutUI();

/*Book Class*/
class Book {
private:
    int id;
    string title;
    string isbn;
    int quantity;
    int categoryId;
    int authorId;

public:
    //Getter & Setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //Getter & Setter (title)
    string getTitle() {
        return this->title;
    }
    void setTitle(string title) {
        this->title = title;
    }
    //Getter & Setter (isbn)
    string getIsbn() {
        return this->isbn;
    }
    void setIsbn(string isbn) {
        this->isbn = isbn;
    }
    //Getter & Setter (quantity)
    int getQuantity() {
        return this->quantity;
    }
    void setQuantity(int quantity) {
        this->quantity = quantity;
    }
    //Getter & Setter (categoryId)
    int getCategoryId() {
        return this->categoryId;
    }
    void setCategory(int category) {
        this->categoryId = categoryId;
    }
    //Getter & Setter (author)
    int getAuthorId() {
        return this->authorId;
    }
    void setAuthorId(int author) {
        this->authorId = author;
    }

    //Book Constructor
    Book() {};
    Book(int id, string title, string isbn, int quantity, int categoryId, int authorId) {
        this->id = id;
        this->title = title;
        this->isbn = isbn;
        this->quantity = quantity;
        this->categoryId = categoryId;
        this->authorId = authorId;
    }

    //Association
    bool checkReference(int bookId) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[2]) == bookId) {
                    loanCSV.close();
                    return true;
                }
            }
            loanCSV.close();
            return false;
        }
    }
    string getCategoryTitleById(int categoryId) {
        fstream authorCSV;
        authorCSV.open("category.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == categoryId) {
                    return vectVal[1];
                }
            }
            authorCSV.close();
        }
    }
    string getAuthorNameById(int authorId) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == authorId) {
                    return vectVal[1];
                }
            }
            authorCSV.close();
        }
    }
    int getBookQtyFromCSV(int bookId) {
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

                if (stoi(vectVal[0]) == bookId) {
                    return stoi(vectVal[3]);
                }
            }
            bookCSV.close();
        }
    }
    int checkBookQuantity(int bookId, int borrowQty) {
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

                if (stoi(vectVal[0]) == bookId) {
                    if (stoi(vectVal[3]) == 0) { return 0; }; // Message Code 0: Out of Stock
                    if (stoi(vectVal[3]) - borrowQty < 0) { return 1; } // Message Code 1: Quantity cannot meet demand
                    return 2; // Message Code 2: Everything OK!
                }
            }
            bookCSV.close();
        }
    }
    void changeBookQty(int bookId, int change) {
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

                if (stoi(vectVal[0]) == bookId) {
                    vectVal[3] = to_string(stoi(vectVal[3]) + change);
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

    /*C.R.U.D - Book.CSV*/
    // Check If Existed
    bool checkIdExisted(int id) {
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
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }
    bool checkTitleExisted(string title) {
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

                if (vectVal[1] == title) {
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }
    bool checkIsbnExisted(string isbn) {
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

                if (vectVal[2] == isbn) {
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }

    // Insert Book Into CSV
    void insertIntoCSV()
    {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::app);
        if (bookCSV.is_open()) {
            bookCSV << this->id << ',';
            bookCSV << this->title << ',';
            bookCSV << this->isbn << ',';
            bookCSV << this->quantity << ',';
            bookCSV << this->categoryId << ',';
            bookCSV << this->authorId << endl;
            bookCSV.close();
        }
    }

    // Update Book In CSV
    void updateInCSV(int id, Book book) {
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
                    vectVal[3] = to_string(book.getQuantity());
                    vectVal[4] = to_string(book.getCategoryId());
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

    // Get Book From CSV
    void getFromCSV() {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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
                cout << "----------------------------------\n";
                cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                cout << "| Title      :  " << vectVal[1] << "\n";
                cout << "| ISBN       :  " << vectVal[2] << "\n";
                cout << "| Quantity   :  " << vectVal[3] << "\n";
                cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                cout << "----------------------------------\n";
            }
            bookCSV.close();
        }
    }
    void getFromCSVById(int id) {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << " (CurrentQty)\n"; 
                    cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                    cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            bookCSV.close();
        }
    }
    void getFromCSVByTitle(string title) {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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

                if (vectVal[1] == title) {
                    cout << "----------------------------------\n";
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << " (CurrentQty)\n";
                    cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                    cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            bookCSV.close();
        }
    }
    void getFromCSVByIsbn(string isbn) {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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

                if (vectVal[2] == isbn) {
                    cout << "----------------------------------\n";
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << " (CurrentQty)\n";
                    cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                    cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            bookCSV.close();
        }
    }
    void getFromCSVByCateId(int cateId) {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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

                if (stoi(vectVal[4]) == cateId) {
                    cout << "----------------------------------\n";
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << " (CurrentQty)\n";
                    cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                    cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                    cout << "----------------------------------\n";
                }
            }
            bookCSV.close();
        }
    }
    void getFromCSVByCateTitle(string cateTitle) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);
        int cateId;
        Book book;

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == cateTitle) {
                    cateId = stoi(vectVal[0]);
                    getFromCSVByCateId(cateId);
                }
            }
            categoryCSV.close();
        }
    }
    void getFromCSVByAuthId(int authId) {
        fstream bookCSV;
        bookCSV.open("book.csv", ios::in);
        Book book;

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

                if (stoi(vectVal[5]) == authId) {
                    cout << "----------------------------------\n";
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << " (CurrentQty)\n";
                    cout << "| Category   :  " << book.getCategoryTitleById(stoi(vectVal[4])) << "\n";
                    cout << "| Author     :  " << book.getAuthorNameById(stoi(vectVal[5])) << "\n";
                    cout << "----------------------------------\n";
                }
            }
            bookCSV.close();
        }
    }
    void getFromCSVByAuthName(string authName) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);
        int cateId;
        Book book;

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == authName) {
                    cateId = stoi(vectVal[0]);
                    getFromCSVByAuthId(cateId);
                }
            }
            authorCSV.close();
        }
    }

    // Remove Book From CSV
    void removeFromCSV(int id) {
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
void createBookUI() {
    int id;
    string title;
    string isbn;
    int quantity;
    int categoryId;
    int authorId;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        CREATE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId     :  "; cin >> id;
    if (book.checkIdExisted(id)) {
    cout << "----------------------------------\n";
    book.getFromCSVById(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    cout << "| Title      :  "; getline(cin >> ws, title);
    if (book.checkTitleExisted(title)) {
    cout << "----------------------------------\n";
    book.getFromCSVByTitle(title);
    cout << "Notice[!]: Title Is Already Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    cout << "| ISBN       :  "; getline(cin >> ws, isbn);
    if (book.checkIsbnExisted(isbn)) {
    cout << "----------------------------------\n";
    book.getFromCSVByIsbn(isbn);
    cout << "Notice[!]: Isbn Is Already Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    cout << "| Quantity   :  "; cin >> quantity;
    cout << "| CategoryId :  "; cin >> categoryId;
    cout << "| Category   :  " << book.getCategoryTitleById(categoryId) << endl;
    cout << "| AuthorId   :  "; cin >> authorId;
    cout << "| Author     :  " << book.getAuthorNameById(authorId) << endl;
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|       CONFIRM TO CREATE ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (option == 'Y' || option == 'y') {
            Book newBook(id, title, isbn, quantity, categoryId, authorId);
            newBook.insertIntoCSV();
            cout << "Notice[!]: Book Created \n";
            system("pause");
            bookManagementUI();
        }
        else if (option == 'N' || option == 'n') {
            bookManagementUI();
        }
    }
}
void getAllBookUI() {
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    book.getFromCSV();
    system("pause");
    bookManagementUI();
    return;
};
void getBookByIdUI() {
    int id;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| BookId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!book.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getFromCSVById(id);
    system("pause");
    bookManagementUI();
    return;
};
void getBookByTitleUI() {
    string title;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Title    :  "; getline(cin >> ws, title);
    cout << "----------------------------------\n";
    if (!book.checkTitleExisted(title)) {
    cout << "Notice[!]: Title Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getFromCSVByTitle(title);
    system("pause");
    bookManagementUI();
    return;
};
void getBookByIsbnUI() {
    string isbn;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| ISBN     :  "; getline(cin >> ws, isbn);
    cout << "----------------------------------\n";
    if (!book.checkIsbnExisted(isbn)) {
    cout << "Notice[!]: Isbn Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getFromCSVByIsbn(isbn);
    system("pause");
    bookManagementUI();
    return;
};
void getBookByCateUI(){
    string cateTitle;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Category :  "; getline(cin >> ws, cateTitle);
    cout << "----------------------------------\n";
    book.getFromCSVByCateTitle(cateTitle);
    system("pause");
    bookManagementUI();
    return;
}
void getBookByAuthUI() {
    string authName;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Author   :  "; getline(cin >> ws, authName);
    cout << "----------------------------------\n";
    book.getFromCSVByAuthName(authName);
    system("pause");
    bookManagementUI();
    return;
}
void updateBookUI() {
    int id;
    string title;
    string isbn;
    int quantity;
    int categoryId;
    int authorId;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        UPDATE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId     :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!book.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "| BookId     :  " << id << " (Update Version)\n";
    cout << "| Title      :  "; getline(cin >> ws, title);
    cout << "| ISBN       :  "; getline(cin >> ws, isbn);
    cout << "| Quantity   :  "; cin >> quantity;
    cout << "| CategoryId :  "; cin >> categoryId;
    cout << "| Category   :  " << book.getCategoryTitleById(categoryId) << endl;
    cout << "| AuthorId   :  "; cin >> authorId;
    cout << "| Category   :  " << book.getAuthorNameById(authorId) << endl;
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|     YOU WANT TO REPLACED ?     |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Book altBook(id, title, isbn, quantity, categoryId, authorId);
            altBook.updateInCSV(id, altBook);
            cout << "Notice[!]: Book Updated \n";
            system("pause");
            bookManagementUI();
        }
        else if (toupper(option) == 'N') {
            bookManagementUI();
        }
    }
}
void deleteBookUI() {
    int id;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        DELETE BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| BookId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!book.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    }
    if (book.checkReference(id)) {
    cout << "Notice[!]: Cannot Delete \nMake Sure No Reference To A Loan\n";
    system("pause");
    bookManagementUI();
    return;
    }
    book.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            book.removeFromCSV(id);
            cout << "Notice[!]: Book Deleted \n";
            system("pause");
            bookManagementUI();
        }
        else if (toupper(option) == 'N') {
            bookManagementUI();
        }
    }
}
void bookManagementUI() {
    int option;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       BOOK MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all books               |\n";
    cout << "| 2> Get book by ID              |\n";
    cout << "| 3> Get book by title           |\n";
    cout << "| 4> Get book by ISBN            |\n";
    cout << "| 5> Get book by category        |\n";
    cout << "| 6> Get book by author          |\n"; 
    cout << "| 7> Create book                 |\n";
    cout << "| 8> Modify book by ID           |\n";
    cout << "| 9> Delete book by ID           |\n";
    cout << "| 10> Back to Main Menu          |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllBookUI(); break;
    case 2: getBookByIdUI(); break;
    case 3: getBookByTitleUI(); break;
    case 4: getBookByIsbnUI(); break;
    case 5: getBookByCateUI(); break;
    case 6: getBookByAuthUI(); break;
    case 7: createBookUI(); break;
    case 8: updateBookUI(); break;
    case 9: deleteBookUI(); break;
    case 10: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); bookManagementUI(); };
    }
}

/*Category Class*/
class Category{
private:
    int id;
    string title;

public:
    //Getter & Setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //Getter & Setter (title)
    string getTitle() {
        return this->title;
    }
    void setTitle(string title) {
        this->title = title;
    }

    //Book Constructor
    Category(){};
    Category(int id, string title) {
        this->id = id;
        this->title = title;
    }

    // Association
    bool checkReference(int categoryId) {
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

                if (stoi(vectVal[4]) == categoryId) {
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }

    /*C.R.U.D - Category.CSV*/
    // Check CategoryId If Existed
    bool checkIdExisted(int id) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    categoryCSV.close();
                    return true;
                }
            }
            categoryCSV.close();
            return false;
        }
    }
    bool checkTitleExisted(string title) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == title) {
                    categoryCSV.close();
                    return true;
                }
            }
            categoryCSV.close();
            return false;
        }
    }

    // Insert Category Into CSV
    void insertIntoCSV()
    {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::app);

        if (categoryCSV.is_open()) {
            categoryCSV << this->id << ',';
            categoryCSV << this->title << endl;
            categoryCSV.close();
        }
    }

    // Update Category From CSV
    void updateInCSV(int id, Category category) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    vectVal[0] = to_string(category.getId());
                    vectVal[1] = category.getTitle();
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1];
                    vectObj.push_back(altLine);
                }
                else {
                    vectObj.push_back(line);
                }
            }
            categoryCSV.close();

            fstream categoryCSV;
            categoryCSV.open("category.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {

                if (categoryCSV.is_open()) {
                    categoryCSV << vectObj[i] << "\n";
                }
            }
            categoryCSV.close();
        }
    }

    // Get Category From CSV
    void getFromCSV() {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }
                cout << "----------------------------------\n";
                cout << "| CateId   :  " << vectVal[0] << " (Current Version)\n";
                cout << "| Title    :  " << vectVal[1] << "\n";
                cout << "----------------------------------\n";
            }
            categoryCSV.close();
        }
    }
    void getFromCSVById(int id) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    cout << "----------------------------------\n";
                    cout << "| CateId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title    :  " << vectVal[1] << "\n";
                    cout << "----------------------------------\n";
                    categoryCSV.close();
                    return;
                }
            }
            categoryCSV.close();
        }
    }
    void getFromCSVByTitle(string title) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            string line;
            while (getline(categoryCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == title) {
                    cout << "----------------------------------\n";
                    cout << "| CateId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title    :  " << vectVal[1] << "\n";
                    cout << "----------------------------------\n";
                    categoryCSV.close();
                    return;
                }
            }
            categoryCSV.close();
        }
    }

    // Remove Category From CSV
    void removeFromCSV(int id) {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::in);

        if (categoryCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(categoryCSV, line)) {
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
            categoryCSV.close();

            fstream categoryCSV;
            categoryCSV.open("category.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {
                if (categoryCSV.is_open()) {
                    categoryCSV << vectObj[i] << "\n";
                }
            }
            categoryCSV.close();
        }
    }
};
void createCategoryUI() {
    int id;
    string title;
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|      CREATE CATEGORY FORM      |\n";
    cout << "----------------------------------\n";
    cout << "| CateId   :  "; cin >> id;
    if (category.checkIdExisted(id)) {
    cout << "----------------------------------\n";
    category.getFromCSVById(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    cout << "| Title    :  "; getline(cin >> ws, title);
    if (category.checkTitleExisted(title)) {
    cout << "----------------------------------\n";
    category.getFromCSVByTitle(title);
    cout << "Notice[!]: Title Is Already Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|       CONFIRM TO CREATE ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Category newCategory(id, title);
            newCategory.insertIntoCSV();
            cout << "Notice[!]: Category Created \n";
            system("pause");
            categoryManagementUI();
        }
        else if (toupper(option) == 'N') {
            categoryManagementUI();
        }
    }
}
void getAllCategoryUI() {
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|    CATEGORY MANAGEMENT MENU    |\n";
    cout << "----------------------------------\n";
    category.getFromCSV();
    system("pause");
    categoryManagementUI();
    return;
};
void getCategoryByIdUI() {
    int id;
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|    CATEGORY MANAGEMENT MENU    |\n";
    cout << "----------------------------------\n";
    cout << "| CateId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!category.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    category.getFromCSVById(id);
    system("pause");
    categoryManagementUI();
    return;
};
void getCategoryByTitleUI() {
    string cateTitle;
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|    CATEGORY MANAGEMENT MENU    |\n";
    cout << "----------------------------------\n";
    cout << "| Title    :  "; getline(cin >> ws, cateTitle);
    cout << "----------------------------------\n";
    if (!category.checkTitleExisted(cateTitle)) {
    cout << "Notice[!]: Title Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    category.getFromCSVByTitle(cateTitle);
    system("pause");
    categoryManagementUI();
    return;
};
void updateCategoryUI() {
    int id;
    string title;
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|      UPDATE CATEGORY FORM      |\n";
    cout << "----------------------------------\n";
    cout << "| CateId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!category.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    category.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "| CateId   :  " << id << " (Update Version)\n";
    cout << "| Title    :  "; getline(cin >> ws, title);
    if (category.checkTitleExisted(title)) {
    cout << "----------------------------------\n";
    category.getFromCSVByTitle(title);
    cout << "Notice[!]: Title Is Already Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|     YOU WANT TO REPLACED ?     |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Category altCategory(id, title);
            altCategory.updateInCSV(id, altCategory);
            cout << "Notice[!]: Category Updated \n";
            system("pause");
            categoryManagementUI();
        }
        else if (toupper(option) == 'N') {
            categoryManagementUI();
        }
    }
}
void deleteCategoryUI() {
    int id;
    Category category;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|      DELETE CATEGORY FORM      |\n";
    cout << "----------------------------------\n";
    cout << "| CateId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!category.checkIdExisted(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        categoryManagementUI();
        return;
    }
    category.getFromCSVById(id);
    if (category.checkReference(id)) {
        cout << "Notice[!]: Cannot Delete \nMake Sure No Reference To A Book\n";
        system("pause");
        categoryManagementUI();
        return;
    };
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            category.removeFromCSV(id);
            cout << "Notice[!]: Category Deleted \n";
            system("pause");
            categoryManagementUI();
        }
        else if (toupper(option) == 'N') {
            categoryManagementUI();
        }
    }
}
void categoryManagementUI() {
    int option;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|    CATEGORY MANAGEMENT MENU    |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all categories          |\n";
    cout << "| 2> Get category by ID          |\n";
    cout << "| 3> Get category by title       |\n";
    cout << "| 4> Create category             |\n";
    cout << "| 5> Modify category by ID       |\n";
    cout << "| 6> Delete category by ID       |\n";
    cout << "| 7> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllCategoryUI(); break;
    case 2: getCategoryByIdUI(); break;
    case 3: getCategoryByTitleUI();break;
    case 4: createCategoryUI(); break;
    case 5: updateCategoryUI(); break;
    case 6: deleteCategoryUI(); break;
    case 7: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); categoryManagementUI(); };
    }
}

/*Author Class*/
class Author{
private:
    int id;
    string name;
    string email;

public:
    //Getter & Setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //Getter & Setter (name)
    string getName() {
        return this->name;
    }
    void setName(string name) {
        this->name = name;
    }
    //Getter & Setter (email)
    string getEmail() {
        return this->email;
    }
    void setEmail(string email) {
        this->email = email;
    }

    //Author Constructor
    Author() {};
    Author(int id, string name, string email) {
        this->id = id;
        this->name = name;
        this->email = email;
    }

    //Association
    bool checkReference(int authorId) {
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

                if (stoi(vectVal[5]) == authorId) {
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }

    /*C.R.U.D - Author.CSV*/
    // Check AuthorId If Existed
    bool checkIdExisted(int id) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    authorCSV.close();
                    return true;
                }
            }
            authorCSV.close();
            return false;
        }
    }
    bool checkNameExisted(string name) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == name) {
                    authorCSV.close();
                    return true;
                }
            }
            authorCSV.close();
            return false;
        }
    }
    bool checkEmailExisted(string email) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[2] == email) {
                    authorCSV.close();
                    return true;
                }
            }
            authorCSV.close();
            return false;
        }
    }

    // Insert Author Into CSV
    void insertIntoCSV()
    {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::app);

        if (authorCSV.is_open()) {
            authorCSV << this->id << ',';
            authorCSV << this->name << ',';
            authorCSV << this->email << endl;
            authorCSV.close();
        }
    }

    // Update Author From CSV
    void updateInCSV(int id, Author author) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    vectVal[0] = to_string(author.getId());
                    vectVal[1] = author.getName();
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1];
                    vectObj.push_back(altLine);
                }
                else {
                    vectObj.push_back(line);
                }
            }
            authorCSV.close();

            fstream authorCSV;
            authorCSV.open("author.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {

                if (authorCSV.is_open()) {
                    authorCSV << vectObj[i] << "\n";
                }
            }
            authorCSV.close();
        }
    }

    // Get Author From CSV
    void getFromCSV() {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }
                cout << "----------------------------------\n";
                cout << "| AuthId   :  " << vectVal[0] << " (Current Version)\n";
                cout << "| Name     :  " << vectVal[1] << "\n";
                cout << "| Email    :  " << vectVal[2] << "\n";
                cout << "----------------------------------\n";
            }
            authorCSV.close();
        }
    }
    void getFromCSVById(int id) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    cout << "----------------------------------\n";
                    cout << "| AuthId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name     :  " << vectVal[1] << "\n";
                    cout << "| Email    :  " << vectVal[2] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            authorCSV.close();
        }
    }
    void getFromCSVByName(string name) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == name) {
                    cout << "----------------------------------\n";
                    cout << "| AuthId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name     :  " << vectVal[1] << "\n";
                    cout << "| Email    :  " << vectVal[2] << "\n";
                    cout << "----------------------------------\n";
                }
            }
            authorCSV.close();
        }
    }
    void getFromCSVByEmail(string email) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            string line;
            while (getline(authorCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[2] == email) {
                    cout << "----------------------------------\n";
                    cout << "| AuthId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name     :  " << vectVal[1] << "\n";
                    cout << "| Email    :  " << vectVal[2] << "\n";
                    cout << "----------------------------------\n";
                }
            }
            authorCSV.close();
        }
    }

    // Remove Author From CSV
    void removeFromCSV(int id) {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::in);

        if (authorCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(authorCSV, line)) {
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
            authorCSV.close();

            fstream authorCSV;
            authorCSV.open("author.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {
                if (authorCSV.is_open()) {
                    authorCSV << vectObj[i] << "\n";
                }
            }
            authorCSV.close();
        }
    }
};
void createAuthorUI() {
    int id;
    string name;
    string email;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       CREATE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    if (author.checkIdExisted(id)) {
    cout << "----------------------------------\n";
    author.getFromCSVById(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "| Email    :  "; getline(cin >> ws, email);
    if (author.checkEmailExisted(email)) {
    cout << "----------------------------------\n";
    author.getFromCSVByEmail(email);
    cout << "Notice[!]: Email Is Already Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|       CONFIRM TO CREATE ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Author newAuthor(id, name, email);
            newAuthor.insertIntoCSV();
            cout << "Notice[!]: Author Created \n";
            system("pause");
            authorManagementUI();
        }
        else if (toupper(option) == 'N') {
            authorManagementUI();
        }
    }
}
void getAllAuthorUI() {
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     AUTHOR MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    author.getFromCSV();
    system("pause");
    authorManagementUI();
    return;
};
void getAuthorByIdUI() {
    int id;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     AUTHOR MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!author.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    author.getFromCSVById(id);
    system("pause");
    authorManagementUI();
    return;
};
void getAuthorByNameUI() {
    string authName;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     AUTHOR MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Name     :  "; getline(cin >> ws, authName);
    cout << "----------------------------------\n";
    if (!author.checkNameExisted(authName)) {
    cout << "Notice[!]: Name Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    author.getFromCSVByName(authName);
    system("pause");
    authorManagementUI();
    return;
};
void getAuthorByEmailUI() {
    string email;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     AUTHOR MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Email    :  "; getline(cin >> ws, email);
    cout << "----------------------------------\n";
    if (!author.checkEmailExisted(email)) {
    cout << "Notice[!]: Email Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    author.getFromCSVByEmail(email);
    system("pause");
    authorManagementUI();
    return;
};
void updateAuthorUI() {
    int id;
    string name;
    string email;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       UPDATE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!author.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    author.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "| AuthId   :  " << id << " (Update Version)\n";
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "| Email    :  "; getline(cin >> ws, email);
    if (author.checkEmailExisted(email)) {
    cout << "----------------------------------\n";
    author.getFromCSVByEmail(email);
    cout << "Notice[!]: Email Is Already Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|     YOU WANT TO REPLACED ?     |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Author altAuthor(id, name, email);
            altAuthor.updateInCSV(id, altAuthor);
            cout << "Notice[!]: Author Updated \n";
            system("pause");
            authorManagementUI();
        }
        else if (toupper(option) == 'N') {
            authorManagementUI();
        }
    }
}
void deleteAuthorUI() {
    int id;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       DELETE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!author.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    }
    author.getFromCSVById(id);
    if (author.checkReference(id)) {
    cout << "Notice[!]: Cannot Delete \nMake Sure No Reference To A Book\n";
    system("pause");
    authorManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            author.removeFromCSV(id);
            cout << "Notice[!]: Author Deleted \n";
            system("pause");
            authorManagementUI();
        }
        else if (toupper(option) == 'N') {
            authorManagementUI();
        }
    }
}
void authorManagementUI() {
    int option;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     AUTHOR MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all authors             |\n";
    cout << "| 2> Get author by ID            |\n";
    cout << "| 3> Get author by name          |\n";
    cout << "| 4> Get author by email         |\n";
    cout << "| 5> Create author               |\n";
    cout << "| 6> Modify author by ID         |\n";
    cout << "| 7> Delete author by ID         |\n";
    cout << "| 8> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllAuthorUI(); break;
    case 2: getAuthorByIdUI(); break;
    case 3: getAuthorByNameUI(); break;
    case 4: getAuthorByEmailUI(); break;
    case 5: createAuthorUI(); break;
    case 6: updateAuthorUI(); break;
    case 7: deleteAuthorUI(); break;
    case 8: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); authorManagementUI(); };
    }
}

/*Patron Class*/
class Patron{
private:
    int id;
    string name;
    string phoneNumber;
    string email;
    string address;

public:
    //Getter & Setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //Getter & Setter (name)
    string getName() {
        return this->name;
    }
    void setName(string name) {
        this->name = name;
    }
    //Getter & Setter (phoneNumber)
    string getPhoneNumber() {
        return this->phoneNumber;
    }
    void setPhoneNumber(string phoneNumber) {
        this->phoneNumber = phoneNumber;
    }
    //Getter & Setter (email)
    string getEmail() {
        return this->email;
    }
    void setEmail(string email) {
        this->email = email;
    }
    //Getter & Setter (email)
    string getAddress() {
        return this->address;
    }
    void setAddress(string address) {
        this->address = address;
    }

    //Patron Constructor
    Patron() {};
    Patron(int id, string name, string phoneNumber, string email, string address) {
        this->id = id;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->email = email;
        this->address = address;
    }

    //Association

    /*C.R.U.D - Author.CSV*/
    // Check PatronId If Existed
    bool checkIdExisted(int id) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    patronCSV.close();
                    return true;
                }
            }
            patronCSV.close();
            return false;
        }
    }
    bool checkNameExisted(string name) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == name) {
                    patronCSV.close();
                    return true;
                }
            }
            patronCSV.close();
            return false;
        }
    }
    bool checkPhoneExisted(string phoneNumber) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[2] == phoneNumber) {
                    patronCSV.close();
                    return true;
                }
            }
            patronCSV.close();
            return false;
        }
    }
    bool checkEmailExisted(string email) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[3] == email) {
                    patronCSV.close();
                    return true;
                }
            }
            patronCSV.close();
            return false;
        }
    }
    bool checkAddressExisted(string address) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[4] == address) {
                    patronCSV.close();
                    return true;
                }
            }
            patronCSV.close();
            return false;
        }
    }

    // Insert Patron Into CSV
    void insertIntoCSV()
    {
        fstream authorCSV;
        authorCSV.open("patron.csv", ios::app);

        if (authorCSV.is_open()) {
            authorCSV << this->id << ',';
            authorCSV << this->name << ',';
            authorCSV << this->phoneNumber << ',';
            authorCSV << this->email << ',';
            authorCSV << this->address << endl;
            authorCSV.close();
        }
    }

    // Update Patron From CSV
    void updateInCSV(int id, Patron patron) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    vectVal[0] = to_string(patron.getId());
                    vectVal[1] = patron.getName();
                    vectVal[2] = patron.getPhoneNumber();
                    vectVal[3] = patron.getEmail();
                    vectVal[4] = patron.getAddress();
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1] + ','
                            + vectVal[2] + ','
                            + vectVal[3] + ','
                            + vectVal[4];
                    vectObj.push_back(altLine);
                }
                else {
                    vectObj.push_back(line);
                }
            }
            patronCSV.close();

            fstream patronCSV;
            patronCSV.open("patron.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {

                if (patronCSV.is_open()) {
                    patronCSV << vectObj[i] << "\n";
                }
            }
            patronCSV.close();
        }
    }

    // Get Author From CSV
    void getFromCSV() {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }
                cout << "----------------------------------\n";
                cout << "| PatrId   :  " << vectVal[0] << " (Current Version)\n";
                cout << "| Name     :  " << vectVal[1] << "\n";
                cout << "| Phone    :  " << vectVal[2] << "\n";
                cout << "| Email    :  " << vectVal[3] << "\n";
                cout << "| Address  :  " << vectVal[4] << "\n";
                cout << "----------------------------------\n";
            }
            patronCSV.close();
        }
    }
    void getFromCSVById(int id) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    cout << "----------------------------------\n";
                    cout << "| PatrId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name       :  " << vectVal[1] << "\n";
                    cout << "| Phone      :  " << vectVal[2] << "\n";
                    cout << "| Email      :  " << vectVal[3] << "\n";
                    cout << "| Address    :  " << vectVal[4] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByName(string name) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == name) {
                    cout << "----------------------------------\n";
                    cout << "| PatrId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name       :  " << vectVal[1] << "\n";
                    cout << "| Phone      :  " << vectVal[2] << "\n";
                    cout << "| Email      :  " << vectVal[3] << "\n";
                    cout << "| Address    :  " << vectVal[4] << "\n";
                    cout << "----------------------------------\n";
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByPhone(string phoneNumber) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[2] == phoneNumber) {
                    cout << "----------------------------------\n";
                    cout << "| PatrId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name       :  " << vectVal[1] << "\n";
                    cout << "| Phone      :  " << vectVal[2] << "\n";
                    cout << "| Email      :  " << vectVal[3] << "\n";
                    cout << "| Address    :  " << vectVal[4] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByEmail(string email) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[3] == email) {
                    cout << "----------------------------------\n";
                    cout << "| PatrId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name       :  " << vectVal[1] << "\n";
                    cout << "| Phone      :  " << vectVal[2] << "\n";
                    cout << "| Email      :  " << vectVal[3] << "\n";
                    cout << "| Address    :  " << vectVal[4] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByAdd(string address) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[4] == address) {
                    cout << "----------------------------------\n";
                    cout << "| PatrId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name       :  " << vectVal[1] << "\n";
                    cout << "| Phone      :  " << vectVal[2] << "\n";
                    cout << "| Email      :  " << vectVal[3] << "\n";
                    cout << "| Address    :  " << vectVal[4] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            patronCSV.close();
        }
    }

    // Remove Author From CSV
    void removeFromCSV(int id) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);

        if (patronCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(patronCSV, line)) {
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
            patronCSV.close();

            fstream authorCSV;
            patronCSV.open("patron.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {
                if (patronCSV.is_open()) {
                    patronCSV << vectObj[i] << "\n";
                }
            }
            patronCSV.close();
        }
    }
};
void createPatronUI() {
    int id;
    string name;
    string phoneNumber;
    string email;
    string address;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       CREATE PATRON FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| PatrId   :  "; cin >> id;
    if (patron.checkIdExisted(id)) {
    cout << "----------------------------------\n";
    patron.getFromCSVById(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "| Phone    :  "; getline(cin >> ws, phoneNumber);
    if (patron.checkPhoneExisted(phoneNumber)) {
    cout << "----------------------------------\n";
    patron.getFromCSVByPhone(phoneNumber);
    cout << "Notice[!]: Phone Is Already Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    cout << "| Email    :  "; getline(cin >> ws, email);
    if (patron.checkEmailExisted(email)) {
    cout << "----------------------------------\n";
    patron.getFromCSVByEmail(email);
    cout << "Notice[!]: Email Is Already Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    cout << "| Address  :  "; getline(cin >> ws, address);
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|       CONFIRM TO CREATE ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Patron patron(id, name, phoneNumber, email, address);
            patron.insertIntoCSV();
            cout << "Notice[!]: Patron Created \n";
            system("pause");
            patronManagementUI();
        }
        else if (toupper(option) == 'N') {
            patronManagementUI();
        }
    }
}
void getAllPatronUI() {
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    patron.getFromCSV();
    system("pause");
    patronManagementUI();
    return;
};
void getPatronByIdUI() {
    int id;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| PatrId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!patron.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVById(id);
    system("pause");
    patronManagementUI();
    return;
};
void getPatronByNameUI() {
    string name;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "----------------------------------\n";
    if (!patron.checkNameExisted(name)) {
    cout << "Notice[!]: Name Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVByName(name);
    system("pause");
    patronManagementUI();
    return;
};
void getPatronByPhoneUI() {
    string phoneNumber;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Phone    :  "; getline(cin >> ws, phoneNumber);
    cout << "----------------------------------\n";
    if (!patron.checkPhoneExisted(phoneNumber)) {
    cout << "Notice[!]: Phone Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVByPhone(phoneNumber);
    system("pause");
    patronManagementUI();
    return;
};
void getPatronByEmailUI() {
    string email;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Email    :  "; getline(cin >> ws, email);
    cout << "----------------------------------\n";
    if (!patron.checkEmailExisted(email)) {
    cout << "Notice[!]: Email Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVByEmail(email);
    system("pause");
    patronManagementUI();
    return;
};
void getPatronByAddUI() {
    string address;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| Address  :  "; getline(cin >> ws, address);
    cout << "----------------------------------\n";
    if (!patron.checkAddressExisted(address)) {
    cout << "Notice[!]: Address Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVByAdd(address);
    system("pause");
    patronManagementUI();
    return;
};
void updatePatronUI() {
    int id;
    string name;
    string phoneNumber;
    string email;
    string address;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       UPDATE PATRON FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| PatrId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!patron.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "| PatrId   :  " << id << " (Update Version)\n";
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "| Phone    :  "; getline(cin >> ws, name);
    if (patron.checkPhoneExisted(phoneNumber)) {
    cout << "----------------------------------\n";
    patron.getFromCSVByPhone(phoneNumber);
    cout << "Notice[!]: Phone Is Already Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    cout << "| Email    :  "; getline(cin >> ws, name);
    if (patron.checkEmailExisted(email)) {
    cout << "----------------------------------\n";
    patron.getFromCSVByEmail(email);
    cout << "Notice[!]: Email Is Already Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    cout << "| Address  :  "; getline(cin >> ws, address);
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|     YOU WANT TO REPLACED ?     |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Patron altPatron(id, name, phoneNumber, email, address);
            altPatron.updateInCSV(id, altPatron);
            cout << "Notice[!]: Author Updated \n";
            system("pause");
            authorManagementUI();
        }
        else if (toupper(option) == 'N') {
            authorManagementUI();
        }
    }
}
void deletePatronUI() {
    int id;
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       DELETE PATRON FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| PatrId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!patron.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    patronManagementUI();
    return;
    };
    patron.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            patron.removeFromCSV(id);
            cout << "Notice[!]: Patron Deleted \n";
            system("pause");
            patronManagementUI();
        }
        else if (toupper(option) == 'N') {
            patronManagementUI();
        }
    }
}
void patronManagementUI() {
    int option;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|     PATRON MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all patrons             |\n";
    cout << "| 2> Get patron by ID            |\n";
    cout << "| 3> Get patron by name          |\n";
    cout << "| 4> Get patron by phone number  |\n";
    cout << "| 5> Get patron by email         |\n";
    cout << "| 6> Get patron by address       |\n";
    cout << "| 7> Create patron               |\n";
    cout << "| 8> Modify patron by ID         |\n";
    cout << "| 9> Delete patron by ID         |\n";
    cout << "| 10> Back to Main Menu          |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllPatronUI(); break;
    case 2: getPatronByIdUI(); break;
    case 3: getPatronByNameUI() ; break;
    case 4: getPatronByPhoneUI(); break;
    case 5: getPatronByEmailUI(); break;
    case 6: getPatronByAddUI(); break;
    case 7: createPatronUI(); break;
    case 8: updatePatronUI(); break;
    case 9: deletePatronUI(); break;
    case 10: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); patronManagementUI(); };
    }
}

class Loan {
private:
    int id;
    int patronId;
    int bookId;
    int borrowQty;
    string borrowDate;
    string dueDate;
    string returnDate;
    string returnStat;
    Patron patron;
    Book book;

public:
    //Getter & Setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //Getter & Setter (patronId)
    int getPatronId() {
        return this->patronId;
    }
    void setPatronId(int patronId) {
        this->patronId = patronId;
    }
    //Getter & Setter (bookId)
    int getBookId() {
        return this->bookId;
    }
    void setBookId(int bookId) {
        this->bookId = bookId;
    }
    //Getter & Setter (bookQty)
    int getBorrowQty() {
        return this->borrowQty;
    }
    void setBorrowQty(int borrowQty) {
        this->borrowQty = borrowQty;
    }
    //Getter & Setter (borrowDate)
    string getBorrowDate() {
        return this->borrowDate;
    }
    void setBorrowDate(string borrowDate) {
        this->borrowDate = borrowDate;
    }
    //Getter & Setter (dueDate)
    string getDueDate() {
        return this->dueDate;
    }
    void setDueDate(string dueDate) {
        this->dueDate = dueDate;
    }
    //Getter & Setter (returnDate)
    string getReturnDate() {
        return this->returnDate;
    }
    void setReturnDate(string returnDate) {
        this->returnDate = returnDate;
    }
    //Getter & Setter (returnStat)
    string getReturnStat() {
        return this->returnStat;
    }
    void setReturnStat(string returnStat) {
        this->returnStat = returnStat;
    }

    //Loan Constructor
    Loan() {};
    Loan(int id, int patronId, int bookId, int borrowQty) {
        this->id = id;
        this->patronId = patronId;
        this->bookId = bookId;
        this->borrowQty = borrowQty;
    };
    Loan(int id, int patronId, int bookId, int borrowQty, string borrowDate, string dueDate, string returnDate, string returnStat) {
        this->id = id;
        this->patronId = patronId;
        this->bookId = bookId;
        this->borrowQty = borrowQty;
        this->borrowDate = borrowDate;
        this->dueDate = dueDate;
        this->returnDate = returnDate;
        this->returnStat = returnStat;
    }

    //Association
    bool checkReference(int bookId) {
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

                if (stoi(vectVal[0]) == bookId) {
                    bookCSV.close();
                    return true;
                }
            }
            bookCSV.close();
            return false;
        }
    }
    int getBookIdFromCSV(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    return stoi(vectVal[2]);
                }
            }
            loanCSV.close();
        }
    }
    int getBorrowQtyFromCSV(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    return stoi(vectVal[3]);
                }
            }
            loanCSV.close();
        }
    }
    void updateReturnStat(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    vectVal[7] = "Returned";
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1] + ','
                            + vectVal[2] + ','
                            + vectVal[3] + ','
                            + vectVal[4] + ','
                            + vectVal[5] + ','
                            + vectVal[6] + ','
                            + vectVal[7];
                    vectObj.push_back(altLine);
                }
                else {
                    vectObj.push_back(line);
                }
            }
            loanCSV.close();

            fstream loanCSV;
            loanCSV.open("loan.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {

                if (loanCSV.is_open()) {
                    loanCSV << vectObj[i] << "\n";
                }
            }
            loanCSV.close();
        }
    }
    void borrowBook(int bookId, int borrowQty) {
        Book book;
        book.changeBookQty(bookId, -borrowQty);
    }
    void returnBook(int loanId) {
        Book book;
        Loan loan;
        int bookId = loan.getBookIdFromCSV(loanId);
        int borrowQty = loan.getBorrowQtyFromCSV(loanId);
        book.changeBookQty(bookId, borrowQty);
        loan.updateReturnStat(loanId);
    }


    /*C.R.U.D - Loan.CSV*/
    // Check If Existed
    bool checkIdExisted(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    loanCSV.close();
                    return true;
                }
            }
            loanCSV.close();
            return false;
        }
    }
    bool checkIfReturned(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[7] == "Returned") {
                    loanCSV.close();
                    return true;
                }
            }
            loanCSV.close();
            return false;
        }
    }

    // Insert Loan Into CSV
    void insertIntoCSV()
    {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::app);

        if (loanCSV.is_open()) {
            loanCSV << this->id << ',';
            loanCSV << this->patronId << ',';
            loanCSV << this->bookId << ',';
            loanCSV << this->borrowQty << ',';
            loanCSV << this->borrowDate << ',';
            loanCSV << this->dueDate << ',';
            loanCSV << this->returnDate << ',';
            loanCSV << this->returnStat << endl;
            loanCSV.close();
        }
    }

    // Update Loan In CSV
    void updateInCSV(int id, Loan loan) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    vectVal[0] = to_string(loan.getId());
                    vectVal[1] = to_string(loan.getPatronId());
                    vectVal[2] = to_string(loan.getBookId());
                    vectVal[3] = to_string(loan.getBorrowQty());
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1] + ','
                            + vectVal[2] + ','
                            + vectVal[3] + ','
                            + vectVal[4] + ','
                            + vectVal[5] + ','
                            + vectVal[6] + ','
                            + vectVal[7];
                    vectObj.push_back(altLine);
                }
                else {
                    vectObj.push_back(line);
                }
            }
            loanCSV.close();

            fstream loanCSV;
            loanCSV.open("loan.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {

                if (loanCSV.is_open()) {
                    loanCSV << vectObj[i] << "\n";
                }
            }
            loanCSV.close();
        }
    }

    // Get Loan From CSV
    void getFromCSV() {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);
        Patron patron;

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }
                cout << "----------------------------------\n";
                cout << "| LoanId     :  " << vectVal[0] << " (Current Version)\n";
                patron.getFromCSVById(stoi(vectVal[1]));
                book.getFromCSVById(stoi(vectVal[2]));
                cout << "| BookQty    :  " << vectVal[3] << "\n";
                cout << "| BorrowDate :  " << vectVal[4] << "\n";
                cout << "| DueDate    :  " << vectVal[5] << "\n";
                cout << "| ReturnDate :  " << vectVal[6] << "\n";
                cout << "| ReturnStat :  " << vectVal[7] << "\n";
                cout << "----------------------------------\n\n\n\n\n";
            }
            loanCSV.close();
        }
    }
    void getFromCSVById(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);
        Book book;
        Patron patron;

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[0]) == id) {
                    cout << "----------------------------------\n";
                    cout << "| LoanId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "----------------------------------\n";
                    patron.getFromCSVById(stoi(vectVal[1]));
                    book.getFromCSVById(stoi(vectVal[2]));
                    cout << "----------------------------------\n";
                    cout << "| BookQty    :  " << vectVal[3] << "\n";
                    cout << "| BorrowDate :  " << vectVal[4] << "\n";
                    cout << "| DueDate    :  " << vectVal[5] << "\n";
                    cout << "| ReturnDate :  " << vectVal[6] << "\n";
                    cout << "| ReturnStat :  " << vectVal[7] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            loanCSV.close();
        }
    }
    void getFromCSVByPatrId(int patrId) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);
        Book book;

        if (loanCSV.is_open()) {
            string line;
            while (getline(loanCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (stoi(vectVal[1]) == patrId) {
                    cout << "----------------------------------\n";
                    cout << "| LoanId     :  " << vectVal[0] << " (Current Version)\n";
                    patron.getFromCSVById(stoi(vectVal[1]));
                    book.getFromCSVById(stoi(vectVal[2]));
                    cout << "| BorrowQty  :  " << vectVal[3] << "\n";
                    cout << "| BorrowDate :  " << vectVal[4] << "\n";
                    cout << "| DueDate    :  " << vectVal[5] << "\n";
                    cout << "| ReturnDate :  " << vectVal[6] << "\n";
                    cout << "| ReturnStat :  " << vectVal[7] << "\n";
                    cout << "----------------------------------\n\n\n\n\n";
                }
            }
            loanCSV.close();
        }
    }
    void getFromCSVByPatrName(string patrName) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);
        int patrId;
        Book book;

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[1] == patrName) {
                    patrId = stoi(vectVal[0]);
                    getFromCSVByPatrId(patrId);
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByPatrPhone(string patrPhone) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);
        int patrId;
        Book book;

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[2] == patrPhone) {
                    patrId = stoi(vectVal[0]);
                    getFromCSVByPatrId(patrId);
                }
            }
            patronCSV.close();
        }
    }
    void getFromCSVByPatrEmail(string patrEmail) {
        fstream patronCSV;
        patronCSV.open("patron.csv", ios::in);
        int patrId;
        Book book;

        if (patronCSV.is_open()) {
            string line;
            while (getline(patronCSV, line)) {
                vector<string> vectVal;
                stringstream ss(line);

                while (ss.good()) {
                    string word;
                    getline(ss, word, ',');
                    vectVal.push_back(word);
                }

                if (vectVal[3] == patrEmail) {
                    patrId = stoi(vectVal[0]);
                    getFromCSVByPatrId(patrId);
                }
            }
            patronCSV.close();
        }
    }

    // Remove Loan From CSV 
    void removeFromCSV(int id) {
        fstream loanCSV;
        loanCSV.open("loan.csv", ios::in);

        if (loanCSV.is_open()) {
            vector<string> vectObj;
            string line;
            while (getline(loanCSV, line)) {
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
            loanCSV.close();

            fstream loanCSV;
            loanCSV.open("loan.csv", ios::out);
            for (int i = 0; i < vectObj.size(); i++) {
                if (loanCSV.is_open()) {
                    loanCSV << vectObj[i] << "\n";
                }
            }
            loanCSV.close();
        }
    }
};
void getAllLoanUI() {
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    loan.getFromCSV();
    system("pause");
    loanManagementUI();
    return;
};
void getLoanByIdUI() {
    int id;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| LoanId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!loan.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    loanManagementUI();
    return;
    };
    loan.getFromCSVById(id);
    system("pause");
    loanManagementUI();
    return;
};
void getLoanByPatrIdUI() {
    int patrId;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| PatrId   :  "; cin >> patrId;
               
    cout << "----------------------------------\n";
    loan.getFromCSVByPatrId(patrId);
    system("pause");
    bookManagementUI();
    return;
}
void getLoanByPatrNameUI() {
    string patrName;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| PatrName :  "; getline(cin >> ws, patrName);
    cout << "----------------------------------\n";
    loan.getFromCSVByPatrName(patrName);
    system("pause");
    bookManagementUI();
    return;
}
void getLoanByPatrPhoneUI() {
    string patrPhone;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| PatrPhone:  "; getline(cin >> ws, patrPhone);
    cout << "----------------------------------\n";
    loan.getFromCSVByPatrPhone(patrPhone);
    system("pause");
    bookManagementUI();
    return;
}
void getLoanByPatrEmailUI() {
    string patrEmail;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       LOAN MANAGEMENT MENU     |\n";
    cout << "----------------------------------\n";
    cout << "| PatrEmail:  "; getline(cin >> ws, patrEmail);
    cout << "----------------------------------\n";
    loan.getFromCSVByPatrEmail(patrEmail);
    system("pause");
    bookManagementUI();
    return;
}
void borrowBookUI() {
    int id;
    int patronId;
    int bookId;
    int borrowQty;
    string borrowDate;
    string dueDate;
    string returnDate;
    string returnStat = "Not Returned Yet";
    Loan loan;
    Patron patron;
    Book book;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        BORROW BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| LoanId     :  "; cin >> id;
    cout << "----------------------------------\n";
    if (loan.checkIdExisted(id)) {
    loan.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    loanManagementUI();
    return;
    };
    cout << "----------------------------------\n";
    cout << "| PatronId   :  "; cin >> patronId;
    if (!patron.checkIdExisted(patronId)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    loanManagementUI();
    return;
    };
    patron.getFromCSVById(patronId);
    cout << "----------------------------------\n";
    cout << "| BookId     :  "; cin >> bookId;
    if (!book.checkIdExisted(bookId)) {
    cout << "----------------------------------\n";
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    loanManagementUI();
    return;
    };
    book.getFromCSVById(bookId);
    cout << "----------------------------------\n";
    cout << "| BorrowQty  :  "; cin >> borrowQty;
    if (book.checkBookQuantity(bookId, borrowQty) == 0) {
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "Notice[!]: Out of Stock \n";
    system("pause");
    loanManagementUI();
    return;
    } 
    if (book.checkBookQuantity(bookId, borrowQty) == 1) {
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "Notice[!]: Not Enough Book \n";
    system("pause");
    loanManagementUI();
    return;
    }
    cout << "----------------------------------\n";
    cout << "| BorrowDate :  "; getline(cin >> ws, borrowDate);
    cout << "| DueDate    :  "; getline(cin >> ws, dueDate);
    cout << "| ReturnDate :  "; getline(cin >> ws, returnDate);
    cout << "| ReturnStat :  " << returnStat << endl;
    cout << "----------------------------------\n";
    cout << "----------------------------------\n";
    cout << "|       ENTER TO CONFIRM  ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Loan loan(id, patronId, bookId, borrowQty, borrowDate, dueDate, returnDate, returnStat);
            loan.insertIntoCSV();
            loan.borrowBook(bookId, borrowQty);
            cout << "Notice[!]: Book Borrowed \n";
            system("pause");
            loanManagementUI();
        }
        else if (toupper(option) == 'N') {
            loanManagementUI();
        }
    }
}
void returnBookUI() {
    int id;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        RETURN BOOK FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| LoanId     :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!loan.checkIdExisted(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    loanManagementUI();
    return;
    }
    if (loan.checkIfReturned(id)) {
    loan.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "Notice[!]: This Loan Was Returned \n";
    system("pause");
    loanManagementUI();
    return;
    }
    loan.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "|       ENTER TO CONFIRM  ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            loan.returnBook(id);
            cout << "Notice[!]: Book Returned \n";
            system("pause");
            loanManagementUI();
        }
        else if (toupper(option) == 'N') {
            loanManagementUI();
        }
    }
}
void deleteLoanUI() {
    int id;
    Loan loan;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|        DELETE LOAN FORM        |\n";
    cout << "----------------------------------\n";
    cout << "| LoanId     :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!loan.checkIdExisted(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        loanManagementUI();
        return;
    }
    if (!loan.checkIfReturned(id)) {
        loan.getFromCSVById(id);
        cout << "----------------------------------\n";
        cout << "Notice[!]: This Loan Has Not Returned Yet \n";
        system("pause");
        loanManagementUI();
        return;
    }
    loan.getFromCSVById(id);
    cout << "----------------------------------\n";
    cout << "|       ENTER TO CONFIRM  ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            loan.removeFromCSV(id);
            cout << "Notice[!]: Loan Deleted \n";
            system("pause");
            loanManagementUI();
        }
        else if (toupper(option) == 'N') {
            loanManagementUI();
        }
    }
}
void loanManagementUI() {
    int option;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|      LOAN MANAGEMENT MENU      |\n";
    cout << "----------------------------------\n";
    cout << "| 1> Get all loans               |\n";
    cout << "| 2> Get loan by ID              |\n";
    cout << "| 3> Get loan by PatronID        |\n";
    cout << "| 4> Get loan by name            |\n";
    cout << "| 5> Get loan by phone number    |\n";
    cout << "| 6> Get loan by email           |\n";
    cout << "| 7> Borrow book                 |\n";
    cout << "| 8> Return book                 |\n";
    cout << "| 9> Delete loan                 |\n";
    cout << "| 10> Back to Main Menu          |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllLoanUI(); break;
    case 2: getLoanByIdUI(); break;
    case 3: getLoanByPatrIdUI(); break;
    case 4: getLoanByPatrNameUI(); break;
    case 5: getLoanByPatrPhoneUI(); break;
    case 6: getLoanByPatrEmailUI(); break;
    case 7: borrowBookUI(); break;
    case 8: returnBookUI(); break;
    case 9: deleteLoanUI(); break;
    case 10: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); patronManagementUI(); };
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
    case 2: categoryManagementUI(); break;
    case 3: authorManagementUI(); break;
    case 4: patronManagementUI(); break;
    case 5: loanManagementUI(); break;
    case 6: logoutUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); mainMenuUI(); };
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

int main()
{
    //username = "phunghoangvnuit";
    //password = "hello_world_123";
    //loginUI(); 
    mainMenuUI(); 
    
    return 0;
}
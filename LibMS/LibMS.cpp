#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string username = "phunghoangvnuit";
string password = "hello_world_123";

void authorManagementUI();
void categoryManagementUI();
void bookManagementUI();
void mainMenuUI();
void loginUI();
void logoutUI();

/*Book*/
class Book {
    private:
        int id;
        string title;
        string isbn;
        string category;
        int quantity;
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
        // Check Book Id If Exsited
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
        }

        // Get Book
        void getBookFromCSV() {
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
                    cout << "----------------------------------\n";
                    cout << "| BookId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title    :  " << vectVal[1] << "\n";
                    cout << "| ISBN     :  " << vectVal[2] << "\n";
                    cout << "| Category :  " << vectVal[3] << "\n";
                    cout << "| Quantity :  " << vectVal[4] << "\n";
                    cout << "| AuthorId :  " << vectVal[5] << "\n";
                    cout << "----------------------------------\n";
                }
                bookCSV.close();
            }
        }
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
void createBookUI() {
    int id;
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
    cout << "Notice[!]: Id Is Already Exsited \n";
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
    cout << "|       CONFIRM TO CREATE ?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Book newBook(id, title, isbn, category, quantity, authorId);
            newBook.insertBookIntoCSV();
            cout << "Notice[!]: Book Created \n";
            system("pause");
            bookManagementUI();
        }
        else if (toupper(option) == 'N') {
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
    book.getBookFromCSV();
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
    if (!book.checkBookIdIfExsited(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getBookFromCSV(id);
    system("pause");
    bookManagementUI();
    return;
};
void updateBookUI() {
    int id;
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
    cout << "Notice[!]: Id Is Not Exsited \n";
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
    cout << "|     YOU WANT TO REPLACED ?     |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            Book altBook(id, title, isbn, category, quantity, authorId);
            altBook.updateBookInCsv(id, altBook);
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
    if (!book.checkBookIdIfExsited(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    bookManagementUI();
    return;
    };
    book.getBookFromCSV(id);
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            book.deleteBookInCsv(id);
            cout << "Notice[!]: Book Deleted \n";
            system("pause");
            bookManagementUI();
        } else if (toupper(option) == 'N') {
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
    cout << "| 3> Get book by Category        |\n";
    cout << "| 4> Get book by Author          |\n";
    cout << "| 5> Create book                 |\n";
    cout << "| 6> Modify book by ID           |\n";
    cout << "| 7> Delete book by ID           |\n";
    cout << "| 8> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllBookUI() ; break;
    case 2: getBookByIdUI(); break;
    case 3: cout << "c3\n" ; break;
    case 4: cout << "c4\n" ; break;
    case 5: createBookUI() ; break;
    case 6: updateBookUI() ; break;
    case 7: deleteBookUI() ; break;
    case 8: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); bookManagementUI(); };
    }
}

/*Category*/
class Category {
private:
    int id;
    string title;

public:
    //getter & setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //getter & setter (name)
    string getTitle() {
        return this->title;
    }
    void setTitle(string name) {
        this->title = title;
    }

    //Book Constructor
    Category() {};

    Category(int id, string title) {
        this->id = id;
        this->title = title;
    }

    /*C.R.U.D - Category.CSV*/
    // Check Category Id If Exsited
    bool checkCategoryIdIfExsited(int id) {
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
                    return true;
                }
            }
            categoryCSV.close();
            return false;
        }
    }

    // Insert Category
    void insertCategoryIntoCSV()
    {
        fstream categoryCSV;
        categoryCSV.open("category.csv", ios::app);

        if (categoryCSV.is_open()) {
            categoryCSV << this->id << ',';
            categoryCSV << this->title << endl;
            categoryCSV.close();
        }
    }

    // Get Category
    void getCategoryFromCSV() {
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
    void getCategoryFromCSV(int id) {
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
                    return;
                }
            }
            categoryCSV.close();
            cout << "Notice[!]: Id Is Not Exsited";
        }
    }

    // Update Category By Id
    void updateCategoryInCsv(int id, Category category) {
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
                            + vectVal[1] + ',';
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

    // Delete Category By Id
    void deleteCategoryInCsv(int id) {
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
    if (category.checkCategoryIdIfExsited(id)) {
    cout << "----------------------------------\n";
    category.getCategoryFromCSV(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    cout << "| Title    :  "; getline(cin >> ws, title);
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
            newCategory.insertCategoryIntoCSV();
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
    category.getCategoryFromCSV();
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
    if (!category.checkCategoryIdIfExsited(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    category.getCategoryFromCSV(id);
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
    if (!category.checkCategoryIdIfExsited(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    categoryManagementUI();
    return;
    };
    category.getCategoryFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| CateId   :  " << id << " (Update Version)\n";
    cout << "| Title    :  "; getline(cin >> ws, title);
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
            altCategory.updateCategoryInCsv(id, altCategory);
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
    if (!category.checkCategoryIdIfExsited(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        categoryManagementUI();
        return;
    };
    category.getCategoryFromCSV(id);
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            category.deleteCategoryInCsv(id);
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
    cout << "| 3> Create category             |\n";
    cout << "| 4> Modify category by ID       |\n";
    cout << "| 5> Delete category by ID       |\n";
    cout << "| 6> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllCategoryUI(); break;
    case 2: getCategoryByIdUI(); break;
    case 3: createCategoryUI(); break;
    case 4: updateCategoryUI(); break;
    case 5: deleteCategoryUI(); break;
    case 6: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); categoryManagementUI(); };
    }
}

/*Author*/
class Author {
private:
    int id;
    string name;

public:
    //getter & setter (id)
    int getId() {
        return this->id;
    }
    void setId(int id) {
        this->id = id;
    }
    //getter & setter (name)
    string getName() {
        return this->name;
    }
    void setName(string name) {
        this->name = name;
    }

    //Author Constructor
    Author() {};

    Author(int id, string name) {
        this->id = id;
        this->name = name;
    }

    /*C.R.U.D - Author.CSV*/
    // Check Author Id If Exsited
    bool checkAuthorIdIfExsited(int id) {
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
                    return true;
                }
            }
            authorCSV.close();
            return false;
        }
    }

    // Insert Author
    void insertAuthorIntoCSV()
    {
        fstream authorCSV;
        authorCSV.open("author.csv", ios::app);

        if (authorCSV.is_open()) {
            authorCSV << this->id << ',';
            authorCSV << this->name << endl;
            authorCSV.close();
        }
    }

    // Get Author
    void getAuthorFromCSV() {
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
                cout << "----------------------------------\n";
            }
            authorCSV.close();
        }
    }
    void getAuthorFromCSV(int id) {
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
                    cout << "----------------------------------\n";
                    return;
                }
            }
            authorCSV.close();
        }
    }

    // Update Author By Id
    void updateAuthorInCsv(int id, Author author) {
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

    // Delete Category By Id
    void deleteAuthorInCsv(int id) {
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
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       CREATE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    if (author.checkAuthorIdIfExsited(id)) {
    cout << "----------------------------------\n";
    author.getAuthorFromCSV(id);
    cout << "Notice[!]: Id Is Already Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    cout << "| Name     :  "; getline(cin >> ws, name);
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
            Author newAuthor(id, name);
            newAuthor.insertAuthorIntoCSV();
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
    author.getAuthorFromCSV();
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
    if (!author.checkAuthorIdIfExsited(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        authorManagementUI();
        return;
    };
    author.getAuthorFromCSV(id);
    system("pause");
    authorManagementUI();
    return;
};
void updateAuthorUI() {
    int id;
    string name;
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       UPDATE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    cout << "----------------------------------\n";
    if (!author.checkAuthorIdIfExsited(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        authorManagementUI();
        return;
    };
    author.getAuthorFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| AuthId   :  " << id << " (Update Version)\n";
    cout << "| Name     :  "; getline(cin >> ws, name);
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
            Author altAuthor(id, name);
            altAuthor.updateAuthorInCsv(id, altAuthor);
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
    if (!author.checkAuthorIdIfExsited(id)) {
    cout << "Notice[!]: Id Is Not Exsited \n";
    system("pause");
    authorManagementUI();
    return;
    };
    author.getAuthorFromCSV(id);
    cout << "----------------------------------\n";
    cout << "|       YOU WANT TO DELETE?      |\n";
    cout << "----------------------------------\n";
    cout << "|      YES      |     Cancel     |\n";
    cout << "----------------------------------\n";
    char option = ' ';
    while (option != 'Y' && option != 'N') {
        cout << "Enter (Y/N): "; cin >> option;
        if (toupper(option) == 'Y') {
            author.deleteAuthorInCsv(id);
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
    cout << "| 3> Create author               |\n";
    cout << "| 4> Modify author by ID         |\n";
    cout << "| 5> Delete author by ID         |\n";
    cout << "| 6> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllAuthorUI(); break;
    case 2: getAuthorByIdUI(); break;
    case 3: createAuthorUI(); break;
    case 4: updateAuthorUI(); break;
    case 5: deleteAuthorUI(); break;
    case 6: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); authorManagementUI(); };
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
    case 4: cout << "patronManagmentUI()"; break;
    case 5: cout << "loanManagmentUI()"; break;
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
    mainMenuUI();
    return 0;
}




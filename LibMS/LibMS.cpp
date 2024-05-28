/*Team Leader: Phung Hoang          */
/*Team Member 1:                    */
/*Team Member 2:                    */     
/*Contact: phunghoangvnuit@gmail.com*/

/*NOTE_1: 100% "NO" ChatGPT / "NO" SOURCE CODE*/
/*NOTE_2: 
    Exception Handling is in developing until the presentation day!
    At the moment, please be Friendly User with my program =(((
*/

/*Check My Commits on GitHub: https://github.com/phunghoangvnuit/LibMS */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string username = "phunghoangvnuit";
string password = "hello_world_123";

void patronManagementUI();
void authorManagementUI();
void categoryManagementUI();
void bookManagementUI();
void mainMenuUI();
void loginUI();
void logoutUI();

/*Library Object Class*/
class LibObj {
    protected:
        int id;
    public:
        //Getter & Setter (id)
        int getId() {
            return this->id;
        }
        void setId(int id) {
            this->id = id;
        }

        //CSV Handling
        bool checkIdExisted() {};
        void insertIntoCSV()  {};
        void updateInCSV()    {};
        void getFromCSV()     {};
        void removeFromCSV()  {};

        //Association
        string getTitleNameByIdFromCSV() {};
};

/*Category Class*/
class Category : public LibObj {
private:
    string title;

public:
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

    //Associatate Category with Book
    string getTitleNameByIdFromCSV(int categoryId) {
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
    };

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
    void getFromCSV(int id) {
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
    category.getFromCSV(id);
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
    category.getFromCSV(id);
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
    category.getFromCSV(id);
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
    };
    category.getFromCSV(id);
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

/*Author Class*/
class Author : public LibObj{
private:
    string name;

public:
    //Getter & Setter (name)
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

    //Associatate Author with Book
    string getTitleNameByIdFromCSV(int authorId) {
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
    };

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
            authorCSV << this->name << endl;
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
                cout << "----------------------------------\n";
            }
            authorCSV.close();
        }
    }
    void getFromCSV(int id) {
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
    Author author;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       CREATE AUTHOR FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    if (author.checkIdExisted(id)) {
    cout << "----------------------------------\n";
    author.getFromCSV(id);
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
    author.getFromCSV(id);
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
    if (!author.checkIdExisted(id)) {
        cout << "Notice[!]: Id Is Not Exsited \n";
        system("pause");
        authorManagementUI();
        return;
    };
    author.getFromCSV(id);
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
    };
    author.getFromCSV(id);
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

/*Patron Class*/
class Patron : public LibObj {
private:
    string name;
    string phoneNumber;
    string email;

public:
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

    //Patron Constructor
    Patron() {};
    Patron(int id, string name, string phoneNumber, string email) {
        this->id = id;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->email = email;
    }

    /*C.R.U.D - Author.CSV*/
    // Check PatronId If Existed
    bool checkIdExisted(int id) {
        fstream authorCSV;
        authorCSV.open("patron.csv", ios::in);

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

    // Insert Patron Into CSV
    void insertIntoCSV()
    {
        fstream authorCSV;
        authorCSV.open("patron.csv", ios::app);

        if (authorCSV.is_open()) {
            authorCSV << this->id << ',';
            authorCSV << this->name << ',';
            authorCSV << this->phoneNumber << ',';
            authorCSV << this->email << endl;
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
                    string altLine;
                    altLine = vectVal[0] + ','
                            + vectVal[1] + ','
                            + vectVal[2] + ','
                            + vectVal[3];
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
                cout << "----------------------------------\n";
            }
            patronCSV.close();
        }
    }
    void getFromCSV(int id) {
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
                    cout << "| AuthId   :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Name     :  " << vectVal[1] << "\n";
                    cout << "| Phone    :  " << vectVal[2] << "\n";
                    cout << "| Email    :  " << vectVal[3] << "\n";
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
    Patron patron;

    system("cls");
    cout << "----------------------------------\n";
    cout << "|       CREATE PATRON FORM       |\n";
    cout << "----------------------------------\n";
    cout << "| AuthId   :  "; cin >> id;
    if (patron.checkIdExisted(id)) {
        cout << "----------------------------------\n";
        patron.getFromCSV(id);
        cout << "Notice[!]: Id Is Already Exsited \n";
        system("pause");
        patronManagementUI();
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
            Patron patron(id, name, phoneNumber, email);
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
    patron.getFromCSV(id);
    system("pause");
    patronManagementUI();
    return;
};
void updatePatronUI() {
    int id;
    string name;
    string phoneNumber;
    string email;
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
    patron.getFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| PatrId   :  " << id << " (Update Version)\n";
    cout << "| Name     :  "; getline(cin >> ws, name);
    cout << "| Phone    :  "; getline(cin >> ws, name);
    cout << "| Email    :  "; getline(cin >> ws, name);
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
            Patron altPatron(id, name, phoneNumber, email);
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
    patron.getFromCSV(id);
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
    cout << "| 3> Create patron               |\n";
    cout << "| 4> Modify patron by ID         |\n";
    cout << "| 5> Delete patron by ID         |\n";
    cout << "| 6> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllPatronUI(); break;
    case 2: getPatronByIdUI(); break;
    case 3: createPatronUI(); break;
    case 4: updatePatronUI(); break;
    case 5: deletePatronUI(); break;
    case 6: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); patronManagementUI(); };
    }
}

/*Book Class*/
class Book : private LibObj {
private:
    string title;
    string isbn;
    int quantity;
    int categoryId;
    int authorId;
    Category categoryObj;
    Author authorObj;

public:
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

    //Associatate Book with Category/Author
    string getCategoryById(int categoryId) {
        return categoryObj.getTitleNameByIdFromCSV(categoryId);
    }
    string getAuthorById(int authorId) {
        return authorObj.getTitleNameByIdFromCSV(authorId);
    }

    /*C.R.U.D - Book.CSV*/
    // Check BookId If Existed
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
                    vectVal[4] = book.getCategoryId();
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
                Book book;
                // Use Association To Get Value From Other CSV (Reference Like SQL Database PK_FK)
                vectVal[4] = book.getCategoryById(stoi(vectVal[4]));
                vectVal[5] = book.getAuthorById(stoi(vectVal[5]));
                cout << "----------------------------------\n";
                cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                cout << "| Title      :  " << vectVal[1] << "\n";
                cout << "| ISBN       :  " << vectVal[2] << "\n";
                cout << "| Quantity   :  " << vectVal[3] << "\n";
                cout << "| Category   :  " << vectVal[4] << "\n";
                cout << "| Author     :  " << vectVal[5] << "\n";
                cout << "----------------------------------\n";
            }
            bookCSV.close();
        }
    }
    void getFromCSV(int id) {
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
                    Book book;
                    // Use Association To Get Value From Other CSV (Reference Like SQL Database PK_FK)
                    vectVal[4] = book.getCategoryById(stoi(vectVal[4]));
                    vectVal[5] = book.getAuthorById(stoi(vectVal[5]));
                    cout << "----------------------------------\n";
                    cout << "| BookId     :  " << vectVal[0] << " (Current Version)\n";
                    cout << "| Title      :  " << vectVal[1] << "\n";
                    cout << "| ISBN       :  " << vectVal[2] << "\n";
                    cout << "| Quantity   :  " << vectVal[3] << "\n";
                    cout << "| Category   :  " << vectVal[4] << "\n";
                    cout << "| Author     :  " << vectVal[5] << "\n";
                    cout << "----------------------------------\n";
                    return;
                }
            }
            bookCSV.close();
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
        book.getFromCSV(id);
        cout << "Notice[!]: Id Is Already Exsited \n";
        system("pause");
        bookManagementUI();
        return;
    };
    cout << "| Title      :  "; getline(cin >> ws, title);
    cout << "| ISBN       :  "; getline(cin >> ws, isbn);
    cout << "| Quantity   :  "; cin >> quantity;
    cout << "| CategoryId :  "; cin >> categoryId;
    cout << "| Category   :  " << book.getCategoryById(categoryId) << endl;
    cout << "| AuthorId   :  "; cin >> authorId;
    cout << "| Category   :  " << book.getAuthorById(authorId) << endl;
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
            Book newBook(id, title, isbn, quantity, categoryId, authorId);
            newBook.insertIntoCSV();
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
    book.getFromCSV(id);
    system("pause");
    bookManagementUI();
    return;
};
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
    book.getFromCSV(id);
    cout << "----------------------------------\n";
    cout << "| BookId     : " << id << " (Update Version)\n";
    cout << "| Title      : "; getline(cin >> ws, title);
    cout << "| ISBN       : "; getline(cin >> ws, isbn);
    cout << "| Quantity   : "; cin >> quantity;
    cout << "| CategoryId :  "; cin >> categoryId;
    cout << "| Category   :  " << book.getCategoryById(categoryId) << endl;
    cout << "| AuthorId   :  "; cin >> authorId;
    cout << "| Category   :  " << book.getAuthorById(authorId) << endl;
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
    };
    book.getFromCSV(id);
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
    cout << "| 3> Get book by Category        |\n";
    cout << "| 4> Get book by Author          |\n";
    cout << "| 5> Create book                 |\n";
    cout << "| 6> Modify book by ID           |\n";
    cout << "| 7> Delete book by ID           |\n";
    cout << "| 8> Back to Main Menu           |\n";
    cout << "----------------------------------\n";
    cout << "Please choose an option: "; cin >> option;
    switch (option) {
    case 1: getAllBookUI(); break;
    case 2: getBookByIdUI(); break;
    case 3: cout << "c3\n"; break;
    case 4: cout << "c4\n"; break;
    case 5: createBookUI(); break;
    case 6: updateBookUI(); break;
    case 7: deleteBookUI(); break;
    case 8: system("cls"); mainMenuUI(); break;
    default: { cout << "Invalid input\n"; system("pause"); system("cls"); bookManagementUI(); };
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




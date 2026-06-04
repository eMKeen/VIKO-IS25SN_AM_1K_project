//User Menu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
using namespace std;

int menuSelect(int _select, int _kiekis, int _notNULL);
void commonLine(int _lineLenght, string _text, int _select, int _menuSelect);
string toLower(string text);
void wait();
void addBook();
// void viewBook();
// void editBook();
// void deleteBook();
// void outBook();
// void inBook();

struct bookData {
    string title;
    vector<string> authors;
    int year;
    int quantity;
    vector<string> students;

    bool getBookData(ifstream& _inFile) {
        string _authors;
        string _students;
        string _year;
        string _quantity;

        if (!getline(_inFile, title, ';'))
            return false;

        getline(_inFile, _authors, ';');
        getline(_inFile, _year, ';');
        getline(_inFile, _quantity, ';');
        getline(_inFile, _students);

        year = stoi(_year);
        quantity = stoi(_quantity);

        return true;
    }
};

int userMenu() {
    int _select = 0;

    do {
        cout << "=====================================" << endl;
        cout << "          Bibliotekos sistema" << endl;
        cout << "=====================================" << endl;
        cout << "1 - Pridėti naują knygą" << endl;
        cout << "2 - Peržiūrėti knygas" << endl;
        cout << "3 - Redaguoti knygą" << endl;
        cout << "4 - Pašalinti knygą" << endl;
        cout << "5 - Išduoti knygą studentui" << endl;
        cout << "6 - Grąžinti knygą" << endl;
        cout << "0 - Atsijungti" << endl;
        cout << "=====================================" << endl;

        _select = menuSelect(_select, 6, 0);

        switch (_select) {
            case 1:
                addBook();
                break;
            // case 2:
            //     viewBook();
            //     break;
            // case 3:
            //     editBook();
            //     break;
            // case 4:
            //     deleteBook();
            //     break;
            // case 5:
            //     outBook();
            //     break;
            // case 6:
            //     inBook();
            //     break;
            default: break;
        }
    } while (_select != 0);

    return 0;
}

void addBook() {
    bookData book;

    cin.ignore();
    commonLine(45,"",0,0);
    commonLine(45,"Naujos knygos registravimas",2,0);
    commonLine(45,"",0,0);

    commonLine(45,"Iveskite knygos pavadinima:",4,0);
    getline(cin, book.title);
    commonLine(45,"Iveskite leidimo metus:",4,0);
    cin >> book.year;
    commonLine(45,"Iveskite egzemplioriu kieki:",4,0);
    cin >> book.quantity;

    commonLine(45,"Kiek autorių?",4,0);
    int _quantity = 0;
    cin >> _quantity;
    cin.ignore();

    for (int i = 0; i < _quantity; i++) {
        string _author;
        commonLine(45,"Įveskite autorių",3,i + 1);
        getline(cin, _author);
        book.authors.push_back(_author);
    }
    ofstream outFile("../DB/bookDataBase", ios::app);
    outFile << book.title << ";";

    for (int i = 0; i < book.authors.size(); i++) {
        outFile << book.authors[i];
        if (i != book.authors.size() - 1) {
            outFile << "|";
        }
    }
    outFile << ";" << book.year << ";" << book.quantity << ";" << endl;
}

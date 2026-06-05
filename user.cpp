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
int myliuLietuvybe(const string& txt);
void wait();
void addBook();
void viewBook();
void editBook();
void deleteBook();
void outBook();
void returnBook();
void viewAllBooks();
string allAuthors(const vector<string>& _authors);
void viewBooksByCriteria();
bool studentHasBook(const vector<string>& _students, const string& _student);
void reportMenu();
void reportAllBooks();
void reportOutBooks();
void reportUnavailableBooks();
void emptyErrorMessage();
vector<string> splitText(const string& _text, char _spliter);

struct bookData {
    string title;
    vector<string> authors;
    int year = 0;
    int quantity = 0;
    vector<string> students;

    bool getBookData(ifstream& _inFile) {
        string _authors;
        string _students;
        string _year;
        string _quantity;

        authors.clear();
        students.clear();

        if (!getline(_inFile, title, ';'))
            return false;

        getline(_inFile, _authors, ';');
        getline(_inFile, _year, ';');
        getline(_inFile, _quantity, ';');
        getline(_inFile, _students);

        authors = splitText(_authors, '|');
        students = splitText(_students, '|');

        year = stoi(_year);
        quantity = stoi(_quantity);

        return true;
    }
};

void printBooksToFile(const vector<bookData>& _books);
void showBookList(const vector<bookData>& _books);
vector<bookData> loadBooks();

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
            case 2:
                viewBook();
                break;
            case 3:
                editBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                outBook();
                break;
            case 6:
                returnBook();
                break;
            default: break;
        }
    } while (_select != 0);
    return 0;
}

void addBook() {
    bookData _book;

    cin.ignore();
    commonLine(45,"",0,0);
    commonLine(45,"Naujos knygos registravimas",2,0);
    commonLine(45,"",0,0);

    commonLine(45,"Iveskite knygos pavadinima:",4,0);
    getline(cin, _book.title);
    commonLine(45,"Iveskite leidimo metus:",4,0);
    cin >> _book.year;
    commonLine(45,"Iveskite egzemplioriu kieki:",4,0);
    cin >> _book.quantity;

    commonLine(45,"Kiek autorių?",4,0);
    int _quantity = 0;
    cin >> _quantity;
    cin.ignore();

    for (int i = 0; i < _quantity; i++) {
        string _author;
        commonLine(45,"Įveskite autorių",3,i + 1);
        getline(cin, _author);
        _book.authors.push_back(_author);
    }
    ofstream _outFile("../DB/bookDataBase", ios::app);
    _outFile << _book.title << ";";

    for (int i = 0; i < _book.authors.size(); i++) {
        _outFile << _book.authors[i];
        if (i != _book.authors.size() - 1) {
            _outFile << "|";
        }
    }
    _outFile << ";" << _book.year << ";" << _book.quantity << ";" << endl;

    commonLine(45,"",0,0);
    commonLine(45,"Knyga sėkmingai pridėta",2,0);
    commonLine(45,"",0,0);
    wait();
}

void viewBook() {
    int _select = 0;
    while (true) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Knygų peržiūra", 2, 0);
        commonLine(45, "", 0, 0);
        commonLine(45, "Peržiūrėti visas knygas", 3, 1);
        commonLine(45, "Peržiūrėti pagal kriterijus", 3, 2);
        commonLine(45, "Formuoti ataskaitą", 3, 3);
        commonLine(45, "Grįžti", 3, 0);
        commonLine(45, "", 0, 0);

        _select = menuSelect(_select, 3, 0);
        switch (_select) {
            case 1:
                viewAllBooks();
                break;
            case 2:
                viewBooksByCriteria();
                break;
            case 3:
                reportMenu();
                break;
            default:
                return;
        }
    }
}

string allAuthors(const vector<string>& _authors) {
    string _result;
    for (int i = 0; i < _authors.size(); i++) {
        _result += _authors[i];
        if (i != _authors.size() - 1) {
            _result += ", ";
        }
    }
    return _result;
}

vector<string> splitText(const string& _text, char _spliter) {
    vector<string> _result;
    string _temp;

    for (char c : _text) {
        if (c == _spliter) {
            if (!_temp.empty()) {
                _result.push_back(_temp);
                _temp.clear();
            }
        } else {
            _temp += c;
        }
    }
    if (!_temp.empty()) {
        _result.push_back(_temp);
    }
    return _result;
}

void viewAllBooks() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }

    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }

    showBookList(_books);
}

bool containsText(const string& _text, const string& _search) {
    string _lookUpText = toLower(_text);
    string _lookUpSearch = toLower(_search);
    return _lookUpText.find(_lookUpSearch) != string::npos;
}

bool authorMatches(const vector<string>& _authors, const string& _searchAuthor) {
    for (string _author : _authors) {
        if (containsText(_author, _searchAuthor)) {
            return true;
        }
    }
    return false;
}

void printBooksToFile(const vector<bookData>& _books) {
    ofstream _outFile("../DB/Print/Print.txt");

    if (!_outFile) {
        cout << "Nepavyko sukurti failo!" << endl;
        return;
    }
    for (int i = 0; i < _books.size(); i++) {
        int _available = _books[i].quantity - _books[i].students.size();

        _outFile << "Nr.: " << i + 1 << endl;
        _outFile << "Knygos pavadinimas: " << _books[i].title << endl;
        _outFile << "Autorius(-iai): " << allAuthors(_books[i].authors) << endl;
        _outFile << "Laidos metai: " << _books[i].year << endl;
        _outFile << "Esamas kiekis: " << _available << " / " << _books[i].quantity << endl;
        _outFile << "---------------------------------------------" << endl;
    }

    commonLine(45, "", 0, 0);
    commonLine(45, "Ataskaita isšaugota", 2, 0);
    commonLine(45, "Print.txt", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void showBookList(const vector<bookData>& _books) {
    commonLine(90, "", 0, 0);
    int _lineCorrection = 0;
    for (int i = 0; i < _books.size(); i++) {

        _lineCorrection = myliuLietuvybe(_books[i].title) - _books[i].title.length();

        int _available = _books[i].quantity - _books[i].students.size();
        cout << format(
                    "{:<5}{:<3} | {:<{}} | {:<4} | {:>3} / {:<3} \n {:<8}| {}",
                    "Nr.:", i + 1,
                    _books[i].title,
                    50 - _lineCorrection,
                    _books[i].year,
                    _available,
                    _books[i].quantity,
                    "",
                    allAuthors(_books[i].authors)
                ) << endl;
        commonLine(90, "", 0, 0);
    }
    wait();
}

void viewBooksByCriteria() {
    vector<bookData> _books;
    vector<bookData> _results;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }

    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }
    int _criteriaCount = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pagal kiek kriteriju ieskoti?", 2, 0);
    commonLine(45, "Min 1, max 3", 2, 0);
    commonLine(45, "", 0, 0);

    _criteriaCount = menuSelect(_criteriaCount, 3, 1);
    bool _useAuthor = false;
    bool _useTitle = false;
    bool _useYear = false;

    string _searchAuthor;
    string _searchTitle;
    int _searchYear = 0;
    for (int i = 0; i < _criteriaCount; i++) {
        int _select = 0;
        commonLine(45, "", 0, 0);
        commonLine(45, "Pasirinkite kriterijus", 2, 0);
        if (!_useAuthor)
            commonLine(45, "Autorius", 3, 1);
        if (!_useTitle)
            commonLine(45, "Pavadinimas", 3, 2);
        if (!_useYear)
            commonLine(45, "Metai", 3, 3);
        commonLine(45, "", 0, 0);

        while (true) {
            _select = menuSelect(_select, 3, 1);
            if (_select == 1 && !_useAuthor) {
                _useAuthor = true;
                cin.ignore();
                commonLine(45, "Iveskite autorių:", 4, 0);
                getline(cin, _searchAuthor);
                break;
            }
            if (_select == 2 && !_useTitle) {
                _useTitle = true;
                cin.ignore();
                commonLine(45, "Iveskite pavadinimą:", 4, 0);
                getline(cin, _searchTitle);
                break;
            }
            if (_select == 3 && !_useYear) {
                _useYear = true;
                commonLine(45, "Iveskite metus:", 4, 0);
                cin >> _searchYear;
                break;
            }
            commonLine(45, "Kriterijus jau pasirinktas", 2, 0);
        }
    }

    int _onlyAvailable = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Kur ieškoti?", 2, 0);
    commonLine(45, "Tarp visu knygų", 3, 1);
    commonLine(45, "Tik tarp prieinamų", 3, 2);
    commonLine(45, "", 0, 0);

    _onlyAvailable = menuSelect(_onlyAvailable, 2, 1);
    for (const bookData& book : _books) {
        bool match = true;
        int _available = book.quantity - book.students.size();

        if (_onlyAvailable == 2 && _available <= 0) {
            match = false;
        }
        if (_useAuthor && !authorMatches(book.authors, _searchAuthor)) {
            match = false;
        }
        if (_useTitle && !containsText(book.title, _searchTitle)) {
            match = false;
        }
        if (_useYear && book.year != _searchYear) {
            match = false;
        }
        if (match) {
            _results.push_back(book);
        }
    }

    if (_results.empty()) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Rzultatų nerasta", 2, 0);
        commonLine(45, "Spauskite ENTER", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }

    showBookList(_results);

    int _printSelect = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Ar norite spausdinti rezultatus?", 2, 0);
    commonLine(45, "Taip", 3, 1);
    commonLine(45, "Ne", 3, 0);
    commonLine(45, "", 0, 0);

    _printSelect = menuSelect(_printSelect, 1, 0);
    if (_printSelect == 1) {
        printBooksToFile(_results);
    }
}

bool studentHasBook(const vector<string>& _students, const string& _student) {
    string _lookUp = toLower(_student);

    for (string student : _students) {
        student = toLower(student);
        if (student == _lookUp) {
            return true;
        }
    }

    return false;
}

void outBook() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }

    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }
    showBookList(_books);

    int _select = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pasirinkite išduodamos knygos numerį", 1, 0);
    commonLine(45, "", 0, 0);

    _select = menuSelect(_select, _books.size(), 1);
    int _index = _select - 1;
    int _available = _books[_index].quantity - _books[_index].students.size();
    if (_available <= 0) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Laisvų egzempliorių nėra", 2, 0);
        commonLine(45, "Spauskite ENTER", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }

    string _student;
    cin.ignore();
    commonLine(45, "Iveskite studento pavardę:", 4, 0);
    getline(cin, _student);
    _student = toLower(_student);

    if (studentHasBook(_books[_index].students, _student)) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Studentas jau turi šią knygą", 2, 0);
        commonLine(45, "Spauskite ENTER", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }
    _books[_index].students.push_back(_student);

    ofstream _outFile("../DB/bookDataBase");

    if (!_outFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    for (const bookData& book : _books) {
        _outFile << book.title << ";";
        for (int i = 0; i < book.authors.size(); i++) {
            _outFile << book.authors[i];
            if (i != book.authors.size() - 1) {
                _outFile << "|";
            }
        }
        _outFile << ";" << book.year << ";" << book.quantity << ";";
        for (int i = 0; i < book.students.size(); i++) {
            _outFile << book.students[i];
            if (i != book.students.size() - 1) {
                _outFile << "|";
            }
        }
        _outFile << endl;
    }

    commonLine(45, "", 0, 0);
    commonLine(45, "Knyga sekmingai išduota", 2, 0);
    commonLine(45, "Spauskite ENTER", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void returnBook() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }

    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }
    showBookList(_books);

    int _select = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pasirinkite grąžinamos knygos numerį", 1, 0);
    commonLine(45, "", 0, 0);

    _select = menuSelect(_select, _books.size(), 1);
    int _index = _select - 1;
    if (_books[_index].students.empty()) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Ši knygą nėra išduota", 2, 0);
        commonLine(45, "Spauskite ENTER", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }

    string _student;
    cin.ignore();
    commonLine(45, "Iveskite studento pavardę:", 4, 0);
    getline(cin, _student);
    _student = toLower(_student);

    bool _found = false;
    for (int i = 0; i < _books[_index].students.size(); i++) {
        string _currentStudent = _books[_index].students[i];
        toLower(_currentStudent);
        if (_currentStudent == _student) {
            _books[_index].students.erase(_books[_index].students.begin() + i);
            _found = true;
            break;
        }
    }

    if (!_found) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Studentas prie šios knygos nerastas", 2, 0);
        commonLine(45, "Spauskite ENTER", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }

    ofstream _outFile("../DB/bookDataBase");

    if (!_outFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    for (const bookData& book : _books) {
        _outFile << book.title << ";";
        for (int i = 0; i < book.authors.size(); i++) {
            _outFile << book.authors[i];
            if (i != book.authors.size() - 1)
                _outFile << "|";
        }
        _outFile << ";" << book.year << ";" << book.quantity << ";";
        for (int i = 0; i < book.students.size(); i++) {
            _outFile << book.students[i];
            if (i != book.students.size() - 1)
                _outFile << "|";
        }
        _outFile << endl;
    }

    commonLine(45, "", 0, 0);
    commonLine(45, "Knyga sekmingai grąžinta", 2, 0);
    commonLine(45, "Spauskite ENTER", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void editBook() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");
    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }

    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }
    showBookList(_books);

    int _select = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pasirinkite redaguojamos knygos nr.", 1, 0);
    commonLine(45, "", 0, 0);

    _select = menuSelect(_select, _books.size(), 1);
    int _index = _select - 1;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pasirinkite redagavimą", 2, 0);
    commonLine(45, "Knygos pavadinimas", 3, 1);
    commonLine(45, "Autorius(-iai)", 3, 2);
    commonLine(45, "Leidimo metai", 3, 3);
    commonLine(45, "Egzempliorių kiekis", 3, 4);
    commonLine(45, "Atšaukti", 3, 0);
    commonLine(45, "", 0, 0);

    _select = menuSelect(_select, 4, 0);
    switch (_select) {
        case 1: {
            cin.ignore();
            commonLine(45, "Įveskite naują pavadinimą:", 4, 0);
            getline(cin, _books[_index].title);
            break;
        }
        case 2: {
            _books[_index].authors.clear();

            int _count = 0;
            commonLine(45, "Kiek autorių?", 4, 0);
            _count = menuSelect(_count, 10, 1);

            cin.ignore();
            for (int i = 0; i < _count; i++) {
                string _author;
                commonLine(45, "Iveskite autoriu", 3, i + 1);
                getline(cin, _author);
                _books[_index].authors.push_back(_author);
            }
            break;
        }
        case 3: {
            commonLine(45, "Iveskite naujus leidimo metus:", 4, 0);
            cin >> _books[_index].year;
            break;
        }

        case 4: {
            commonLine(45, "Iveskite naują egzempliorių kiekį:", 4, 0);
            cin >> _books[_index].quantity;

            if (_books[_index].quantity < _books[_index].students.size()) {
                commonLine(45, "", 0, 0);
                commonLine(45, "Kiekis mažesnis nei išduota", 2, 0);
                commonLine(45, "Pakeitimas negalimas", 2, 0);
                commonLine(45, "", 0, 0);
                wait();
                return;
            }
            break;
        }
        default:
            return;
    }

    ofstream _outFile("../DB/bookDataBase");

    if (!_outFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    for (const bookData& book : _books) {
        _outFile << book.title << ";";
        for (int i = 0; i < book.authors.size(); i++) {
            _outFile << book.authors[i];
            if (i != book.authors.size() - 1)
                _outFile << "|";
        }

        _outFile << ";" << book.year << ";" << book.quantity << ";";

        for (int i = 0; i < book.students.size(); i++) {
            _outFile << book.students[i];
            if (i != book.students.size() - 1)
                _outFile << "|";
        }
        _outFile << endl;
    }

    commonLine(45, "", 0, 0);
    commonLine(45, "Knyga sekmingai atnaujinta", 2, 0);
    commonLine(45, "Spauskite ENTER", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void deleteBook() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }
    _inFile.close();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }
    showBookList(_books);

    int _select = 0;
    commonLine(45, "", 0, 0);
    commonLine(45, "Pasirinkite šalinamos knygos nr.", 1, 0);
    commonLine(45, "", 0, 0);

    _select = menuSelect(_select, _books.size(), 1);
    int _index = _select - 1;
    if (!_books[_index].students.empty()) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Knyga yra išduota studentams", 2, 0);
        commonLine(45, "Pirmiausia grąžinkite knygą", 2, 0);
        commonLine(45, "", 0, 0);
        wait();
        return;
    }
    _books.erase(_books.begin() + _index);

    ofstream _outFile("../DB/bookDataBase");

    if (!_outFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    for (const bookData& book : _books) {
        _outFile << book.title << ";";
        for (int i = 0; i < book.authors.size(); i++) {
            _outFile << book.authors[i];
            if (i != book.authors.size() - 1)
                _outFile << "|";
        }

        _outFile << ";" << book.year << ";" << book.quantity << ";";

        for (int i = 0; i < book.students.size(); i++) {
            _outFile << book.students[i];
            if (i != book.students.size() - 1)
                _outFile << "|";
        }
        _outFile << endl;
    }

    commonLine(45, "", 0, 0);
    commonLine(45, "Knyga sekmingai pašalinta", 2, 0);
    commonLine(45, "Spauskite ENTER", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void reportMenu() {
    int _select = 0;

    while (true) {
        commonLine(45, "", 0, 0);
        commonLine(45, "Ataskaitų formavimas", 2, 0);
        commonLine(45, "", 0, 0);
        commonLine(45, "Visų knygų ataskaitą", 3, 1);
        commonLine(45, "Išduotų knygų ataskaitą", 3, 2);
        commonLine(45, "Neprieinamų knygų ataskaita", 3, 3);
        commonLine(45, "Grižti", 3, 0);
        commonLine(45, "", 0, 0);

        _select = menuSelect(_select, 3, 0);
        switch (_select) {
            case 1:
                reportAllBooks();
                break;
            case 2:
                reportOutBooks();
                break;
            case 3:
                reportUnavailableBooks();
                break;
            default:
                return;
        }
    }
}

vector<bookData> loadBooks() {
    vector<bookData> _books;
    bookData _book;

    ifstream _inFile("../DB/bookDataBase");

    if (!_inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return _books;
    }
    while (_book.getBookData(_inFile)) {
        _books.push_back(_book);
    }
    return _books;
}

void reportAllBooks() {
    vector<bookData> _books = loadBooks();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }

    ofstream _outFile("../DB/Print/Print_all_books.txt");

    int _totalQuantity = 0;
    int _totalOut = 0;

    _outFile << "VISŲ KNYGŲ ATASKAITA\n";
    _outFile << "---------------------------------------------\n";

    for (const bookData& book : _books) {
        int _out = book.students.size();
        int available = book.quantity - _out;
        _totalQuantity += book.quantity;
        _totalOut += _out;
        _outFile << "Knygos pavadinimas: " << book.title << endl;
        _outFile << "Autorius(-iai): " << allAuthors(book.authors) << endl;
        _outFile << "Laidos metai: " << book.year << endl;
        _outFile << "Esamas kiekis: " << available << " / " << book.quantity << endl;
        _outFile << "---------------------------------------------\n";
    }

    _outFile << "\nBENDRA SUVESTINĖ\n";
    _outFile << "Knygų pavadinimų: " << _books.size() << endl;
    _outFile << "Viso egzempliorių: " << _totalQuantity << endl;
    _outFile << "Išduota: " << _totalOut << endl;
    _outFile << "Prieinama: " << _totalQuantity - _totalOut << endl;

    commonLine(45, "", 0, 0);
    commonLine(45, "Ataskaita suformuota", 2, 0);
    commonLine(45, "Print_all_books.txt", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void reportOutBooks() {
    vector<bookData> _books = loadBooks();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }

    ofstream _outFile("../DB/Print/Print_issued_books.txt");

    _outFile << "IŠDUOTŲ KNYGŲ ATASKAITA\n";
    _outFile << "---------------------------------------------\n";

    int _totalOut = 0;
    for (const bookData& book : _books) {
        if (!book.students.empty()) {
            _outFile << "Knygos pavadinimas: " << book.title << endl;
            _outFile << "Autorius(-iai): " << allAuthors(book.authors) << endl;
            _outFile << "Isduota: " << book.students.size() << endl;
            _outFile << "Studentai:\n";
            for (const string& student : book.students) {
                _outFile << "- " << student << endl;
            }
            _outFile << "---------------------------------------------\n";
            _totalOut += book.students.size();
        }
    }

    _outFile << "\nBENDRAI IŠDUOTA: " << _totalOut << endl;

    commonLine(45, "", 0, 0);
    commonLine(45, "Ataskaita suformuota", 2, 0);
    commonLine(45, "Print_issued_books.txt", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void reportUnavailableBooks() {
    vector<bookData> _books = loadBooks();

    if (_books.empty()) {
        emptyErrorMessage();
        return;
    }

    ofstream _outFile("../DB/Print/Print_unavailable_books.txt");

    _outFile << "NEPRIEINAMŲ KNYGŲ ATASKAITA\n";
    _outFile << "---------------------------------------------\n";

    int _count = 0;
    for (const bookData& book : _books) {
        int available = book.quantity - book.students.size();
        if (available <= 0) {
            _outFile << "Knygos pavadinimas: " << book.title << endl;
            _outFile << "Autorius(-iai): " << allAuthors(book.authors) << endl;
            _outFile << "Laidos metai: " << book.year << endl;
            _outFile << "Kiekis: 0 / " << book.quantity << endl;
            _outFile << "---------------------------------------------\n";
            _count++;
        }
    }
    _outFile << "\nNeprieinamu knygu pavadinimu: " << _count << endl;
    commonLine(45, "", 0, 0);
    commonLine(45, "Ataskaita suformuota", 2, 0);
    commonLine(45, "Print_unavailable_books.txt", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}

void emptyErrorMessage() {
    commonLine(45, "", 0, 0);
    commonLine(45, "Knygų sąrašas tuščias", 2, 0);
    commonLine(45, "Spauskite ENTER", 2, 0);
    commonLine(45, "", 0, 0);
    wait();
}
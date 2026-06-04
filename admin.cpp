//Admin Menu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
using namespace std;

int menuSelect(int _select, int _kiekis, int _notNULL);
void viewRecords();
void addRecord();
void editRecord();
void deleteRecord();
void wait();
void commonLine(int _lineLenght, string _text, int _select, int _menuSelect);
string toLower(string text);
bool userExists(string username);

struct userData {
    string username;
    string password;
    char role;

    bool getData(ifstream &_inFile) {
        if (!getline(_inFile, username, ';'))
            return false;

        getline(_inFile, password, ';');
        _inFile >> role;
        _inFile.ignore();

        return true;
    }
};

int adminMenu() {
    int _select = 0;

    do {
        cout << "=====================================" << endl;
        cout << "      ADMINISTRATORIAUS MENIU" << endl;
        cout << "=====================================" << endl;
        cout << "1 - Peržiuręti įrašus" << endl;
        cout << "2 - Pridėti irašą" << endl;
        cout << "3 - Redaguoti įrašą" << endl;
        cout << "4 - Pašalinti įrašą" << endl;
        cout << "0 - Atsijungti" << endl;
        cout << "=====================================" << endl;

        _select = menuSelect(_select, 4, 0);

        switch (_select) {
            case 1:
                viewRecords();
                break;
            case 2:
                addRecord();
                break;
            case 3:
                editRecord();
                break;
            case 4:
                deleteRecord();
                break;
        }

    } while (_select != 0);

    return 0;
}

void viewRecords() {
    ifstream inFile("../DB/ACC/ACC");

    if (!inFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    userData _user;

    commonLine(45,"",0,0);
    cout << format("{:<4} {:<10}{:<10}{:>15}","Nr.","Vardas","Slaptažodis","Role") << endl;
    commonLine(45,"",0,0);
    string _role;
    int _line = 0;
    while (_user.getData(inFile)) {
        _line++;
        if (_user.role == 'a') {
            _role = "Administratorius";
        } else if (_user.role == 'u') {
            _role = "Naudotojas";
        } else {
            _role = "Klaida!";
        }
        cout << format("{:<2} - {:<10}{:<10}{:>20}",_line,_user.username,_user.password,_role) << endl;
    }
    cout << format("{:-<45}", "") << endl;
    wait();
}


void addRecord() {
    ofstream outFile("../DB/ACC/ACC", ios::app);
    int _select = 0;
    if (!outFile) {
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }

    userData _user;
    while (true) {
        commonLine(45,"",0,0);
        commonLine(45,"Įveskite naudotojo varda:",4,0);
        cin >> _user.username;

        _user.username = toLower(_user.username);
        if (!userExists(_user.username)) {
            break;
        }

        commonLine(45,"",0,0);
        commonLine(45,"Toks naudotojas jau egzistoja",2,0);
        commonLine(45,"Spauskite ENTER",2,0);
        commonLine(45,"",0,0);
        wait();
    }
    commonLine(45,"Įveskite slaptažodį:",4,0);
    cin >> _user.password;

    commonLine(45,"",0,0);
    commonLine(45,"Pasirinkite naudotojo rolę",2,0);
    commonLine(45,"Admnistratorius",3,1);
    commonLine(45,"Naudotojas",3,2);
     _select = menuSelect(_select, 2, 1);

    if (_select == 1) {
        _user.role = 'a';
        commonLine(45,"",0,0);
        commonLine(45,"Kurti Administratoriu?",1,0); //Double Check
        commonLine(45,"Y/N",1,0);
        string _yN;
        cin >> _yN;
        if (_yN == "n") {
            _user.role = 'u';
        }
    } else {
        _user.role = 'u';
    }

    outFile << _user.username << ";" << _user.password << ";" << _user.role <<endl;
    commonLine(45,"",0,0);
    commonLine(45,"Paskyra sekmingai prideta",2,0);
    commonLine(45,"Spauskite ENTER",2,0);
    commonLine(45,"",0,0);
    wait();
};
void editRecord() {};
void deleteRecord() {};

bool userExists(string _username)
{
    toLower(_username);

    ifstream inFile("../DB/ACC/ACC");

    if (!inFile)
        return false;

    userData _user;

    while (_user.getData(inFile)) {
        string _currentUser = _user.username;
        toLower(_currentUser);

        if (_currentUser == _username)
            return true;
    }

    return false;
}
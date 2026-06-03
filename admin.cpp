//Admin Menu
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <format>
using namespace std;

int menuSelect(int _select, int _kiekis, int _notNULL);
int longestText(string _tekstoMasyvas[],int n);
void viewRecords();
void addRecord();
void editRecord();
void deleteRecord();
void wait();

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

    cout << format("{:-<45}", "") << endl;
    cout << format("{:<4} {:<10}{:<10}{:>15}","Nr.","Vardas","Slaptažodis","Role") << endl;
    cout << format("{:-<45}", "") << endl;
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

void addRecord() {};
void editRecord() {};
void deleteRecord() {};
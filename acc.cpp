//User login
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int menuSelect(int _select, int _kiekis, int _notNULL);

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

int acc() {
    string _name;
    string _pwd;
    int _ms = 0;
    while (true) {
        cout << "===========================================" << endl;
        cout << "== Įveskite naudotojo vardą == : ";
        cin >> _name;
        cout << "== Įveskite slaptažodį      == : ";
        cin >> _pwd;

        ifstream _inFile("../DB/ACC/ACC");

        if (!_inFile) {
            cout << "Nepavyko atidaryti failo!" << endl;
            return 0;
        }

        userData _user;
        while (_user.getData(_inFile)) {
            if (_user.username == _name && _user.password == _pwd) {
                cout << "== Prisijungimas sėkmingas ==" << endl;
                switch (_user.role) {
                    case 'a': {
                        cout << "== Jus prisijungete kaip Administratorius ==" << endl;
                        return 1;
                    }
                    case 'u': {
                        cout << "== Jus prisijungete kaip Naudotojas ==" << endl;
                        return 2;
                    }
                    default: {
                        return 3;
                    }
                }
            }
        }

        cout << "== Ne teisingai įvestas Vardas arba Slaptažodis ==" << endl;
        cout << "===========================================" << endl;
        cout << "== Kartoti prisijungima spauskite    == - 1" << endl;
        cout << "== Nutraukti prisijungima spauskite  == - 0" << endl;
        cout << "===========================================" << endl;
        _ms = menuSelect(_ms, 1, 0);

        if (_ms == 0) {
            return 0;
        }
    }
}
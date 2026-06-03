// Projektinis darbas
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int acc();
int userMenu();
int adminMenu();
int menuSelect(int _select, int _kiekis, int _notNULL);
int longestText(string _tekstoMasyvas[],int n);
void wait();

int main() {
    int _select;
    //Lietuvybė
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    //login
    _select = acc();

    switch (_select) {
        default: {
            cout << "==     Prisijungimas nutrauktas!         ==" << endl;
            return 0;
        }
            case 1: {
            return adminMenu();
        }
            case 2: {
            return userMenu();
        }
            case 3: {
            cout << "== Nežinoma naudotojo rolė!         ==" << endl;
            cout << "== Susisiekite su Administratoriumi ==" << endl;
            wait();
            return 0;
        }

    }



    return 0;
}

int menuSelect(int _select, int _kiekis, int _notNULL) { //start _notNULL
    while (true) {
        while (!(cin >> _select) || _select < 0) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "------------------------------------------------" << endl;
            cout << ">> Pasirinkimas ne tinkamas, rinkites iš menių<<" << endl;
            cout << ">>Pakartokite įvedimą" << endl;
        }

        if ( _select >= _notNULL && _select <= _kiekis) {
            return _select;
        }
        cout << "------------------------------------------------" << endl;
        cout << ">> Pasirinkimas ne tinkamas, rinkites iš menių<<" << endl;
        cout << ">>Pakartokite įvedimą" << endl;
    }
}

int longestText(string _tekstoMasyvas[],int n) {  // Tikrinam ilgiausia teksta

    int _tekstoIlgis = 0;
    for (int i=0; i < n; i++) {
        if (_tekstoIlgis<_tekstoMasyvas[i].length()) {
            _tekstoIlgis = _tekstoMasyvas[i].length();
        }
    }
    return _tekstoIlgis;
}

void wait() {
    string _wait;
    cin.ignore();
    getline(cin,_wait);
}
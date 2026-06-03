// Projektinis darbas
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int acc();
int menuSelect(int _select, int _kiekis, int _notNULL);

int main() {
    int _select;
    //Lietuvybė
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    //login
    _select = acc();
    if (_select == 0) {
        cout << "== Prisijungimas nutrauktas ==" << endl;
        return 0;
    }
    if (_select == 3) {
        cout << "== Nežinoma naudotojo rolė!         ==" << endl;
        cout << "== Susisiekite su Administratoriumi ==" << endl;
        string wait;
        cin.ignore();
        getline(cin, wait);
        return 0;
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
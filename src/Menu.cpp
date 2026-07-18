/**
 * @file Menu.cpp
 * @brief Implementación de la logica de Menu.
 * -----------------------------------------------------------------------------
 *
 * @author Douglas Velez Monginaite | Código 202516737-3743
 * @email douglas.velez@correounivalle.edu.co
 *
 * @author Juan Diego Lopez Gomez | Código 202519861-3743
 * @email juan.lopez.g@correounivalle.edu.co
 *
 * @author Nicolas Andres Ramirez | Código 202415510-3743
 * @email nicolas.andres.ramirez@correounivalle.edu.co
 *
*/

#include "Menu.h"
#include <iostream>

Menu::Menu(string title) : titulo(title) {}
Menu::~Menu() {}

int Menu::showMainMenu() {
    int op = -1;
    while (op < 1 || op > 3) {
        cout << "\n===== BUS ESCAPE: TRAFFIC JAM =====" << endl;
        cout << "1. Iniciar Juego" << endl;
        cout << "2. Ver Instrucciones" << endl;
        cout << "3. Salir" << endl;
        cout << "Opcion: ";
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = -1;
        }
        if (op < 1 || op > 3)
            cout << "Opcion invalida." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op;
}

int Menu::showVehicleSelectionMenu(vector<shared_ptr<Vehicle>>& vehiculos) {
    cout << "\n=== SELECCIONA UN VEHICULO ===" << endl;
    for (size_t i = 0; i < vehiculos.size(); ++i) {
        cout << (i + 1) << ". ";
        vehiculos[i]->display();
        cout << endl;
    }
    cout << (vehiculos.size() + 1) << ". Volver al Menu" << endl;

    int op = -1;
    int maxVal = (int)vehiculos.size() + 1;
    while (op < 1 || op > maxVal) {
        cout << "Selecciona (1-" << vehiculos.size() << "): ";
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = -1;
        }
        if (op < 1 || op > maxVal)
            cout << "Invalido." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op - 1;
}

int Menu::showVehicleActionMenu(shared_ptr<Vehicle> vehicle) {
    cout << "\n=== ACCIONES PARA ";
    vehicle->display();
    cout << " ===" << endl;
    cout << "1. Mover adelante" << endl;
    cout << "2. Mover atras" << endl;
    cout << "3. Enviar a zona de parqueo" << endl;
    cout << "4. Cancelar" << endl;

    int op = -1;
    while (op < 1 || op > 4) {
        cout << "Opcion (1-4): ";
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = -1;
        }
        if (op < 1 || op > 4)
            cout << "Invalido." << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return op;
}

void Menu::showMessage(string message) { cout << "\n" << message << endl; }
void Menu::showError(string error) { cout << "\n[ERROR] " << error << endl; }
void Menu::showSuccess(string success) { cout << "\n[EXITO] " << success << endl; }

void Menu::pause() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
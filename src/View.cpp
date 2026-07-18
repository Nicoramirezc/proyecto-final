/**
 * @file View.cpp
 * @brief Implementación de la logica de View.
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
#include "View.h"
#include <iostream>

View::View() {}
View::~View() {}

void View::displayGameBoard(Board& board) {
    board.mostrar();
}

void View::displayParkingZones(vector<ParkingZone>& zones) {
    cout << "\n=== ZONAS DE PARQUEO ===" << endl;
    int occ = 0;
    for (auto& z : zones) {
        cout << "  ";
        z.display();
        if (z.getIsOccupied()) occ++;
    }
    cout << "Ocupadas: " << occ << "/" << zones.size() << endl;
}

void View::displayPassengerQueue(PassengerQueue& queue) {
    queue.display();
}

void View::displayGameStatus(Board& board, vector<ParkingZone>& zones, PassengerQueue& queue, int level) {
    clearScreen();
    cout << "========================================" << endl;
    cout << "     BUS ESCAPE: TRAFFIC JAM" << endl;
    cout << "          NIVEL " << level << endl;
    cout << "========================================" << endl;
    displayGameBoard(board);
    displayParkingZones(zones);
    displayPassengerQueue(queue);
}

void View::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void View::showMessage(string message) {
    cout << "\n>>> " << message << endl;
}

void View::showError(string error) {
    cout << "\n[ERROR] " << error << endl;
}

void View::showSuccess(string message) {
    cout << "\n[EXITO] " << message << endl;
}
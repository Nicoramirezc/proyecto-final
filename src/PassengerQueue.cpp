/**
 * @file PassengerQueue.cpp
 * @brief Implementación de la logica de PassengerQueue.
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
#include "PassengerQueue.h"
#include <iostream>

PassengerQueue::PassengerQueue() {}
PassengerQueue::~PassengerQueue() {}

void PassengerQueue::addPassenger(Passenger p) {
    pasajeros.push(p);
}

Passenger PassengerQueue::frontPassenger() const {
    if (!pasajeros.empty())
        return pasajeros.front();
    return Passenger(-1, "NONE");
}

void PassengerQueue::removePassenger() {
    if (!pasajeros.empty())
        pasajeros.pop();
}

int PassengerQueue::getSize() const { return pasajeros.size(); }
bool PassengerQueue::isEmpty() const { return pasajeros.empty(); }

const queue<Passenger>& PassengerQueue::getAllPassengers() const {
    return pasajeros;
}

void PassengerQueue::display() const {
    cout << "\n=== FILA DE PASAJEROS ===\n";
    if (pasajeros.empty()) {
        cout << "Fila vacia - ¡VICTORIA!\n";
        return;
    }
    cout << "Esperando: " << pasajeros.size() << "\nCola: ";
    queue<Passenger> temp = pasajeros;
    while (!temp.empty()) {
        cout << temp.front().getColor();
        temp.pop();
        if (!temp.empty()) cout << " -> ";
    }
    cout << endl;
}
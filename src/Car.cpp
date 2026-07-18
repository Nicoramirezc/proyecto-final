/**
 * @file Car.cpp
 * @brief Implementación de la logica de Car.
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
#include "Car.h"
#include <iostream>

Car::Car(int id, int x, int y, int length, string color, Orientation orient)
    : Vehicle(id, x, y, length, color, orient, length), attachedToBus(false) {}

Car::~Car() {}

void Car::display() const {
    string dir = (orientation == HORIZONTAL) ? ">>" : "vv";
    cout << "[CAR #" << id << "] " << color
         << " | " << passengerCount << "/" << maxCapacity
         << " pax " << dir;
    if (attachedToBus) cout << " [acoplado]";
}

string Car::getType() const {
    return "Car";
}

bool Car::isAttachedToBus() const { return attachedToBus; }
void Car::attachToBus(bool attached) { attachedToBus = attached; }
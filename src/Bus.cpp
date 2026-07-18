/**
 * @file Bus.cpp
 * @brief Implementación de la logica de Bus.
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

#include "Bus.h"
#include <iostream>

Bus::Bus(int id, int x, int y, int length, string color, Orientation orient)
    : Vehicle(id, x, y, length, color, orient, length) {}

Bus::~Bus() {}

void Bus::display() const {
    string dir = (orientation == HORIZONTAL) ? ">>" : "vv";
    cout << "[BUS #" << id << "] " << color
         << " | " << passengerCount << "/" << maxCapacity
         << " pax " << dir;
}

string Bus::getType() const {
    return "Bus";
}
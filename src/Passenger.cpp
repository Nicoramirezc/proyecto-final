/**
 * @file Passenger.cpp
 * @brief Implementación de la logica de Passenger.
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
#include "Passenger.h"
#include <iostream>

Passenger::Passenger(int id, string color) : id(id), color(color) {}
Passenger::~Passenger() {}

string Passenger::getColor() const { return color; }
int Passenger::getId() const { return id; }

void Passenger::display() const {
    cout << "Pasajero [ID:" << id << " Color:" << color << "]";
}

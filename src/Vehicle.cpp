/**
 * @file Vehicle.cpp
 * @brief Implementación de la logica de Vehicle.
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

#include "Vehicle.h"

Vehicle::Vehicle(int id, int x, int y, int length, string color, Orientation orient, int capacity)
    : x(x), y(y), length(length), color(color), orientation(orient),
      passengerCount(0), maxCapacity(capacity), id(id) {}

Vehicle::~Vehicle() {}

int Vehicle::getX() const { return x; }
int Vehicle::getY() const { return y; }
int Vehicle::getLength() const { return length; }
string Vehicle::getColor() const { return color; }
Orientation Vehicle::getOrientation() const { return orientation; }
int Vehicle::getId() const { return id; }
int Vehicle::getPassengerCount() const { return passengerCount; }
int Vehicle::getMaxCapacity() const { return maxCapacity; }

int Vehicle::getEndX() const {
    return (orientation == HORIZONTAL) ? x + length - 1 : x;
}

int Vehicle::getEndY() const {
    return (orientation == HORIZONTAL) ? y : y + length - 1;
}

void Vehicle::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Vehicle::addPassenger() {
    if (passengerCount < maxCapacity)
        passengerCount++;
}

void Vehicle::removePassenger() {
    if (passengerCount > 0)
        passengerCount--;
}

bool Vehicle::isFull() const {
    return passengerCount >= maxCapacity;
}
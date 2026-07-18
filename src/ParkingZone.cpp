/**
 * @file ParkingZone.cpp
 * @brief Implementación de la logica de ParkingZone.
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

#include "ParkingZone.h"
#include <iostream>

ParkingZone::ParkingZone(int id) : zoneId(id), vehicleParked(nullptr), occupied(false) {}
ParkingZone::~ParkingZone() {}

int ParkingZone::getZoneId() const { return zoneId; }
bool ParkingZone::getIsOccupied() const { return occupied; }
shared_ptr<Vehicle> ParkingZone::getVehicle() const { return vehicleParked; }

bool ParkingZone::parkVehicle(shared_ptr<Vehicle> vehicle) {
    if (!occupied && vehicle != nullptr) {
        vehicleParked = vehicle;
        occupied = true;
        return true;
    }
    return false;
}

void ParkingZone::removeVehicle() {
    vehicleParked = nullptr;
    occupied = false;
}

bool ParkingZone::isVehicleFull() const {
    return vehicleParked != nullptr && vehicleParked->isFull();
}

void ParkingZone::display() const {
    cout << "ZONA " << zoneId << ": ";
    if (occupied && vehicleParked != nullptr)
        vehicleParked->display();
    else
        cout << "DISPONIBLE";
    cout << endl;
}
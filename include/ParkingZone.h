/**
 * @file ParkingZone.h
 * @brief Declaración de la clase ParkingZone.
 *
 * @details
 * Responsabilidades:
 * - Administrar de forma aislada el estado de ocupación de una celda de parqueo.
 * - Contener y referenciar al vehículo actualmente asignado.
 * - Notificar su disponibilidad al controlador principal.
 *
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
#ifndef PARKINGZONE_H
#define PARKINGZONE_H

#include "Vehicle.h"
#include <memory>
using namespace std;

class ParkingZone
{
private:
    int zoneId;
    shared_ptr<Vehicle> vehicleParked;
    bool occupied;
public:
    ParkingZone(int id);
    ~ParkingZone();
    int getZoneId() const;
    bool getIsOccupied() const;
    shared_ptr<Vehicle> getVehicle() const;
    bool parkVehicle(shared_ptr<Vehicle> vehicle);
    void removeVehicle();
    bool isVehicleFull() const;
    void display() const;
};

#endif
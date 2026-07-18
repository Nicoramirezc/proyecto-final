/**
 * @file PassengerQueue.h
 * @brief Declaración de la clase PassengerQueue.
 *
 * @details
 * Responsabilidades:
 * - Administrar la estructura de datos para los pasajeros que están en espera.
 * - Aislar las operaciones estándar (encolar, desencolar) y adaptarlas al contexto del juego.
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

#ifndef PASSENGERQUEUE_H
#define PASSENGERQUEUE_H

#include "Passenger.h"
#include <queue>

class PassengerQueue
{
private:
    queue<Passenger> pasajeros;
public:
    PassengerQueue();
    ~PassengerQueue();
    void addPassenger(Passenger p);
    Passenger frontPassenger() const;
    void removePassenger();
    int getSize() const;
    bool isEmpty() const;
    const queue<Passenger>& getAllPassengers() const;
    void display() const;
};

#endif
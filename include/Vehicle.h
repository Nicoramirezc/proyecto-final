/**
 * @file Vehicle.h
 * @brief Declaración de la clase Vehicle.
 *
 * @details
 * Responsabilidades:
 * - Establecer el contrato (clase base) y características universales de los vehículos.
 * - Controlar el posicionamiento físico, orientación y tamaño en la matriz.
 * - Administrar la ocupación y límite de pasajeros del vehículo.
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

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

enum Orientation { HORIZONTAL, VERTICAL };

class Vehicle
{
protected:
    int x, y;
    int length;
    string color;
    Orientation orientation;
    int passengerCount;
    int maxCapacity;
    int id;

public:
    Vehicle(int id, int x, int y, int length, string color, Orientation orient, int capacity);
    virtual ~Vehicle();

    // Getters
    int getX() const;
    int getY() const;
    int getLength() const;
    string getColor() const;
    Orientation getOrientation() const;
    int getId() const;
    int getPassengerCount() const;
    int getMaxCapacity() const;
    int getEndX() const;
    int getEndY() const;

    void setPosition(int newX, int newY);
    void addPassenger();
    void removePassenger();
    bool isFull() const;

    // Métodos polimórficos puros
    virtual void display() const = 0;
    virtual string getType() const = 0;
};

#endif
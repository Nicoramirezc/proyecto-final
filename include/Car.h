/**
 * @file Car.h
 * @brief Declaración de la clase Car.
 *
 * @details
 *   Responsabilidades:
 *   - Representar un carro en el juego
 *   - Heredar de Vehicle e implementar métodos específicos
 *   - Poder desprenderse del bus (si se requiere)
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

#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle
{
private:
    bool attachedToBus;
public:
    Car(int id, int x, int y, int length, string color, Orientation orient);
    ~Car();
    void display() const override;
    string getType() const override;
    bool isAttachedToBus() const;
    void attachToBus(bool attached);
};

#endif
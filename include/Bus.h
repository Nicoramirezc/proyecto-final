/**
 * @file Bus.h
 * @brief Declaración de la clase Bus.
 *
 * @details
 * Responsabilidades:
 * - Representar la entidad de tipo Bus dentro de la lógica del juego.
 * - Proveer las implementaciones específicas heredadas de la clase base Vehicle.
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

#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

class Bus : public Vehicle
{
public:
    Bus(int id, int x, int y, int length, string color, Orientation orient);
    ~Bus();
    void display() const override;
    string getType() const override;
};

#endif
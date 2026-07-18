/**
 * @file Passenger.h
 * @brief Declaración de la clase Passenger.
 *
 * @details
 * Responsabilidades:
 * - Representar la entidad Pasajero de forma individual.
 * - Almacenar e identificar sus atributos clave (color, ID) que condicionan el abordaje.
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

#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger
{
private:
    // Número de identificación de la entidad
    int id;             
    
    // Atributo restrictivo requerido para coincidir con un vehículo
    string color;       

public:
    // Construye un nuevo pasajero con color asignado
    Passenger(int id, string color);
    
    // Libera la memoria del pasajero
    ~Passenger();
    
    // Consultas de los campos de entidad
    string getColor() const;
    int getId() const;
    
    // Imprime la representación gráfica del pasajero 
    void display() const;
};

#endif
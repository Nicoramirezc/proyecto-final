/**
 * @file Board.h
 * @brief Implementación de la clase Board.
 *
 * @details
 * Responsabilidades:
 * - Cargar y mapear la estructura del nivel a través de archivos de texto.
 * - Contener y administrar el estado de los vehículos activos.
 * - Aplicar las reglas del entorno (limites físicos, prevención de colisiones).
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

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "Vehicle.h"
using namespace std;

class Board
{
private:
    int ancho;
    int alto;
    vector<shared_ptr<Vehicle>> vehiculos;

public:
    Board();
    Board(int w, int h);
    Board(const string& filename);
    ~Board();

    void resize(int w, int h);
    bool cargarDesdeArchivo(const string& filename);

    int getAncho() const;
    int getAlto() const;
    const vector<shared_ptr<Vehicle>>& getVehiculos() const;
    shared_ptr<Vehicle> getVehicleById(int id) const;

    void addVehicle(shared_ptr<Vehicle> vehicle);
    void removeVehicle(int vehicleId);
    void clearVehicles();

    bool esValido(int x, int y) const;
    bool hasCollision(int x, int y, int length, Orientation orient, int excludeId = -1) const;
    bool canVehicleMove(int vehicleId, int newX, int newY) const;
    bool canVehicleExitBoard(int vehicleId, int direction) const;
    bool moveVehicle(int vehicleId, int newX, int newY);

    void mostrar() const;
};

#endif
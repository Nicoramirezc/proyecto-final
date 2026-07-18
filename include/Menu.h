/**
 * @file Menu.h
 * @brief Declaración de la clase Menu.
 *
 * @details
 * Responsabilidades:
 * - Desplegar la interfaz de opciones del juego al usuario.
 * - Capturar y retornar la entrada del usuario de forma segura.
 * - Administrar la navegación entre menús (principal y selección de vehículos).
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

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include "Vehicle.h"
using namespace std;

class Menu
{
private:
    string titulo;
public:
    Menu(string title = "");
    ~Menu();
    int showMainMenu();
    int showVehicleSelectionMenu(vector<shared_ptr<Vehicle>>& vehiculos);
    int showVehicleActionMenu(shared_ptr<Vehicle> vehicle);
    void showMessage(string message);
    void showError(string error);
    void showSuccess(string success);
    void pause();
};

#endif